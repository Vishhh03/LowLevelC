#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //socket() - kernel allocates communication endpoint
    //socket fileDescriptor = AF_INET-IPV4, SOCK_STREAM-TCP, 0-Protocol
    if (sockfd < 0){
        perror("socket");
        return 1;
    }
    //fileDescriptor - integer used by kernel to track the socket/open resource; a handle for kernel
    //There are other socket types than SOCK_DGRAM ,SOCK_RAW, SOCK_SEQPACKET, SOCK_RDM
    //Transport protocol is usually kept 0 wherein the kernel chooses the default based on socket type

    struct sockaddr_in server;
    // sockaddr_in defined in <netinet/in.h> - used to store IPV4 address
    memset(&server, 0, sizeof(server));
    //memory set - fills a block of memory with same byte - fills with 0 in all fields including padding in this case
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);    
    //htons - converts value: network protocol expects big endians, where most pcs use little endians.

    //inet_pton and connect return 1 if success, 0 - invalid IP string or -1 if error

    inet_pton(AF_INET,
    "127.0.0.1",
    &server.sin_addr);
    //converts IP to 4 bytes and saves it in server.sin_addr ; p-to-n -> presentation to numeric

    connect(sockfd,
    (struct sockaddr *)&server,
    sizeof(server)
    );
    //establish connection to server/another computer ; RETURN -1 if no server in sockaddr found

    close(sockfd);
    //release the file descriptor, free socket resource, close connectoin
    return 0;
}