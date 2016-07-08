#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/// STD
#include <random>
#include <vector>
#include <functional>

/// SFML
#include <SFML/Graphics.hpp>

/// PROJECT
#include "Error.h"  // for err::Error reports
#include "texture_manager.h"    // for garbage collection and draw queue

namespace gbl {
    // for consistent, predictable 'random' numbers
    std::default_random_engine rand_eng;

    // current meta_point in the game (independent sections of the game, i.e. location)
    std::function<void(sf::Window&)> game_level;

    // event_handler so game_level can access and handle events uniquely
    std::function<void(sf::Event&)> event_handle;

    // unwind to end
    bool end;

      ////////////////////////////
    // should be defined in main
    // sets game_level to previous state
    void gl_back ();

    std::vector<sf::Drawable*> to_draw_p;
}

#endif
