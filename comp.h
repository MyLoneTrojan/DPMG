#ifndef COMP_H
#define COMP_H

/// STD
#include <iostream>
#include <sstream>
#include <string>

/// SFML

/// PROJECT
#include "global.h"

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

    /// MAIN function
    void comp() {
        std::cout << "\n\nComp: chat, game, or return?\n>";

        std::string activity;

        while (activity != "chat" && activity != "game" && activity != "return")
            std::getline(std::cin, activity);

        std::cout << "For how long (minutes):\n>";

        float min_t;
        using namespace min;
        switch (activity[0])
        {
        case 'c':
            min_t = CHAT_T;
            break;
        case 'g':
            min_t = activity[1] == 'e' ? GAME_E_T : GAME_H_T;
            break;
        case 'r':
            gbl::gl_back();
            return;
        }

        float dt;
        for (std::string input; ; ) {
            std::getline(std::cin, input);

            if (!(std::stringstream(input) >> dt))
                std::cout << "Error: unrecognized number\n>";
            else if (dt < min_t)
                std::cout << "Error: number too low\n\tMin: " << min_t << "\n>";
            else
                break;
        }

        if (min_t == min::CHAT_T)
            chat(dt);
        else if (min_t == min::GAME_E_T)
            game_easy(dt);
        else if (min_t == min::GAME_H_T)
            game_hard(dt);
        std::cout << "\n----------------\n";
    }
}
#endif // COMP_H
