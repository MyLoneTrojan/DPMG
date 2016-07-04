
/// STD
#include <iostream>
#include <string>

/// SFML
//#include <SFML/Graphics.hpp>

/// MULTIPLE CONSOLE WINDOWS
#include "C:\Users\222222day\cpp\Source\ExtraConsole\server.h"

/// PROJECT
#include "attri.h"
#include "comp.h"

void gbl::gl_back () {
    end = true;
}

int main () {

    CConsoleLogger console_log;
    console_log.create("Hello World!");

    std::cout << "Hello World!\n\n";

    gbl::game_level = comp::comp;

    // game loop
    while (!gbl::end) {
        std::string input;

        console_log.printf(attr::print_attr());
        gbl::game_level();
    }

    return 0;
}
