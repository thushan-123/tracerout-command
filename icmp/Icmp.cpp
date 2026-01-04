#include <iostream>
#include <string>
#include <array>
#include <cstddef>
#include <cstdint>

class ICMP {
    public:
        std::byte type{};  // 1 byte
        std::byte code{};  // 1 byte
        uint16_t checksum;  // 2 byte.   16bit checksum
        uint16_t identifier{};  //  
        std::array<std::byte, 56> payload{};

        // std::array<std::byte, 64>   build () {
        //     return type + code + checksum + identifier[:2]+ payload[:56]
        // }


};