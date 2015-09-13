//============================================================================
// Name        : UDPserver.cpp
// Author      : John R Aleman
// Version     :
// Copyright   : Your copyright notice
// Description : This program creates and binds a UDP Socket. It listens to
//				 UDP packets and saves it's contents to a database
//============================================================================

#include "Setup.h"

using namespace std;

#define MAXBUFLEN 100

int main(int argc, char *argv[]) {

	if (argc != 4) {
		fprintf(stderr,
				"usage: UDPserver [Port to listen to] [Destination IP] [Destination Port]\n");
		exit(1);
	}

	/*****************************
	 Network SetUp
	 ******************************/
//    #define PORT "4950"
	int fdmax = 0;
	fd_set fdlist;
	FD_ZERO(&fdlist);

//	int rv;
//	struct addrinfo hints, *ai, *p, *ab;
//	/*
//	 * Setup hints Struct
//	 */
//	memset(&hints, 0, sizeof hints);
//	hints.ai_family = AF_INET;
//	hints.ai_socktype = SOCK_DGRAM;
//	hints.ai_flags = AI_PASSIVE;
//	/*
//	 * Initialize Socket and Bind it
//	 */
//	int sockfd;
//	if ((sockfd = socket(hints.ai_family, hints.ai_socktype, 0)) == -1) {
//		perror("talker: socket");
//	}
	//getaddrinfo(NULL, argv[1], &hints, &ab);
//	for (p = ai; p != NULL; p = p->ai_next) {
//		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
//			close(sockfd);
//			perror("sockfd: bind");
//			continue;
//		}
//		break;
//	}
//	if (p == NULL) {
//		fprintf(stderr, "selectserver: failed to bind\n");
//		exit(2);
//	}

	int sockfd = NetworkSetup(argv[1]);

//	if ((rv = getaddrinfo(argv[2], argv[3], &hints, &ai)) != 0) {
//		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
//		return 1;
//	}

	/*****************************
	 Timer and others
	 ******************************/

	struct timeval tic;
//	bool toggleSwitch1 = false;
//	int64_t microseconds;
	gettimeofday(&tic, NULL);

	/*****************************
	 Main Loop
	 ******************************/
	printf("Setup Successful, entering the main loop.\n");

	while (1) {
		// UDP Catcher
		fdmax = sockfd;
		fd_set read_fds;
		FD_ZERO(&read_fds);
		FD_SET(sockfd, &read_fds);
		struct timeval tv;
		tv.tv_sec = 4;
		tv.tv_usec = 0;

		int pollResult = select(fdmax + 1, &read_fds, NULL, NULL, &tv);
		if (pollResult == -1) {
			perror("poll"); //error occured in poll
			exit(4);
		} else if (pollResult == 0) {
			// Timeout handler
			printf("Timeout occurred!  No data after 3000 milliseconds.\n");
		} else {
			// Check for events on listenfd:
			//struct sockaddr_in their_addr;
			char bufs[MAXBUFLEN];
			int nbytes;
			//socklen_t addr_len;
//			struct addrinfo client_addr, *client_addr_pointer;
//			client_addr_pointer = &client_addr;
			// Handle data from a client
			struct addrinfo client_addr;
//			memset(&client_addr, 0, sizeof client_addr);
//			client_addr.ai_family = AF_INET;
//			client_addr.ai_socktype = SOCK_DGRAM;
//			client_addr.ai_flags = AI_PASSIVE;

//			if ((nbytes = recvfrom(sockfd, bufs, sizeof bufs, 0,
//					(struct sockaddr *) &their_addr, &addr_len)) == -1) {
//				// got error or connection closed by client
//				perror("recvfrom: invalid file descriptorr");
//			} else {
//			if ((nbytes = recvfrom(sockfd, bufs, sizeof bufs, 0,
//					client_addr_pointer->ai_addr,
//					&client_addr_pointer->ai_addrlen)) == -1) {
//				// got error or connection closed by client
//				perror("recvfrom: invalid file descriptorr");
//			} else {
			if ((nbytes = recvfrom(sockfd, bufs, sizeof bufs, 0,
					client_addr.ai_addr, &client_addr.ai_addrlen)) == -1) {
				// got error or connection closed by client
				perror("recvfrom: invalid file descriptorr");
			} else {
				//We got some data from a client
				printf(":%s :%i \n", bufs, nbytes);
				int numbytes;
				char UDPpacket[] = "Hi There22";
//				if ((numbytes = sendto(sockfd, UDPpacket, sizeof(UDPpacket), 0,
//						(struct sockaddr *) &their_addr, addr_len)) == -1) {
//					perror("talker: sendto");
//				}
//				if ((numbytes = sendto(sockfd, UDPpacket, sizeof(UDPpacket), 0,
//						client_addr_pointer->ai_addr,
//						client_addr_pointer->ai_addrlen)) == -1) {
//					perror("talker: sendto");
//				}
				if ((numbytes = sendto(sockfd, UDPpacket, sizeof(UDPpacket), 0,
						client_addr.ai_addr, client_addr.ai_addrlen)) == -1) {
					perror("talker: sendto");
				}

			}
		}

//		int rv;
//		struct addrinfo hints, *ai, *p;
//		/*
//		 * Setup hints Struct
//		 */
//		memset(&hints, 0, sizeof hints);
//		hints.ai_family = AF_INET;
//		hints.ai_socktype = SOCK_DGRAM;
//		hints.ai_flags = AI_PASSIVE;
//		if ((rv = getaddrinfo(argv[2], argv[3], &hints, &ai)) != 0) {
//			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
//			return 1;
//		}
//
//        int numbytes;
//        char UDPpacket[] = "Hi There2";
//		if ((numbytes = sendto(sockfd, UDPpacket, sizeof(UDPpacket), 0,
//				ai->ai_addr, ai->ai_addrlen)) == -1) {
//			perror("talker: sendto");
//			exit(1);
//		}
//		break;

	}

	/*****************************
	 Wrap up
	 ******************************/
	//freeaddrinfo(ai); // all done with this
	close(sockfd);
	return 1;
}
