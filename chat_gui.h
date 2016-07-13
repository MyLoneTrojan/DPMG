#ifndef CHAT_GUI_H_INCLUDED
#define CHAT_GUI_H_INCLUDED

namespace chx {

    void chat_gui_start () {}

    void chat_gui_close () {}

    void chat_gui () {

        // if close chat
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            chat_gui_close();
            return;
        }
    }
}

#endif // CHAT_GUI_H_INCLUDED
