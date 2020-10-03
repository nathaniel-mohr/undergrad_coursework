// Program: otp_enc.c
// Author: Nathaniel Mohr
// Arguments: plaintext, key, port
// Description: Client side for the encryption.
//							Communicates with daemon over socket
//							Sends plaintext and key to daemon
//							Receives ciphertext from daemon and prints out

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
	char* plaintextFile = NULL;
	char* keyFile = NULL;
	int plaintextLength, keyLength, i;

	if (argc < 4) { fprintf(stderr,"USAGE: %s plaintext key port\n", argv[0]); exit(0); } // Check usage & args

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
	strcpy(childType,"OTP_ENC");
	charsWritten = send(socketFD, childType, 7, 0); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < 7) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Get return message from server
	memset(serverResponse, '\0', 2); // Clear out the buffer again for reuse
	charsRead = recv(socketFD, serverResponse, 1, 0); // Read data from the socket, leaving \0 at end
	if (charsRead < 0) error("CLIENT: ERROR reading from socket");
	// If trying to connect to wrong port, exit
	if(strcmp(serverResponse, "N") == 0){
		fprintf(stderr, "OTP_ENC cannot connect to OTP_DEC_D on port %d\n", portNumber);
		exit(2);
	}

	// Get plaintext info
	fp = fopen(argv[1], "r");
	getline(&plaintextFile, &buffer, fp);
	plaintextLength = strlen(plaintextFile) - 1;
	fclose(fp);

	// Get key info
	fp = fopen(argv[2], "r");
	getline(&keyFile, &buffer, fp);
	keyLength = strlen(keyFile) - 1;
	fclose(fp);

	// Key is shorter than plaintext: exit(1)
	if(keyLength < plaintextLength){
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

	// Plaintext has bad characters: exit(1)
	for(i = 0; i < plaintextLength; i++){
		if((int)plaintextFile[i] != 32){
			if((int)plaintextFile[i] < 65 || (int)plaintextFile[i] > 90){
				fprintf(stderr, "Bad characters in %s\n", argv[1]);
				exit(1);
			}
		}
	}
	// Send length of plaintext
	charsWritten = write(socketFD, &plaintextLength, sizeof(plaintextLength)); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < sizeof(int)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Send length of key
	charsWritten = write(socketFD, &keyLength, sizeof(keyLength)); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < sizeof(int)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Send plaintext
	charsWritten = 0;
	while(charsWritten < plaintextLength){
		charsWritten += send(socketFD, plaintextFile, plaintextLength - charsWritten, 0); // Write to the server
		if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
		if (charsWritten < plaintextLength) printf("CLIENT: WARNING: Not all data written to socket!\n");
	}

	// Send key
	charsWritten = 0;
	while(charsWritten < keyLength){
		charsWritten += send(socketFD, keyFile, keyLength - charsWritten, 0); // Write to the server
		if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
		if (charsWritten < keyLength) printf("CLIENT: WARNING: Not all data written to socket!\n");
	}

	// Receive ciphertext
	charsRead = 0;
	char ciphertextFile[plaintextLength + 1];
	memset(ciphertextFile, '\0', plaintextLength + 1);
	while(charsRead < plaintextLength){
		charsRead += recv(socketFD, ciphertextFile, plaintextLength - charsRead, 0); // Read the client's message from the socket
		if (charsRead < 0) error("ERROR reading from socket");
	}

	fprintf(stdout, "%s\n", ciphertextFile);

	close(socketFD); // Close the socket
	return 0;
}
