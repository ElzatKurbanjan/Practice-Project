#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

int connect_to_server(const char *ip, uint16_t port) {
    int sockfd = -1;
    struct sockaddr_in server;

    memset(&server, 0, sizeof(struct sockaddr_in));

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int main(int argc, char *argv[]) {
    int sockfd = -1;
    char buf[4096] = {0};

    if ((sockfd = connect_to_server("0.0.0.0", 20000)) < 0) {
        fprintf(stderr, "connection error\n");
        exit(1);
    }

    printf("connection success\n");

    while(1) {
        scanf("%s", buf);
        if(strcmp(buf, "end") == 0) {
            printf("will send end\n");
            break;
        }
        send(sockfd, buf, strlen(buf), 0);
        memset(buf, 0, sizeof(buf));
    }
    send(sockfd, "\n", 1, 0);
    
    memset(buf, 0, sizeof(buf));
    recv(sockfd, buf, sizeof(buf), 0);
    printf("recv from server: %s", buf);

    if (sockfd > 0) {
        close(sockfd);
        sockfd = -1;
    }
    return 0;
}