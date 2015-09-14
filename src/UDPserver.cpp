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
	/*
	 * Check if arguments were set up correctly
	 */
	if (argc != 4) {
		fprintf(stderr,
				"usage: UDPserver [Port to listen to] [Destination IP] [Destination Port]\n");
		exit(1);
	}
	/*
	 * Network Setup
	 */
	int fdmax = 0;
	fd_set fdlist;
	FD_ZERO(&fdlist);

	int sockfd = NetworkSetup(argv[1]);
	/*
	 * Timer Setup and others
	 */
	struct timeval tic;
//	bool toggleSwitch1 = false;
//	int64_t microseconds;
	gettimeofday(&tic, NULL);
	/*
	 * Main Loop starts here
	 */
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
			perror("poll"); //error in poll
			exit(4);
		} else if (pollResult == 0) {
			// Timeout handler
			printf("Timeout occurred!  No data after 3000 milliseconds.\n");
		} else {
			// Check for events on listenfd:
			char bufs[MAXBUFLEN];
			int nbytes;

			struct sockaddr_storage client_addr;
			socklen_t addr_len;
			addr_len = sizeof client_addr;
			if ((nbytes = recvfrom(sockfd, bufs, sizeof bufs, 0,
					(struct sockaddr *)&client_addr, &addr_len)) == -1) {
				// got error or connection closed by client
				perror("recvfrom: invalid file descriptorr");
			} else {
				//We got some data from a client
				printf(":%s :%i \n", bufs, nbytes);
				int numbytes;
				char UDPpacket[] = "Hi There22";
				if ((numbytes = sendto(sockfd, UDPpacket, sizeof(UDPpacket), 0,
						(struct sockaddr *)&client_addr, sizeof(client_addr))) == -1) {
					perror("talker: sendto");
				}

			}
		}
	}
	close(sockfd);
	return 1;
}
