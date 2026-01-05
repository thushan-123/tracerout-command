#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h> 
#include <netinet/udp.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <chrono>

#define MAX_HOPS 64
#define TIME_OUT 3
#define BASE_DST_PORT 33434

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <host>\n";
        return 1;
    }

    std::cout << "Traceroute command clone - Developed by Thush \n" << std::endl;

    //resolve host
    hostent* host = gethostbyname(argv[1]);
    if (!host) {
        std::cerr << "Cannot resolve host\n";
        return 1;
    }

    sockaddr_in dest{};
    dest.sin_family = AF_INET;
    memcpy(&dest.sin_addr, host->h_addr, host->h_length);

    char target_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &dest.sin_addr, target_ip, sizeof(target_ip));
    std::cout << "Traceroute to " << argv[1] << " (" << target_ip << "), "
              << MAX_HOPS << " max hops\n\n";

    
    int icmp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (icmp_sock < 0) { perror("icmp socket"); return 1; }

    timeval timeout{};
    timeout.tv_sec = TIME_OUT;
    setsockopt(icmp_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    for (int ttl = 1; ttl <= MAX_HOPS; ttl++) {
        // UDP socket 
        int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (udp_sock < 0) { perror("udp socket"); return 1; }

        //ttl
        setsockopt(udp_sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

        
        int dst_port = BASE_DST_PORT + ttl;
        dest.sin_port = htons(dst_port);

        auto start = std::chrono::high_resolution_clock::now();

        //send UDP packet
        sendto(udp_sock, "", 0, 0, (sockaddr*)&dest, sizeof(dest));
        close(udp_sock);  

        // Receive ICMP reply
        char recvbuf[1024];
        sockaddr_in reply{};
        socklen_t len = sizeof(reply);

        int n = recvfrom(icmp_sock, recvbuf, sizeof(recvbuf), 0,
                         (sockaddr*)&reply, &len);

        auto end = std::chrono::high_resolution_clock::now();
        double rtt = std::chrono::duration<double, std::milli>(end - start).count();

        std::cout << ttl << "  ";

        if (n < 0) {
            std::cout << "*\n";
            continue;
        }

        char hop_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &reply.sin_addr, hop_ip, sizeof(hop_ip));
        std::cout << hop_ip << "  " << rtt << " ms";

    
        struct ip* ip_hdr = (struct ip*)recvbuf;
        int ip_hdr_len = ip_hdr->ip_hl * 4;
        
        struct icmp* icmp_header = (struct icmp*)(recvbuf + ip_hdr_len);

        
        if (icmp_header->icmp_type == ICMP_UNREACH && 
            icmp_header->icmp_code == ICMP_UNREACH_PORT) {

            std::cout << "  (destination reached)";
            std::cout << "\n";
            break;
        }

        std::cout << "\n";
    }

    close(icmp_sock);
    return 0;
}

