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

    sockaddr_in socket{};
    socket.sin_family = AF_INET;



    return 0;


}