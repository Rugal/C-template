#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "TCPSocket.h"
#include "Configuration.h"
#include "String.h"


void startClient(int server)
{
    while(1)
    {
        String* s = createString(10);
        char buffer;
        printf("-->\n");
        //read from stdin
        while (scanf("%c", &buffer) > 0 && buffer != '\n')
            appendChar(s, buffer);
        if(size(s) == 0)
        {
            deleteString(s);
            continue;
        }
        if(strncmp("exit", data(s), 4) == 0)
        {
            write(server, "exit", 5);
            break;
        }
        //put last newline character
        appendChar(s, '\0');
        //send data to server
        write(server, data(s), size(s));
        deleteString(s);
        //read output from server
        int count ;
        while(read(server, &buffer, 1)>0 && buffer != '\0')
            printf("%c", buffer);
    }
}

/*
 *
 */
int main(int argc, char** argv)
{
    //prepare paremeters
    Configuration* conf = createConfiguration();
    if(argc <= 1)
    {
        fprintf(stderr, "USAGE:\nclient <server.ip.address> <port to connect>\n");
        exit(0);
    }
    if(argc == 2)//only port
        conf->port = atoi(argv[1]);
    else
    {
        conf->ip = argv[1];
        conf->port = atoi(argv[2]);
    }
    //create socket to connect to server
    int server = createTCPSocket();
    struct sockaddr_in serverAddress ;
    serverAddress.sin_family = AF_INET;
    if(conf->ip == NULL)
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        serverAddress.sin_addr.s_addr = inet_addr(conf->ip);
    serverAddress.sin_port = htons(conf->port);
    deleteConfiguration(conf);
    //Trying to connect to server
    printf("Trying to connect server %s:%d\n",inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port));
    if (connect(server, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        fprintf(stderr, "Unable to connect to server\n" );
        exit(2);
    }
    printf("Server connected %s:%d\n",inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port));
    startClient(server);
    close(server);
    /*exit(0);*/
    return (EXIT_SUCCESS);
}
