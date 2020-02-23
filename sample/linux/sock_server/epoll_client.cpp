#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int sock = -1;
    int rc   = 0;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr      = NULL;
    hints.ai_next      = NULL;
    hints.ai_family    = AF_UNSPEC; /* Allows IPv4 or IPv6 */
    hints.ai_socktype  = SOCK_STREAM;

    struct addrinfo *result, *rp;
    rc = getaddrinfo("127.0.0.1", "8888", &hints, &result);
    if (rc != 0) {
        errno = ENOSYS;
        return -1;
    }

    /* Walk through returned list until we find an address structure
       that can be used to successfully connect a socket */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sock == -1)
            continue; /* On error, try next address */

        if (connect(sock, rp->ai_addr, rp->ai_addrlen) != -1)
            break; /* Success */

        /* Connect failed: close this socket and try next address */

        close(sock);
        sock = -1;
    }

    freeaddrinfo(result);

    if (sock == -1) {
        printf("connect failed, rc = %d\n", errno);
        return -1;
    }

    // write to socket
    static const int BUF_SIZE = 64;
    char             buf[BUF_SIZE];
    while (true) {
        char* p = fgets(buf, sizeof(buf), stdin);
        if (p == nullptr) {
            printf("fgets return null\n");
            close(sock);
            break;
        }
        write(sock, buf, strlen(buf));
    }

    return 0;
}

