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


    std::vector<sf::Sprite> spr_p;
    txmg::TexPtr tx_p [TX_P_SIZE];

    err::Error room_gui_load () {
        spr_p.resize(3);

            // load sf::textures
        tx_p[0] = { txmg::makeTex( fp::room_i ) };
        tx_p[1] = { txmg::makeTex( fp::desk_i ) };
        tx_p[2] = { txmg::makeTex( fp::bed_i  ) };

            // check for error
        for (int n = 0; n < TX_P_SIZE; ++n) {
            if ((sf::Texture*)tx_p[n] == nullptr) {
                err::Error param;
                param.setFile(__FILE__).setLine(__LINE__).setText("Error: loading tx_p");
                return param;
            }
        }

        // set textures into sprites
        for (int n = 0; n < spr_p.size(); ++n) {
            spr_p[n].setTexture(sf::Texture*(tx_p[n]));
        }
    }

    void room_gui_close () {
    }

    void room () {

    }
}

#endif // ROOM_H_INCLUDED
