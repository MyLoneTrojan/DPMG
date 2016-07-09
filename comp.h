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

    float dt = -1;
    char func = 0;

    sf::String          input;
    sf::String          input_hint;
    sf::RectangleShape* box_;
    sf::Text*           text_;
    sf::Font*           font;
    std::vector<sf::Sprite> spr_v;
    std::vector<txmg::TexPtr> tx_v;

    void getText_handler (sf::Event& event) {
        if (event.type != sf::Event::TextEntered)
            return;

        // clear from previous error
        if (input == "bad input")
            input.clear();

        std::cout << "input\n";
        char in = char(event.text.unicode);

        if ( (in >= '0' && in <= '9') || in == '.' )
            input += sf::String(event.text.unicode);
        else if (in == '\b')
            input.erase( input.getSize()-1 );

        if (in == '\r') {
            dt = std::atof(input.toAnsiString().c_str());
            input = "bad input"; // communicate to user
            std::cout << "Submit\n";
        }

        text_->setString(input);
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
        spr_v.resize(4);
        tx_v.resize(4);

        box_  = new sf::RectangleShape;
        text_ = new sf::Text;
        font  = new sf::Font;

        if (!font->loadFromFile(fp::framd_font)) {
            gbl::end = true;
            return;
        }


        tx_v[0] = { txmg::makeTex(fp::screen_i) };
        tx_v[1] = { txmg::makeTex(fp::game_e_ic) };
        tx_v[2] = { txmg::makeTex(fp::game_h_ic) };
        tx_v[3] = { txmg::makeTex(fp::chat_ic  ) };

        // add textures and check for errors in texture load
        for (int n(0); n < spr_v.size(); ++n) {
            if (tx_v[n].getBase() == nullptr) {
                err::emergency_terminate.setFile(__FILE__).setLine(__LINE__).setText("texture failed to load.");
                return;
            }
            spr_v[n].setTexture(tx_v[n].getBaseRef());
        }

        /// SETUP

        float icon_x = 100, icon_y = 100;

        spr_v[0].setScale(double(869)/643, double(869)/643);

        spr_v[1].setPosition(10,10);
        spr_v[1].setScale(double(icon_x)/1024, double(icon_y)/1024);

        spr_v[2].setPosition(370, 10);

        spr_v[3].setPosition(10, 370);
        spr_v[3].setScale(double(icon_x)/512, double(icon_y)/512);

            /////////////////////
        /// text box for time input
        box_->setPosition(0, 500);
        box_->setFillColor(sf::Color::Blue);
        box_->setSize(sf::Vector2f(1600, 50));

        text_->setPosition(20, 500);
        text_->setColor(sf::Color::White);
        text_->setFont(*font);
        //////////////////////////


    }

    void comp_gui_close () {
        delete box_;
        delete text_;
        delete font;

        tx_v.resize(0);
        tx_v.shrink_to_fit();

        spr_v.resize(0);
        spr_v.shrink_to_fit();

        dt = -1;
        func = 0;
        input.clear();
        input_hint.clear();
    }

    /// MAIN function
    void comp(sf::Window& window) {
        gbl::to_draw_p.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)) {
            comp_gui_close();
            gbl::game_level = room::room;

            std::cout << "comp_close()\nroom()\n";
            return;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dt < 0) {
            //std::cout << "Left Mouse\n";
            sf::Vector2i mosPos = sf::Mouse::getPosition(window);
            for (int n=1; n < spr_v.size(); ++n) { // skips 0 b/c background
                if (spr_v[n].getGlobalBounds().contains(mosPos.x, mosPos.y)) {
                    gbl::event_handle = getText_handler;
                    func = n;
                    dt = 0;
                    std::cout << "click on: " << n << "\n";
                    break;
                }
            }
        }
        else if (dt > 0) {
            switch (func)
            {
            case 1:
                if (dt < min::GAME_E_T)
                    break;

                std::cout << "game_easy()";
                game_easy(dt);
                dt = -1;
                gbl::event_handle = gbl::do_nothing<sf::Event&>;
                break;
            case 2:
                if (dt < min::GAME_H_T)
                    break;

                std::cout << "game_hard()";
                game_hard(dt);
                dt = -1;
                gbl::event_handle = gbl::do_nothing<sf::Event&>;
                break;
            case 3:
                if (dt < min::CHAT_T)
                    break;

                std::cout << "chat()";
                chat(dt);
                dt = -1;
                gbl::event_handle = gbl::do_nothing<sf::Event&>;
                break;
            }
        }

        for (sf::Drawable& obj : spr_v)
            gbl::to_draw_p.push_back(&obj);

        if (dt >= 0) {
            if (input == "bad input")
                text_->setColor(sf::Color::Red);
            else if (text_->getColor() == sf::Color::Red)
                text_->setColor(sf::Color::White);

            gbl::to_draw_p.push_back(box_);
            gbl::to_draw_p.push_back(text_);
        }
    }
}
#endif // COMP_H
