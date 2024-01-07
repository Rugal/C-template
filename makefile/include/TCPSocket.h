/* 
 * File:   InternetSocket.h
 * Author: Rugal Bernstein
 *
 * Created on March 20, 2016, 1:42 PM
 */

#ifndef INTERNETSOCKET_H
#define INTERNETSOCKET_H
#include <netinet/in.h>
#include "Configuration.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * Create a TCP based internet socket.
     * @return
     */
    int createTCPSocket();
    /**
     * Bind an socket with address and port.
     * In this version of implementation, it will bind to 0.0.0.0:port
     * @param sd
     * @param port
     * @return
     */
    struct sockaddr_in* bindTCPAddress(Configuration* conf);


#ifdef __cplusplus
}
#endif

#endif /* INTERNETSOCKET_H */

