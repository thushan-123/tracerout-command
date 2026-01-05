#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <chrono>

#include "icmp/icmp.h"

#define MAX_HOPS 64
#define TIME_OUT 2

int main (int argc, char *argv[]) {

    // check argument count
    if ( argc != 2 ){
        std::cout<< "usage " << argv[0] << " < host > " << std::endl;
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

    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
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
        ICMP icmp{};

        icmp.type = 0x08;
        icmp.code = 0x00;
        icmp.un.echo.id = getpid();
        icmp.un.echo.sequence = ttl;
        icmp.payload.fill(0xAA);
        icmp.checksum = 0;

        auto packet = icmp.build();

        icmp.checksum = icmp.icmpChecksum(reinterpret_cast<const u_int16_t *>(packet.data()), packet.size());

        packet = icmp.build();

        auto start = std::chrono::high_resolution_clock::now();

        sendto(sock, packet.data() , packet.size(), 0, (sockaddr * ) &dest, sizeof(dest));

        char recvbuffer[1024];
        sockaddr_in reply{};
        socklen_t len = sizeof(reply);

        int n = recvfrom(sock , recvbuffer, sizeof(recvbuffer), 0, (sockaddr*)&reply , &len);

        auto end = std::chrono::high_resolution_clock::now();

        if (n < 0) {
            std::cout << ttl << "  *\n";
            continue;
        }

        auto rtt = std::chrono::duration<double, std::milli>(end - start).count();

        char hop_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &reply.sin_addr, hop_ip, sizeof(hop_ip));

        std::cout << ttl << "  " << hop_ip
                  << "  " << rtt << " ms\n";

        struct ip *ip_hdr = (struct ip*)recvbuffer;
        int ip_header_len = ip_hdr->ip_hl * 4;

        struct icmp *icmp_hdr = (struct icmp *)(recvbuffer + ip_header_len);
        if (icmp_hdr->icmp_type == ICMP_ECHOREPLY) {
            break;
        }



    }
    close(sock);

    return 0;


}