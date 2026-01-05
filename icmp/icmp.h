#ifndef ICMP_H
#define ICMP_H

#include <array>
#include <cstddef>
#include <cstdint>

class ICMP {
public:
    uint8_t type{};        // 1 byte
    uint8_t code{};        // 1 byte
    uint16_t checksum{};   // 2 bytes

    union {
        struct {
            uint16_t id;
            uint16_t sequence;
        } echo;
    } un{};

    std::array<uint8_t, 56> payload{};

    u_int16_t icmpChecksum(const u_int16_t *data, size_t length);

    
    std::array<uint8_t, 64> build() const;

    
};

#endif 
