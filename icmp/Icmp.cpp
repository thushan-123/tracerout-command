#include <iostream>
#include <string>
#include <array>
#include <cstddef>
#include <cstdint>
#include "icmp.h"

// class ICMP {
//     public:
//         uint8_t type{};  // 1 byte
//         uint8_t code{};  // 1 byte
//         uint16_t checksum;  // 2 byte.   16bit checksum

//         union {
//             struct 
//             {
//                 uint16_t id;
//                 uint16_t sequence;
//             } echo;
            
//         } un;
        

//         uint16_t identifier{};  //  
//         std::array<uint8_t, 56> payload{};

//         // std::array<std::byte, 64>   build () {
//         //     return type + code + checksum + identifier[:2]+ payload[:56]
//         // }

//         u_int16_t icmpChecksum (const u_int16_t* data , size_t length) {

//             u_int16_t sum = 0;

//             // sum 16 bits
//             while (length > 1) {
//                 sum += (data[0] << 8) | data[1];
//                 data += 2;
//                 length -= 2;
//             }

//             if (length == 1){
//                 sum +=(data[0] << 8);
//             }

//             while (sum >> 16) {
//                 sum = (sum & 0xFFFF) + (sum >> 16);
//             }

//             return static_cast<u_int16_t>(~sum);
//         }


//         std::array<std::byte , 64> build () const {

//             std::array<uint8_t, 64> packet{};
//             size_t k = 0;
            
//             packet[k++] = type;
//             packet[k++] = code;

//             // checksum
//             packet[k++] = checksum >> 8;
//             packet[k++] = checksum & 0xFF;

//             // identifier
//             packet[k++] = un.echo.id >> 8;
//             packet[k++] = un.echo.id & 0xFF;

//             // seq
//             packet[k++] = un.echo.sequence >> 8;
//             packet[k++] = un.echo.sequence & 0xFF;

//             for (auto b : payload) {
//                 packet[k++] = b;
//             }
//         }


// };


u_int16_t ICMP::icmpChecksum (const u_int16_t* data , size_t length) {

    u_int16_t sum = 0;

    // sum 16 bits
    while (length > 1) {
        sum += (data[0] << 8) | data[1];
        data += 2;
        length -= 2;
    }

    if (length == 1){
        sum +=(data[0] << 8);
    }

    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    return static_cast<u_int16_t>(~sum);
}


std::array<std::byte , 64> ICMP::build () const {

    std::array<uint8_t, 64> packet{};
    size_t k = 0;
            
    packet[k++] = type;
    packet[k++] = code;

    // checksum
    packet[k++] = checksum >> 8;
    packet[k++] = checksum & 0xFF;

    // identifier
    packet[k++] = un.echo.id >> 8;
    packet[k++] = un.echo.id & 0xFF;

    // seq
    packet[k++] = un.echo.sequence >> 8;
    packet[k++] = un.echo.sequence & 0xFF;

    for (auto b : payload) {
        packet[k++] = b;
    }
}