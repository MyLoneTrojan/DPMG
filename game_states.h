#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

/// STD

/// SFML
#include <SFML/Graphics.hpp>

/// Project


namespace gs {
    struct game_state {
        virtual void update (sf::Window&) =0;

        virtual void event (sf::Event&) =0;
    };

    std::vector<std::shared_ptr<game_state>> game_states;
}


#endif // GAME_STATE_H_INCLUDED
