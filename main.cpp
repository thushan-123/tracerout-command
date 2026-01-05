#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>


#define MAX_HOPS 64
#define TIME_OUT 2

int main (int argc, char *argv[]) {

    // check argument count
    if ( argc != 2 ){
        std::cout<< "usage " << argv[0] << " host " << std::endl;
        return 1;
    }

    // resolve host nam
    struct hostent *host = gethostbyname(argv[1]);
    if (host == NULL) {
        std::cout << "can't resolve domain name" << std::endl;
        return 1;
    }

    sockaddr_in dest{};
    dest.sin_family = AF_INET;
    memcpy(&dest.sin_addr, host->h_addr, host->h_length);

    char  target_ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &dest.sin_addr, target_ip, sizeof(target_ip));

    std::cout << "Traceroute to " << argv[1] << "(" << target_ip << ") " << "64 max hops" <<std::endl;
    std::cout << std::endl;

    int sock = socket(AF_INET6, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0){
        std::cout<< "socket ERROR" << std::endl;
        return 1;
    }

    //time out
    timeval timeout{};
    timeout.tv_sec = TIME_OUT;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));


    for (int ttl = 1; ttl <= MAX_HOPS; ttl++){
        setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

        // create icmp packet
        
    }


    return 0;


}