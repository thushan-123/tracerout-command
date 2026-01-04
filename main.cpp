#include <iostream>

int main (int argc, char *argv[]) {

    // check argument count
    if ( argc != 2 ){
        std::cout<< "usage " << argv[0] << " host " << std::endl;
        return 1;
    }

    return 0;
}