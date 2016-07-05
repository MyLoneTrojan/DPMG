#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

/// STD
#include <vector>

/// SFML
#include <SFML/Graphics.hpp>

/// PROJECT
#include "global.h"
#include "texture_manager.h"
#include "file_paths.h"

namespace room {

    const std::size_t TX_P_SIZE = 3;
    const std::size_t ROOM_POS  = 0,
                      DESK_POS  = 1,
                       BED_POS  = 2;


    sf::Sprite* spr_p;
    txmg::TexPtr tx_p [TX_P_SIZE];

    err::Error room_gui_load () {
        spr_p = new sf::Sprite [3];

        tx_p[0] = { txmg::makeTex( fp::room_i ) };
        tx_p[1] = { txmg::makeTex( fp::desk_i ) };
        tx_p[2] = { txmg::makeTex( fp::bed_i  ) };
    }

    void room_gui_close () {
    }

    void room () {

    }
}

#endif // ROOM_H_INCLUDED
