#include <iostream>

int main (int argc, char *argv[]) {

    // check argument count
    if ( argc != 2 ){
        std::cerr << "usage " << argv[0] << " host \n";
        return 1;
    }

    return 0;
}