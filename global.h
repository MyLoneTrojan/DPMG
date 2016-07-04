#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/// STD
#include <random>
#include <functional>

/// SFML

/// PROJECT
/*--- purposely empty ---*/

namespace gbl {
    // for consistent, predictable 'random' numbers
    std::default_random_engine rand_eng;

    // current meta_point in the game (independent sections of the game, i.e. location)
    std::function<void()> game_level;

    // unwind to end
    bool end;
}

#endif
