#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

void read_data_from_socket(int sock)
{
    static char buf[64];
    while (true) {
        int len = read(sock, buf, sizeof(buf));
        if (len > 0) {
            fwrite(buf, sizeof(char), len, stdout);
            // printf("read data, len = %d\n", len);
        } else if (len == 0) {
            printf("read data, len = 0\n");
            break;
        } else if (len == -1) {
            if (errno != EAGAIN) {
                printf("read data error, rc = %d\n", errno);
            }
            break;
        }
    }
    printf("\nread_data_from_socket finished...\n");
}

int main(int argc, char** argv)
{
    short port     = 8888;
    int   listen_sock = 0;
    int   rc          = 0;

    //
    // TODO: switch to getaddrinfo, and create socket to support both IPV4 and
    // IPV6
    //
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == -1) {
        printf("Could not create socket to listen...\n");
        return -1;
    }

    int optval = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    //
    // bind
    //
    struct sockaddr_in server;
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(port);

    rc = bind(listen_sock, (struct sockaddr*)&server, sizeof(server));

    //
    // listen
    //
    int backlog = 10;
    rc          = listen(listen_sock, backlog);

    //
    // epoll
    //
    static const int   MAX_EVENTS = 10;
    struct epoll_event ev, events[MAX_EVENTS];
    int                epollfd, conn_sock, nfds;

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        return -1;
    }

    ev.events  = EPOLLIN;
    ev.data.fd = listen_sock;
    rc         = epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev);
    if (rc == -1) {
        return -1;
    }

    while (true) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == listen_sock) {
                conn_sock = accept(listen_sock, nullptr, nullptr);
                if (conn_sock == -1) {
                    printf("accept failed...\n");
                    return -1;
                }

                // set conn_sock as non-blocking
                int flags = fcntl(conn_sock, F_GETFL);
                fcntl(conn_sock, F_SETFL, flags | O_NONBLOCK);

                ev.events  = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;
                rc         = epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev);
                if (rc == -1) {
                    printf("epoll_ctl, add conn_sock failed\n");
                    return -1;
                }
            } else {
                // when client is killed, here still receive a EPOLLIN event.
                printf("event = %d\n", events[i].events);
                read_data_from_socket(events[i].data.fd);
            }
        }
    }

    return 0;
}

