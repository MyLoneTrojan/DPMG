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
            if (tx_p[n].getBase() == nullptr) {
                err::Error param;
                param.setFile(__FILE__).setLine(__LINE__).setText("Error: loading tx_p");
                return param;
            }
        }

        // set textures into sprites
        for (int n = 0; n < spr_p.size(); ++n)
            spr_p[n].setTexture( tx_p[n].getBaseRef() );

        // position sprites
        spr_p[0].setPosition(  0,   0);

        spr_p[1].setPosition(1000, 500);

        spr_p[2].setPosition(310, 500);
        spr_p[2].setScale(.5f, .5f);

        return err::Error();
    }

    void room_gui_close () {
        spr_p.clear();
        spr_p.shrink_to_fit();

        for (int n = 0; n < TX_P_SIZE; ++n)
            tx_p[n].clear();
    }

    inline void room (sf::Window& window) {
        gbl::to_draw_p.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            room_gui_close();
            gbl::gl_back();
            return;
        }

        sf::Vector2i mosPos = sf::Mouse::getPosition(window);

        // check if hovering (skips 0 b/c it's background)
        for (int n = 1; n < spr_p.size(); ++n) {
            if (spr_p[n].getGlobalBounds().contains(mosPos.x, mosPos.y)) {
                spr_p[n].setColor(sf::Color(100,100,100,100));

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    switch (n)
                    {
                    case 2:
                        std::cout << "Sleep()";
                        break;
                    case 1:
                        std::cout << "Comp()";
                        comp::comp_gui_load();
                        gbl::game_level = comp::comp;
                        break;
                    }
                }
            } else {
                spr_p[n].setColor(sf::Color::White);
            }
        }

        for (sf::Drawable& obj : spr_p)
            gbl::to_draw_p.push_back(&obj);
    }
}

#endif // ROOM_H_INCLUDED
