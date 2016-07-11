#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/// STD
#include <string>
#include <random>
#include <vector>
#include <sstream>
#include <functional>

/// SFML
#include <SFML/Graphics.hpp>

/// PROJECT
#include "Error.h"  // for err::Error reports
#include "texture_manager.h"    // for garbage collection and draw queue
#include "level_func.h"

namespace gbl {
    // for consistent, predictable 'random' numbers
    std::default_random_engine rand_eng;

    sf::Vector2u win_size = {1600, 869};
    // current meta_point in the game (independent sections of the game, i.e. location)
    std::function<void(sf::Window&)> game_level;

    // event_handler so game_level can access and handle events uniquely
    std::function<void(sf::Event&)> event_handle;

    // unwind to end
    bool end;

    template <class ...T>
    void do_nothing(T&&...) {};

      ////////////////////////////
    // should be defined in main
    // sets game_level to previous state
    void gl_back ();

    std::vector<sf::Drawable*> to_draw_p;

    /// Supplement b/c windows gcc lacks std::to_string
    template <class T>
    std::string to_string (T&& num) {
        std::string param;
        std::stringstream sstream;
        sstream << num;
        sstream >> param;
        return param;
    }
}

#endif
