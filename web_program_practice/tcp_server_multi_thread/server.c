#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXUSER 100

int cmdline_arg_resolve(int argc, char *argv[], in_port_t *port) {
    char opt = 0;

    if (argc != 3) {
        return -1;
    }

    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt)
        {
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

int create_server_socket(in_port_t port) {
    int sockfd = -1;
    struct sockaddr_in server_addr = {0};

    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(sockfd);
        return -1;
    }

    if (listen(sockfd, 20) < 0) {
        perror("listen");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

void *worder(void *arg) {
    int fd = *((int *)arg);
    printf("fd : %d\n", fd);

    while(1) {
        char buff[2048] = {0};
        size_t recv_len = recv(fd, buff, sizeof(buff), 0);
        if (recv_len <= 0) {
            close(fd);
            break;
        } else {
            send(fd, buff, strlen(buff), 0);
        }
    }

    printf("fd : %d is closed\n", fd);
    return NULL;
}

void run_server(int sockfd) {
    int all_users[MAXUSER] = {0};

    while (1) {
        pthread_t tmp_tid;
        int new_fd = -1;
        struct sockaddr_in client_addr = {0};
        socklen_t addr_len = sizeof(client_addr);

        if ((new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
            perror("accept");
            continue;
        }
        if (new_fd > MAXUSER) {
            fprintf(stderr, "connection full");
            close(new_fd);
            continue;
        }

        all_users[new_fd] = new_fd;
        pthread_create(&tmp_tid, NULL, worder, (void *)&all_users[new_fd]);
    }

    return;
}

int main(int argc, char *argv[]) {
    int sockfd = 0;
    in_port_t server_port = 0;

    if (cmdline_arg_resolve(argc, argv, &server_port) < 0) {
        fprintf(stderr, "Usage: %s -p port\n", argv[0]);
        exit(1);
    }

    if ((sockfd = create_server_socket(server_port)) < 0) {
        fprintf(stderr, "create server socket error\n");
        exit(1);
    }

    run_server(sockfd);

    if (sockfd > 0) {
        close(sockfd);
    }
    return 0;
}