#include <stdio.h>
#include <sys/ioctl.h>
#include <string>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <arpa/inet.h>

using namespace std;

#define print_log(fmt, __arg__...) fprintf(stderr, fmt "\n", ##__arg__)

void ifname_get_ipaddr (const string &if_name, string &addr)
{
    addr.clear ();
    int sockfd;
    if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
        throw runtime_error ("socket error");

    struct ifconf ifc;
    struct ifreq *ifr;
    struct sockaddr_in *sinptr;
    char buf[2048], addrstr[INET_ADDRSTRLEN];
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_req = (struct ifreq *) buf;
    // SIOCGIFCONF defined in sockios
    if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0)
        throw runtime_error ("ioctl SIOCGIFCONF error");

    for (char *ptr = buf; ptr < buf + ifc.ifc_len; ) {
        ifr = (struct ifreq *) ptr;
        ptr += sizeof(ifr->ifr_name) + sizeof(struct sockaddr);
        if (ifr->ifr_addr.sa_family == AF_INET) {
            sinptr = (struct sockaddr_in *) &ifr->ifr_addr;
            if (if_name == ifr->ifr_name)
                addr = inet_ntop(AF_INET, &sinptr->sin_addr, addrstr, sizeof(addrstr));
        }
    }

    if (addr.empty ())
        throw runtime_error ("bad ifname");
}

int main (int argc, char ** argv)
{
    string if_name (argc == 1 ? "eth0" : argv[1]);
    print_log ("interface name: %s", if_name.c_str ());

    string addr ("");
    try {
        ifname_get_ipaddr (if_name, addr);
        print_log ("%s\t%s", if_name.c_str (), addr.c_str ());
    } catch (const runtime_error &ex) {
        print_log ("catch exception: %s", ex.what ());
    }

    return 0;
}
