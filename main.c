#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


void startServer(struct Server *self)
{
    char buffer[3000];
    int adress_length = sizeof(self->address);
    socklen_t addr_len = (socklen_t)adress_length;
    printf("Server started on port %d\n", self->port);
    while(1)
    {
        printf("WAITING FOR CLIENT\n");
        int client = accept(self->socket, (struct sockaddr *)&self->address, &addr_len);    
        if(client < 0)
        {
            perror("accept");
            exit(1);
        }
        read(client, buffer, sizeof(buffer));
        printf("%s\n\n", buffer);
        printf("Client connected\n");
        char hello[] = "HTTP/1.1 200 OK\n"
              "Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
              "Server: Apache/2.2.14 (Win32)\n"
              "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
              "Content-Type: text/html\n"
              "Connection: Closed\n"
              "\n"
              "<html><body><h1>Hello World</h1></body></html>";

        write(client, hello, strlen(hello));
        close(client);
    }
}

int main()
{
    struct Server server = newServer(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 5, &startServer);
    server.start(&server);
    return 0;
}