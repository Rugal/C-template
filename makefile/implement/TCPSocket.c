#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "TCPSocket.h"
#include "Configuration.h"

int createTCPSocket()
{
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        perror("Unable to create socket\n");
        exit(1);
    }
    return sd;
}

struct sockaddr_in* bindTCPAddress(Configuration* conf)
{
    //Create sockAddress object
    struct sockaddr_in* serverAddress = malloc(sizeof (struct sockaddr_in));
    {
        memset(serverAddress, 0, sizeof (struct sockaddr_in));
        serverAddress->sin_family = AF_INET;
        serverAddress->sin_addr.s_addr = htonl(conf->address);
        serverAddress->sin_port = htons(conf->port);
    }
    //Trying to bind socket with specific address and port
    if (bind(conf->socket, (struct sockaddr *) serverAddress, sizeof (struct sockaddr_in)) < 0)
    {
        fprintf(stderr, "Unable to bind socket to %s:%d\n",inet_ntoa(serverAddress->sin_addr), htons(serverAddress->sin_port));
        exit(1);
    }
    return serverAddress;
}
