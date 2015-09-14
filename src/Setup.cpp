/*
 * Setup.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: jaleman
 */

#include "Setup.h"

int NetworkSetup(char *portNumber){
	int rv;
	struct addrinfo hints, *ai, *p;
	/*
	 * Setup hints Struct
	 */
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	/*
	 * Initialize Socket and Bind it
	 */
	int sockfd;
	if ((sockfd = socket(hints.ai_family, hints.ai_socktype, 0)) == -1) {
		perror("talker: socket");
	}
	if ((rv = getaddrinfo(NULL, portNumber, &hints, &ai)) != 0) {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
		exit(1);
	}
	for (p = ai; p != NULL; p = p->ai_next) {
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("sockfd: bind");
			continue;
		}
		break;
	}
	if (p == NULL) {
		fprintf(stderr, "selectserver: failed to bind\n");
		return -1;
	}
	freeaddrinfo(ai);
	return sockfd;
}
