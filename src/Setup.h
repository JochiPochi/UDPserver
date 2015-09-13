/*
 * Setup.h
 *
 *  Created on: Sep 13, 2015
 *      Author: jaleman
 */

#ifndef SETUP_H_
#define SETUP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>      // Error number definitions
//Needed for Network
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

extern int NetworkSetup(char *portNumber);


#endif /* SETUP_H_ */
