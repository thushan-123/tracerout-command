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
        std::array<std::byte , 64> build () const {

            std::array<std::byte, 64> packet{};

            packet[0] = type;
            packet[1] = code;

            // checksum
            packet[2] = std::byte(checksum >> 8);
            packet[3] = std::byte(checksum & 0xFF);

            // identifier
            packet[4] = std::byte(identifier >> 8);
            packet[5] = std::byte(identifier & 0xFF);

            // seq
            packet[6] = std::byte{0};
            packet[7] = std::byte{0};

            // payload
            for(int i =0 ; i < payload.size(); i++){
                packet[8 + i] = payload[i];
            }
        }


};