#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define SERVER_PORT 20000
#define SERVER_IP_STR "0.0.0.0"

#define MAX_DATA_SIZE 4096
#define MAX_USER 512
#define EPOLLSIZE 15

typedef struct _user_data {
    char data[MAX_DATA_SIZE];
    int user_sockfd;
    struct in_addr user_ip;
    in_port_t user_port;
} UserData;

int create_server_socket(uint16_t port, const char *ip) {
    int sockfd = 0;
    struct sockaddr_in server_addr = {0};

    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
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

int check_end(char *str, ssize_t n) {
    for (int i = 0; i < n; ++i) {
        if (str[i] == '\n') return 1;
    }
    return 0;
}

void process_user_date(char *str) {
    int Atoa_offset = 'A' - 'a';
    int atoA_offset = 'a' - 'A';
    for (int i = 0; str[i] && i < MAX_DATA_SIZE; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= atoA_offset;
        } else if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] -= Atoa_offset;
        }
    }
    return;
}

int run_service(int sockfd) {
    int epollfd = 0;
    int ret = 0;
    int nfds = 0;
    struct epoll_event ev, events[EPOLLSIZE];
    UserData users[MAX_USER] = {0};
    struct sockaddr_in client = {0};
    int new_fd = 0;

    if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create");
        ret = -1;
        goto out;
    }
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) {
        perror("epoll_ctl");
        ret = -1;
        goto out;
    }

    while (1) {
        if ((nfds = epoll_wait(epollfd, events, EPOLLSIZE, -1)) < 0) {
            perror("epoll_wait");
            ret = -1;
            goto out;
        }
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == sockfd) {
                socklen_t len = sizeof(client);
                if ((new_fd = accept(sockfd, (struct sockaddr *)&client, &len)) < 0) {
                    perror("accept");
                    ret = -1;
                    goto out;
                }
                users[new_fd].user_sockfd = new_fd;
                users[new_fd].user_ip = client.sin_addr;
                users[new_fd].user_port = ntohs(client.sin_port);
                printf("Recv from : [%s] : [%u]\n", inet_ntoa(users[new_fd].user_ip), users[new_fd].user_port);
                ev.events = EPOLLIN;
                ev.data.fd = new_fd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, new_fd, &ev) < 0) {
                    perror("epoll_ctl");
                    ret = -1;
                    goto out;
                }
            } else {
                char tmp_buffer[MAX_DATA_SIZE] = {0};
                int tmp_fd = events[i].data.fd;
                ssize_t n = recv(tmp_fd, tmp_buffer, sizeof(tmp_buffer), 0);
                if (n <= 0) {
                    if (epoll_ctl(epollfd, EPOLL_CTL_DEL, tmp_fd, NULL) < 0) {
                        perror("epoll_ctl");
                        ret = -1;
                        goto out;
                    }
                    printf("client [%s] : [%u] disconnected\n", inet_ntoa(users[tmp_fd].user_ip), users[tmp_fd].user_port);
                    close(tmp_fd);
                }
                if (n >= MAX_DATA_SIZE) {
                    printf("long message, ignore!!!\n");
                    continue;
                }
                strncat(users[tmp_fd].data, tmp_buffer, n);
                if (check_end(tmp_buffer, n)) {
                    process_user_date(users[tmp_fd].data);
                    send(tmp_fd, users[tmp_fd].data, strlen(users[tmp_fd].data), 0);
                    memset(users[tmp_fd].data, 0, sizeof(users[tmp_fd].data));
                }
            }
        }
    }

out:
    if (epollfd > 0) {
        close(epollfd);
    }
    return ret; 
}

int main() {
    int sockfd = 0;

    if ((sockfd = create_server_socket(SERVER_PORT, SERVER_IP_STR)) < 0) {
        fprintf(stderr, "create_server_socket error\n");
        exit(1);
    }

    if (run_service(sockfd) < 0) {
        fprintf(stderr, "run_service failed\n");
        exit(1);
    }

    if (sockfd > 0) {
        close(sockfd);
    }
    return 0;
}