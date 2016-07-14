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

    namespace ret {
        const int SUCCESS         = 0,
                  FAIL_ENERGY     = 1,
                  FAIL_MOTIV      = 2,
                  FAIL_NO_FRIENDS = 3,
                  FAIL_TIME       = 4,
                  FAIL_SKILL      = 5;
    }

    float dt = -1;
    float clock_align;
    char func = 0;

    sf::String          input;
    sf::RectangleShape* box_;
    sf::Text*           text_;
    sf::Font*           font;
    std::vector<sf::Sprite> spr_v;
    std::vector<txmg::TexPtr> tx_v;

        /////////////////
    /// Clock manipulator
    void update_clock () {
        const float og_y = 50, x_buff = 10;
        text_[2].setString(attr::get_clock());

        sf::FloatRect c_dimen = text_[2].getLocalBounds();
        sf::Vector2f pos = box_[1].getPosition();

        text_[2].setPosition(gbl::win_size.x - clock_align - c_dimen.width - c_dimen.left - x_buff, og_y);
    }


    /// Input of text
    void getText_handler (sf::Event& event) {
        if (event.type != sf::Event::TextEntered)
            return;

        auto& in = event.text.unicode;

        if ( (in >= '0' && in <= '9') || in == '.' ) {
            if (input == "bad input") {
                input.clear();
                text_->setColor(sf::Color::White);
            }
            input += sf::String(event.text.unicode);
        } else if (in == '\b' && input.getSize() > 0)
            input.erase( input.getSize()-1 );
        else if (in == '\r') { // enter was pressed
            dt = std::strtof(input.toAnsiString().c_str(), nullptr);

            float min;
            switch (func)
            {
            case 1:
                min = min::GAME_E_T;
                break;
            case 2:
                min = min::GAME_H_T;
                break;
            case 3:
                min = min::CHAT_T;
                break;
            }

            if (input.getSize() == 0) {
                func = 0;
                dt = -1;
                text_[1].setString("");
            }
            else if (dt < min) {
                input = "bad input";
                text_->setColor(sf::Color::Red);
                dt = -1;
            } else {
                input.clear();
            }
        }

        text_->setString(input);
    }

    ///////////////////////
    ///
    /// ATTRIBUTE MODIFIERS

    int chat (float dt) {
        using namespace attr;

        // CHECK if capable
        if (attr::fri_close.size() < 1)
            return ret::FAIL_NO_FRIENDS;

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

        return ret::SUCCESS;
    }

    int game_easy (float dt) {
        using namespace attr;

        mood *= dt * .7;

        social_adv(dt);
        motiv_adv(dt);

        time_adv(dt);

        return ret::SUCCESS;
    }
    int game_hard (float dt) {
        return game_easy(dt);
    }

    int learn (float dt); // add topic as parameter

    /// \ ATTRIBUTE MODIFER
    ////////////////////////


    void comp_gui_load () {
        spr_v.resize(4);
        tx_v.resize(4);

        box_  = new sf::RectangleShape[2];
        text_ = new sf::Text[3];
        font  = new sf::Font[2];

        if (!font->loadFromFile(fp::framd_font) || !font[1].loadFromFile(fp::consola_font)) {
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

        /// Sprites
        float icon_x = 100, icon_y = 100;
        float   og_x = 50,    og_y = 50;
        float buff_x = 10,  buff_y = 10;

        spr_v[0].setScale(double(869)/643, double(869)/643);
        sf::FloatRect bounds = spr_v[0].getGlobalBounds();
        spr_v[0].setPosition(gbl::win_size.x/2 - bounds.width/2, gbl::win_size.y/2 - bounds.height/2);

        og_x += spr_v[0].getPosition().x;
        og_y += spr_v[0].getPosition().y;

        spr_v[1].setPosition(og_x, og_y);
        spr_v[1].setScale(double(icon_x)/1024, double(icon_y)/1024);

        spr_v[2].setPosition(og_x+icon_x+buff_x, og_y);
        spr_v[2].setScale(double(icon_x)/350,  double(icon_y)/350);

        spr_v[3].setPosition(og_x+icon_x*2+buff_x*2, og_y);
        spr_v[3].setScale(double(icon_x)/512,  double(icon_y)/512);

            /////////////////////
        /// clock - image
        float c_size_x = 100, c_size_y = 50;
        clock_align = og_x;
        box_[1].setSize( sf::Vector2f(c_size_x, c_size_y));
        //box_[1].setOrigin(c_size_x, 0);
        box_[1].setPosition(gbl::win_size.x - og_x - c_size_x, og_y);
        box_[1].setFillColor(sf::Color(0x03, 0xF7, 0xEB));

        text_[2].setColor(sf::Color(0xF1, 0xF1, 0xF1));
        text_[2].setFont(font[1]);
        update_clock();

            /////////////////////
        /// text box for time input
        box_->setPosition(og_x-6, 652);
        box_->setFillColor(sf::Color(0xC9, 0xDA, 0xEA));
        box_->setSize(sf::Vector2f(993, 45));

            // input
        text_->setPosition(og_x, 654);
        text_->setColor(sf::Color(0x19, 0x15, 0x16));
        text_->setFont(*font);

            // output / hint
        text_[1].setPosition(og_x, 604);
        text_[1].setColor(sf::Color(0xF1, 0xF1, 0xF1));
        text_[1].setFont(*font);
        //text_[1].setString("Input time for action (in minutes)");  // set on click of icon
        //////////////////////////


    }

    void comp_gui_close () {
        delete[] box_;
        delete[] text_;
        delete[] font;

        tx_v.resize(0);
        tx_v.shrink_to_fit();

        spr_v.resize(0);
        spr_v.shrink_to_fit();

        dt = -1;
        func = 0;
        input.clear();
        //input_hint.clear();
    }

    /// MAIN function
    void comp(sf::Window& window) {
        gbl::to_draw_p.clear();

        /// Check for 'return'
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            comp_gui_close();

            // room should not have closed
            gbl::game_level = room::room;
            return;
        }

        /// check for icon click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mosPos = sf::Mouse::getPosition(window);

            // check if mosPos is in a sprite (stops after first find)
            for (int n=1; n < spr_v.size(); ++n) {
                    // if on sprite (proper icon click
                if (spr_v[n].getGlobalBounds().contains(mosPos.x, mosPos.y)) {
                    func = n; // store which function to use
                    gbl::event_handle = getText_handler; // start collecting input

                    sf::String input_hint;
                    switch (func)
                    {
                    case 1:
                        input_hint = "Easy Game: minutes (min: " + gbl::to_string(min::GAME_E_T);
                        break;
                    case 2:
                        input_hint = "Hard Game: minutes (min: " + gbl::to_string(min::GAME_H_T);
                        break;
                    case 3:
                        input_hint = "Chat: minutes (min: " + gbl::to_string(min::CHAT_T);
                        break;
                    }

                    text_[1].setString(input_hint + ")");

                    break; // only counts this sprite
                }
            }
        }

        // if valid input
        if (dt > 0) {
            int ret = 0; // un-handled currently

            switch (func)
            {
            case 1:
                ret = game_easy(dt);
                std::cout << "game_easy()\n";
                break;
            case 2:
                ret = game_hard(dt);
                std::cout << "game_hard()\n";
                break;
            case 3:
                ret = chat(dt);
                std::cout << "chat()\n";
                break;
            }
            update_clock();
            func = 0;
            dt = -1;
            gbl::event_handle = gbl::do_nothing<sf::Event&>;
        }

        // draw typical background and icons
        for (sf::Sprite& spr : spr_v)
            gbl::to_draw_p.push_back(&spr);

        // draw clock
        gbl::to_draw_p.push_back( box_ + 1);
        gbl::to_draw_p.push_back(text_ + 2);

        // draw text input box when collecting input
        if (func != 0) {
            gbl::to_draw_p.push_back( box_);
            gbl::to_draw_p.push_back(text_);
            gbl::to_draw_p.push_back(text_ + 1);
        }
    }
}
#endif // COMP_H
