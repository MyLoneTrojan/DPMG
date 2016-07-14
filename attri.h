#ifndef ATTRI_H_INCLUDED
#define ATTRI_H_INCLUDED

/// STD
#include <sstream>
#include <vector>
#include <string>

/// SFML


/// PROJECT
#include "global.h"

namespace attr {
    float    mood =  50.f,    mood_min = -100,    mood_max =  100;  // positive or negative vibes?
    float  energy = 100.f,  energy_min =    0,  energy_max =  100;  // physical energy required (tiredness)
    float clarity = 100.f, clarity_min = -100, clarity_max =  100;  // How clearly one can think (in a trance or think right?)
    float  social =   0.f,  social_min = -100,  social_max =  100;  // ease of socializing (negative means to socialize drains energy and mood quicker)
    float  libido =   0.f,  libido_min =    0,  libido_max =  100;  //    0 to 100
    float   motiv =  50.f,   motiv_min = -100,   motiv_max =  100;  // -100 to 100
    float   skill =   0.f,   skill_min =    0,   skill_max =  100;  //    0 to 100
    float    time =   0.f,    time_min =    0,    time_max = 1440;  //    0 to 1440  (24-hour day in minutes)

    std::vector<float>        fri_close;
    std::vector<txmg::TexPtr> fri_avi;
    std::vector<std::string>  fri_name;

    /*
    struct friend_qualities {
        bool night_owl;
        float closeness;
        float trust;
        float problem;
    };

    std::vector<friend_qualities> fri_qual;
    */

    /// Neatly print out all attributes
    void print_attr () {
        using namespace attr;

        std::cout << "Mood: "       << mood    << "\tEnergy: " << energy
                  << "\tClarity: "  << clarity << "\tSocial: " << social
                  << "\n\nLibido: " << libido  << "\tMotiv: "  << motiv
                  << "\tSkill: "    << skill   << "\tTime: "   << time;
    }

    std::string get_clock () {
        int hour   = time / 60;
        int minute = fmod(time, 60);

        std::string min_ = gbl::to_string(minute);
        if (min_.size() < 2)
            min_ = "0" + min_;

        return gbl::to_string(hour) + ":" + min_;
    }


    #define attr_mk_inbound(a) { if (a < a ## _min) a = a ## _min; else if (a > a ## _max) a = a ## _max; }

    inline void time_adv (const float& dt) {
        time += dt;
        time  = fmod(time, time_max);
    }
    inline void clarity_adv (const float& dt) {
        clarity /= dt;
        attr_mk_inbound(clarity);
    }
    inline void energy_adv (const float& dt) {
        energy -= dt / 5;
        attr_mk_inbound(energy);
    }
    inline void social_adv (const float& dt) {
        social += dt/30;
        attr_mk_inbound(social);
    }
    inline void libido_adv (const float& dt) {
        libido += dt / 60;
        attr_mk_inbound(libido);
    }
    inline void mood_adv (const float& dt) {
        mood -= dt / 120;
        attr_mk_inbound(mood);
    }
    inline void motiv_adv (const float& dt) {
        motiv += .006 * energy * mood * dt;
        attr_mk_inbound(motiv);
    }


    void sleep_adv (const float& dt) {
        const float e_gain = .15625f; // eight hours should yield 75 energy

        // obvious math
        time   += dt;
        energy += e_gain * dt;

        // independent; random
        libido  = gbl::rand_eng() % 50 + 30;
        clarity = gbl::rand_eng() % 75 /*max high*/ - gbl::rand_eng() % 75 /*max low*/;
        social += gbl::rand_eng() % 40;

        // mood-based raise
        mood    = mood / 30 + gbl::rand_eng() % 50;

        // absolute value raises : sign mirrors mood
        motiv   = (mood < 0 ? -1 : 1) * (abs(mood) / 10 + rand() % 50);
    }
};

#endif
