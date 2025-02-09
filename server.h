#pragma once

#include <sys/socket.h>
#include <netinet/in.h> 

struct Server {
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;
    // ip Address
    struct sockaddr_in address;

    void (*start)( struct Server *self);

    int socket;
};

struct Server newServer(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*start)(struct Server *self));