#include <stdio.h>
#include <stdlib.h>
#include "server.h"

struct Server newServer(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*start)(struct Server *self))
{
    struct Server server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;
    server.start = start;

    server.address.sin_family = domain;
    server.address.sin_addr.s_addr = htonl(interface);
    server.address.sin_port = htons(port);

    server.socket = socket(domain, service, protocol);
    if(server.socket < 0)
    {
        perror("socket");
        exit(1);
    }

    if(bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
    {
        perror("bind");
        exit(1);
    }

    if(listen(server.socket, backlog) < 0)
    {
        perror("listening failed");
        exit(1);
    }

    server.start = start;
    
    return server;
}