
/// STD
#include <iostream>
#include <string>

/// SFML
//#include <SFML/Graphics.hpp>

/// PROJECT
#include "attri.h"
#include "comp.h"

int main () {

    std::cout << "Hello World!\n\n";

    // game loop?
    while (true) {
        std::string input;

        print_attr();
        print_choices();
    }

    return 0;
}
