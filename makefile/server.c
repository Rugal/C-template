/*
 * File:   main.c
 * Author: Rugal Bernstein
 *
 * Created on March 20, 2016, 12:28 PM
 */
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include "TCPSocket.h"
#include "Configuration.h"
#include "String.h"
#include "ArrayList.h"
#define BUFFER_SIZE 1024

void handler(int s)
{
    if( s == SIGPIPE )
        exit(0);
    int status;
    /*waitpid(0, &status, WNOHANG);*/
    wait(&status);
    printf("One child terminated %d\n", s);
}

void execute(int socket, ArrayList* list)
{
    //going to use pipe
    char buffer;
    int status=0, p[2];
    if(pipe(p)<0)
        fprintf(stderr, "Unable to create pipe\n");
    if(fork()==0) // child
    {
        printf("A child process has been dispatched to execute:\n");
        for(int i=0; i < list->size ; i++)
            printf("%s ", list->array[i]);
        printf("\n");
        //piping stdout to pipe-write
        dup2(p[1], 1);
        dup2(p[1], 2);
        close(p[0]);
        close(p[1]);
        execvp(list->array[0], list->array);
        exit(0);
        printf("Should not be here\n");
    }
    else
    {
        wait(&status);
        //read from pipe
        //send to through socket
        close(p[1]);
        while (read(p[0], &buffer, 1) > 0)
            write(socket, &buffer, 1);
        close(p[0]);
        buffer='\0';
        write(socket, &buffer, 1);
    }
}

ArrayList* readCommand(int socket, ArrayList* list)
{
    //Buffering all input command
    String* s = createString(10);
    char input;
    while(read(socket, &input, 1) > 0 &&  '\0' != input)
    {
        printf("%c", input);
        appendChar(s, input);
    }
    /*printf("\n%d\n", size(s));*/
    if(0 == size(s))
    {
        deleteString(s);
        return NULL;
    }
    //extract each word into word array
    FILE *stream = fmemopen(data(s), size(s), "r");
    while(!feof(stream))
    {
        char token[BUFFER_SIZE];
        fscanf(stream, "%s", token);
        addWord(list, token);
    }
    fclose(stream);
    deleteString(s);
    //See if time to exit
    return list;
}

void childProcess(int socket, struct sockaddr_in * client)
{
    for(int count = 0; 1; count++)
    {
        signal(SIGPIPE, handler);
        //printf("Waiting for data from %s:%d\n",
                //inet_ntoa(client->sin_addr),
                //htons(client->sin_port));
        //buffering all command input
        ArrayList* list = createArrayList();
        if(NULL == readCommand(socket, list))
        {
            deleteArrayList(list);
            if(count == 5)
                break;
            continue;
        }
        if(strncmp("exit", list->array[0], 4) == 0)
            break;
        printf("Receiving data from %s:%d\n",
                inet_ntoa(client->sin_addr),
                htons(client->sin_port));
        //See if time to exit
        /*if(strcmp(list->array[0], "exit") == 0)*/
            /*break;*/
        printf("Going to execute command for %s:%d\n",
                inet_ntoa(client->sin_addr),
                htons(client->sin_port));
        //execute command and listen from pipe
        execute(socket, list);
        deleteArrayList(list);
        count=0;
    }
    close(socket);
}

void registerSignal()
{
    struct sigaction act;
    memset(&act, 0, sizeof (act));
    act.sa_handler = &handler;
    act.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &act, NULL) < 0)
    {
        perror("Unable to handle Signal Child!\n");
        exit(1);
    }
}

void start(int socket)
{
    struct sockaddr_in clientAddress;
    socklen_t clientLength = sizeof (clientAddress);
    int client = 0;
    while ((client = accept(socket, (struct sockaddr *)&clientAddress, &clientLength)) >= 0)
    {
        registerSignal();
        printf("Get connection from %s:%d\n",inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        if(0 == fork()) // child
        {
            close(socket);
            printf("Child forked for %s:%d\n",inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
            childProcess(client, &clientAddress);
            printf("Child terminating for %s:%d\n",inet_ntoa(clientAddress.sin_addr),ntohs(clientAddress.sin_port));
            exit(0);
        }
        //Signal register
        close(client);
    }
}

/*
 *
 */
int main(int argc, char** argv)
{
    //paremeter setting
    Configuration* conf = createConfiguration();
    if(argc > 1)
    {
        conf->port = atoi(argv[1]);
    }


    //socket setup
    printf("Server launched\n");
    conf->socket = createTCPSocket();
    struct sockaddr_in *serverAddress = bindTCPAddress(conf);
    printf("Bind socket to %s:%d\n",inet_ntoa(serverAddress->sin_addr), ntohs(serverAddress->sin_port));
        //specify the quene length
    listen(conf->socket, conf->queue);

    //start listening
    printf("Server listening\n");
    start(conf->socket);

    //Cleanup
    close(conf->socket);
    deleteConfiguration(conf);
    free(serverAddress);
    return (EXIT_SUCCESS);
}
