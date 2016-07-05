
/// STD
#include <iostream>
#include <string>

/// SFML
#include <SFML/Graphics.hpp>

/// PROJECT
#include "attri.h"
#include "comp.h"
#include "file_paths.h"

void gbl::gl_back () {
    end = true;
}

int main () {

        //visual window
    sf::RenderWindow window (sf::VideoMode(1366, 768), "DPMG", sf::Style::Titlebar | sf::Style::Close);

        ///////////////////
    /// TIME STEP variables
    sf::Clock game_clock;

    sf::Time frame_dt     = sf::Time::Zero;
    sf::Time max_frame_dt = sf::milliseconds(100);

    sf::Time time_step    = sf::milliseconds( 30);
    /////////////////////////

    gbl::game_level = room::room;

    // game loop
    while (!gbl::end && window.isOpen()) {

        frame_dt += game_clock.restart(); // add missed time

        if (frame_dt < max_frame_dt)      // check against max
            frame_dt = max_frame_dt;

        /// GAME LOOP
        for (; frame_dt >= time_step; frame_dt -= time_step) {
            attr::print_attr();
            gbl::game_level();
        }

        // intermediate draw?

        /// handle events
        for (sf::Event event; window.pollEvent(event);) {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        /// DISPLAY
        window.clear();

        // draw queue
        for (sf::Drawable* obj_p : gbl::to_draw_p)
            window.draw(*obj_p);

        window.display();
    }

    return 0;
}
