// Program: otp_dec.c
// Author: Nathaniel Mohr
// Arguments: ciphertext, key, port
// Description: Client side for the decryption.
//							Communicates with daemon over socket
//							Sends ciphertext and key to daemon
//							Receives plaintext from daemon and prints out

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues

int main(int argc, char *argv[]) {
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char childType[8], serverResponse[2];
	FILE* fp;
	ssize_t buffer = 0;
	char* ciphertextFile = NULL;
	char* keyFile = NULL;
	int ciphertextLength, keyLength, i;

	if (argc < 4) { fprintf(stderr,"USAGE: %s ciphertext key port\n", argv[0]); exit(0); } // Check usage & args

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");

	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");


	// Send childType to server
	strcpy(childType,"OTP_DEC");
	charsWritten = send(socketFD, childType, 7, 0); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < 7) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Get return message from server
	memset(serverResponse, '\0', 2); // Clear out the buffer again for reuse
	charsRead = recv(socketFD, serverResponse, 1, 0); // Read data from the socket, leaving \0 at end
	if (charsRead < 0) error("CLIENT: ERROR reading from socket");
	// If trying to connect to wrong port, exit
	if(strcmp(serverResponse, "N") == 0){
		fprintf(stderr, "OTP_DEC cannot connect to OTP_ENC_D on port %d\n", portNumber);
		exit(2);
	}

	// Get ciphertext info
	fp = fopen(argv[1], "r");
	getline(&ciphertextFile, &buffer, fp);
	ciphertextLength = strlen(ciphertextFile) - 1;
	fclose(fp);

	// Get key info
	fp = fopen(argv[2], "r");
	getline(&keyFile, &buffer, fp);
	keyLength = strlen(keyFile) - 1;
	fclose(fp);

	// Key is shorter than ciphertext: exit(1)
	if(keyLength < ciphertextLength){
		fprintf(stderr, "Error: key %s too short\n", argv[2]);
		exit(1);
	}

	// Key has bad characters: exit(1)
	for(i = 0; i < keyLength; i++){
		if((int)keyFile[i] != 32){
			if((int)keyFile[i] < 65 || (int)keyFile[i] > 90){
				fprintf(stderr, "Bad characters in %s\n", argv[2]);
				exit(1);
			}
		}
	}

	// ciphertext has bad characters: exit(1)
	for(i = 0; i < ciphertextLength; i++){
		if((int)ciphertextFile[i] != 32){
			if((int)ciphertextFile[i] < 65 || (int)ciphertextFile[i] > 90){
				fprintf(stderr, "Bad characters in %s\n", argv[1]);
				exit(1);
			}
		}
	}
	// Send length of ciphertext
	charsWritten = write(socketFD, &ciphertextLength, sizeof(ciphertextLength)); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < sizeof(int)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Send length of key
	charsWritten = write(socketFD, &keyLength, sizeof(keyLength)); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < sizeof(int)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Send ciphertext
	charsWritten = 0;
	while(charsWritten < ciphertextLength){
		charsWritten += send(socketFD, ciphertextFile, ciphertextLength - charsWritten, 0); // Write to the server
		if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
		if (charsWritten < ciphertextLength) printf("CLIENT: WARNING: Not all data written to socket!\n");
	}

	// Send key
	charsWritten = 0;
	while(charsWritten < ciphertextLength){
		charsWritten = send(socketFD, keyFile, keyLength, 0); // Write to the server
		if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
		if (charsWritten < keyLength) printf("CLIENT: WARNING: Not all data written to socket!\n");
	}

	// Receive plaintext
	charsRead = 0;
	char plaintextFile[ciphertextLength+1];
	memset(plaintextFile, '\0', ciphertextLength + 1);
	while(charsRead < ciphertextLength){
		charsRead += recv(socketFD, plaintextFile, ciphertextLength - charsRead, 0); // Read the client's message from the socket
		if (charsRead < 0) error("ERROR reading from socket");
	}

	printf("%s\n", plaintextFile);

	close(socketFD); // Close the socket
	return 0;
}
