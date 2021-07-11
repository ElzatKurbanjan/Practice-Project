#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct UserInfo {
    char name[50];
    char phone[20];
} UserInfo;

int cmdline_arg_resolve(int argc, char *argv[], in_addr_t *ip, in_port_t *port) {
    char opt = 0;

    if (argc != 5) {
        return -1;
    }

    while ((opt = getopt(argc, argv, "a:p:")) != -1) {
        switch (opt)
        {
            case 'a': {
                printf("ip : %s\n", optarg);
                *ip = inet_addr(optarg);
            } break;
            case 'p' : {
                printf("port : %s\n", optarg);
                *port = htons((uint32_t)atoi(optarg));
            } break;
            default : 
                return -1;
        }
    }

    return 0;
}

int connect_to_server(in_addr_t ip, in_port_t port) {
    int sockfd = -1;
    struct sockaddr_in server;

    memset(&server, 0, sizeof(struct sockaddr_in));

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = ip;
    server.sin_port = port;

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

void swap_msg(int sockfd) {
    ssize_t recv_len = 0;

    while (1) {
        char buff[512] = {0};
        recv_len = recv(sockfd, buff, sizeof(buff), 0);
        printf("buff : %s\n", buff);
        if (recv_len <= 0) {
            break;
        }
        int type = atoi(buff);
        memset(buff, 0, sizeof(buff));
        switch (type) {
            case 1 : {
                strcpy(buff, "151xxxxxxxx");
                send(sockfd, buff, sizeof(buff), 0);
            } break;
            case 2 : {
                strcpy(buff, "Elzat Kurbanjan");
                send(sockfd, buff, sizeof(buff), 0);  
            } break;
            case 3 : {
                UserInfo tmp = {0};
                strcpy(tmp.name, "Elzat Kurbanjan");
                strcpy(tmp.phone, "151xxxxxxxx");
                send(sockfd, (void *)&tmp, sizeof(tmp), 0);
            } break;
            case 4 :
                printf("4\n");
            default :
                printf("default\n");
                return ;
        }
    }

    return ;
}

int main(int argc, char *argv[]) {
    int sockfd = -1;
    in_addr_t server_ip = 0;
    in_port_t server_port = 0;

    if (cmdline_arg_resolve(argc, argv, &server_ip, &server_port) < 0) {
        fprintf(stderr, "Usage: %s -a ip -p port\n", argv[0]);
        exit(1);
    }

    if ((sockfd = connect_to_server(server_ip, server_port)) < 0) {
        fprintf(stderr, "connection error\n");
        exit(1);
    }

    printf("connection success\n");

    swap_msg(sockfd);

    if (sockfd > 0) {
        close(sockfd);
        sockfd = -1;
    }
    return 0;
}