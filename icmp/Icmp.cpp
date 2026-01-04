#include <iostream>
#include <string>

class ICMP {
    public:
        std::byte type;
        std::byte code;
        std::byte checksum;
        std::byte identifier;
};