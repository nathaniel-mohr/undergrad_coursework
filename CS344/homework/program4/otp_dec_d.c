// Program: otp_dec_d.c
// Author: Nathaniel Mohr
// Arguments: ciphertext, key, port
// Description: Server side for the encryption.
//							Communicates with client over socket
//							Receives ciphertext and key from client
//							Decrypts ciphertext using key to form plaintext
//							Sends plaintext to client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues
void* threadFunction(void*);

pthread_mutex_t lock;
int listenSocketFD;

int main(int argc, char *argv[])
{
	struct sockaddr_in serverAddress;
	int portNumber;
	pthread_t threads[5];
	int i;

	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections

	// Initialize mutex
	if(pthread_mutex_init(&lock, NULL) != 0){
		fprintf(stderr, "mutex init has failed\n");
		return 1;
	}

	// Lock mutex
	if(pthread_mutex_lock(&lock) != 0){
		fprintf(stderr, "mutex locking has failed\n");
		return 1;
	}

	// Create pthread
	for(i = 0; i < 5; i++){
		if(pthread_create(&threads[i], NULL, &threadFunction, NULL) != 0){
			fprintf(stderr, "Thread creation has failed\n");
			return 1;
		}
	}

	pthread_mutex_unlock(&lock);
/*

*/
	pthread_join(threads[0], NULL);
	return 0;
}

void* threadFunction(void* arg){
	struct sockaddr_in clientAddress;
	socklen_t sizeOfClientInfo;
	int establishedConnectionFD, charsRead;
	char childType[8];
	int ciphertextLength, keyLength, i;

	pthread_mutex_lock(&lock);

	while(1){
		// Accept a connection, blocking if one is not available until one connects
		sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
		if (establishedConnectionFD < 0) error("ERROR on accept");

		pthread_mutex_unlock(&lock);

		// Get childType from the client and display it
		memset(childType, '\0', 8);
		charsRead = recv(establishedConnectionFD, childType, 7, 0); // Read the client's message from the socket
		if (charsRead < 0) error("ERROR reading from socket");
		// If wrong child, send N, close connection and go to top of while
		if(strcmp(childType, "OTP_DEC") != 0){
			charsRead = send(establishedConnectionFD, "N", 1, 0); // Send success back
			if (charsRead < 0) error("ERROR writing to socket");
			close(establishedConnectionFD); // Close the existing socket which is connected to the client
			continue;
		// Else send Y and continue on
		}else{
			charsRead = send(establishedConnectionFD, "Y", 1, 0); // Send success back
			if (charsRead < 0) error("ERROR writing to socket");
		}

		// Receive length of ciphertext
		charsRead = read(establishedConnectionFD, &ciphertextLength, sizeof(ciphertextLength)); // Read the client's message from the socket

		// Receive length of key
		charsRead = read(establishedConnectionFD, &keyLength, sizeof(keyLength)); // Read the client's message from the socket

		// Receive ciphertext
		char ciphertextFile[ciphertextLength];
		charsRead = 0;
		while(charsRead < ciphertextLength){
			charsRead += recv(establishedConnectionFD, &ciphertextFile[charsRead], ciphertextLength - charsRead, 0); // Read the client's message from the socket
			if (charsRead < 0) error("ERROR reading from socket");
		}

		// Receive key
		char keyFile[keyLength];
		charsRead = 0;
		while(charsRead < keyLength){
			charsRead += recv(establishedConnectionFD, &keyFile[charsRead], keyLength - charsRead, 0); // Read the client's message from the socket
			if (charsRead < 0) error("ERROR reading from socket");
		}

		// Decode
		char decodedMessage[ciphertextLength];
		memset(decodedMessage, '\0', ciphertextLength);
		int pn, kn, cn;
		for(i = 0; i < ciphertextLength; i++){
			pn = (ciphertextFile[i] == ' ') ? 26 : (int) ciphertextFile[i] - 65;
			kn = (keyFile[i] == ' ') ? 26 : (int) keyFile[i] - 65;
			cn = (pn - kn);
			// If negative, make not
			if(cn < 0){
				cn += 27;
			}
			cn %= 27;
			decodedMessage[i] = (cn == 26) ? ' ' : (char) (cn + 65);
		}

		// Send ciphertext
		charsRead = 0;
		while(charsRead < ciphertextLength){
			charsRead += send(establishedConnectionFD, decodedMessage, ciphertextLength - charsRead, 0); // Send success back
			if (charsRead < 0) error("ERROR writing to socket");
		}

		close(establishedConnectionFD); // Close the existing socket which is connected to the client

		pthread_mutex_lock(&lock);
	}

  pthread_exit(0);
}
