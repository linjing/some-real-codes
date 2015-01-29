#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <string>
using namespace std;

static int init_listen_fd (int port)
{
    int listen_fd = -1;
    int reuseaddr = 1;
    int ret = 0;
    struct sockaddr_in sa;

    listen_fd = socket (AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        cerr << "init server failed when call socket. " << endl;
        return -1;
    }

    ret = setsockopt (listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
            sizeof (reuseaddr));
    if (ret == -1) {
        cerr << "init server failed when call setsockopt." << endl;
        close (listen_fd);
        return -1;
    }
    memset (sa.sin_zero, 0, sizeof (sa.sin_zero));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl (INADDR_ANY);
    sa.sin_port = htons (port);

    ret = bind (listen_fd, (struct sockaddr *) &sa, sizeof (struct sockaddr_in));
    if (ret == -1) {
        cerr << "init server failed when call bind." << endl;
        close (listen_fd);
        return -1;
    }

    ret = listen (listen_fd, 5);
    if (ret == -1) {
        cerr << "init server failed when call listen." << endl;
        close (listen_fd);
        return -1;
    }

    return listen_fd;
}
