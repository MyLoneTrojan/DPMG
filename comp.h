#ifndef COMP_H
#define COMP_H

/// STD
#include <iostream>
#include <sstream>
#include <string>

/// SFML
#include <SFML/Graphics.hpp>

/// PROJECT
#include "global.h"
#include "file_paths.h"

namespace comp {

    /***
     * Activities
     **
     * Chat, Game (easy or hard) [with friends?],
     * Learn, Seek help (needs prerequisite)
     ***
     ****/

    namespace min {
        const float CHAT_T   = 10.f;
        const float GAME_E_T = 20.f;
        const float GAME_H_T = 40.f;
        const float LEARN_T  = 30.f;
    }

    sf::String          input;
    sf::RectangleShape* box_;
    sf::Text*           text_;
    sf::Font*           font;

    void getText (sf::Event& event) {
        if (event.type != sf::Event::TextEntered && *input.end() != '\n')
            return;

        if ( (event.text.unicode >= 0x30 && event.text.unicode >= 0x39) || event.text.unicode == 0x2E )
            input += sf::String(event.text.unicode);
        else if (event.text.unicode == '\b')
            input.erase( input.getSize()-1 );
    }

    void chat (float dt) {
        using namespace attr;

        social  -= 10 * dt/30;
        mood    += 10 * dt/30;
        clarity +=  5 * dt/30;

        if (social < 0) { // social is negative, so adding will still decrease value
            energy += social / 3;
            motiv  += social / 4;
        }
        energy_adv(dt);
        motiv_adv(dt);

        time_adv(dt);
    }

    void game_easy (float dt) {
        using namespace attr;

        mood *= dt * .7;

        social_adv(dt);
        motiv_adv(dt);

        time_adv(dt);
    }
    void game_hard (float dt) {
        game_easy(dt);
    }

    void learn (float dt); // add topic as parameter


    void comp_gui_load () {
        box_  = new sf::RectangleShape;
        text_ = new sf::Text;
        font  = new sf::Font;

        if (!font->loadFromFile(fp::framd_font)) {
            gbl::end = true;
            return;
        }

        box_->setPosition(800, 500);
        box_->setFillColor(sf::Color::Black);
        box_->setSize(sf::Vector2f(1000, 50));

        text_->setPosition(820, 490);
        text_->setColor(sf::Color::White);
        text_->setFont(*font);
    }

    void comp_gui_close () {
        delete box_;
        delete text_;
        delete font;
    }

    /// MAIN function
    void comp(sf::Window& window) {
        gbl::event_handle = getText;

        text_->setString(input);

        if (*input.end() == '\n') {
            float dt = std::atof(input.toAnsiString().c_str());

            if (dt )
        }

        gbl::to_draw_p.push_back(box_);
        gbl::to_draw_p.push_back(text_);
    }
}
#endif // COMP_H
