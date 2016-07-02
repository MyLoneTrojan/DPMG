#include <iostream>
#include <string>
//#include <SFML/Graphics.hpp>

void print_stats () {
    std::cout << "TIME: " << attr::time << "\nmood: " << attr::mood << "\nEnergy: " << attr::energy
              << "\nClarity: " << attr::clarity << "\nSkill" << attr::skill;
}

namespace gs_place {
    const int HOME = 0;
    const int COMP = 1; // const int PHONE;
    const int BED  = 2;

    const int ERRAND = 3;
    const int FRIEND = 4;
};

int bedroom () {
    std::cout << "\n\nComputer\nSleep\nPhone\nLeave...\n"

    int choice_place = -1;
    while (choice_place == -1) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "computer")
            choice_place = gs_place::COMP;
        else if (input == "sleep")
            choice_place = gs_place::BED;
        else if (input == "phone")
            choice_place =gs_place::COMP; // PHONE
    }
}

int comp () {
    std::cout << "\n\nEasy games\nHard games\nChat\nStudy\nWatch films";

    // pick action
    char i_action = '\0';
    while (i_aciton == '\0') {
        std::string input;
        std::getline(std::cin, input);

        if (input.size() == 0)
            continue;

        if (input[0] == 'e' || input[0] == 'h' || input[0] == 'c' || input[0] == 's' || input[0] == 'w')
            i_action = input[0];
    }

    // perform action
    switch (i_action)
    {
        using namespace attr;
    case 'e':
        const float dt = 10;
        mood += -clarity / dt;
        time_advance(dt);
        break;
    case 'h':
        const float dt = 60;
        mood +=  clarity / dt;
        time_advance(dt);
        break;
    case 'c':
        return i_action;
    case 's':
        const float dt = 30;
        skill += (clarity < 0 ? .5 : (.8*clarity + 4));
        time_advance(dt);
        break;
    case 'w':
        const float dt = 90;
        if (clarity < 90)
            clarity = 100;
        else
            clarity += 10;

        time_advance(dt);
        break;
    }
}

int main () {
    std::cout << "Welcome!\n\n";

    int state_place = gs_place::HOME;

    while (true) {
        switch (state_place)
        {
            using namespace gs_place;
        case HOME:
            break;
        case BED:
            state_place = bedroom();
            break;
        case ERRAND:
            break;
        case COMP:
            state_place = comp();
            break;

        }
    }

    return 0;
}
