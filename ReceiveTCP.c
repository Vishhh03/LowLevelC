#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if (listenfd < 0){
        perror("socket");
        return 1;
    }

    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY; 
    // sin_addr is defined as a struct, read the sin_addr definition in <netinet/in.h>
    // INADDR_ANY = 0 so it translates to 0.0.0.0 which in kernel means allow all IPs

    bind(listenfd,
    (struct sockaddr *)&server,
    sizeof(server)
    );
    // bind socket to port
    listen(listenfd, 5);
    // Mark the socket as a listening socket
    int clientfd = accept(listenfd, NULL, NULL);
    // returns a new socket file descriptor from kernel of a connection made to the port that listenfd is listening to
    
    char buffer[1024];
    //buffer string to receive the payload
    int bytes = recv(clientfd, buffer, sizeof(buffer)-1, 0);
    //Received bytes already present in kernel buffer is copied to our buffer variable
    buffer[bytes] = '\0';
    //String terminator; recv() returns number of bytes copied
    printf("%s\n",buffer);

    close(clientfd);
    close(listenfd);
    //close both listening socket and client connection socket
    return 0;
}


/*

Error handling is still yet to be implemented for inet_pton() and connect()


*/