#ifndef CHAT_GUI_H_INCLUDED
#define CHAT_GUI_H_INCLUDED

/// STD


/// SFML
#include <SFML/Graphics.hpp>

/// PROJECT
#include "Global.h"
#include "Comp.h"

namespace chx {

    sf::RectangleShape*     con_bg; //5
    std::vector<sf::Text>   text_p;
    //sf::Sprite*             spr_p;
    std::vector<sf::Sprite> avi;

    void chat_gui_start () {}

    void chat_gui_close () {}

    void chat_gui () {
        gbl::to_draw_p.clear();
        //comp::draw();

        // if close chat
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            chat_gui_close();
            return;
        }
    }
}

#endif // CHAT_GUI_H_INCLUDED
