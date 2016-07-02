#ifndef ATTRI_H_INCLUDED
#define ATTRI_H_INCLUDED

    int main () {
        std::string input;
        std::getline(std::cin, input);

        const char _add = 12;
        for (int i=0; i < input.size()/sizeof(char); ++i)
            input[i] = ((int)input[i] + _add) % 255;
    }

namespace attr {
    float    mood = 50.f,     mood_min = -100,    mood_max = 100;  // positive or negative vibes?
    float  energy = 100.f,  energy_min = 0,     energy_max = 100;  // physical energy required (tiredness)
    float clarity = 100.f, clarity_min = -100, clarity_max = 100;  // How clearly one can think (in a trance or think right?)
    float  social = 0.f,    social_min = -100,  social_max = 100;  // Socialbility (negative means it takes significant effort)
    float  libido = 0.f,    libido_min = 0,     libido_max = 100;  //    0 to 100
    float   motiv = 50.f     motiv_min = -100    motiv_max = 100;  // -100 to 100
    float   skill = 0.f,     skill_min = 0,      skill_max = 100;  //    0 to 100
    float    time = 0.f,      time_min = 0,       time_max = 1440; //    0 to 1440  (24-hour day in minutes)

    std::vector<float> fri_close;

    #define attr_mk_inbound (a) { if (a < a_min) a = a_min; else if (a > a_max) a = a_max; }

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
        libido  = rand() % 50 + 30;
        clarity = rand() % 75 /*max high*/ - rand() % 75 /*max low*/;
        social += rand() % 40;

        // mood-based raise
        mood    = mood / 30 + rand() % 50;

        // absolute value raises : sign mirrors mood
        motiv   = (mood < 0 ? -1 : 1) * (abs(mood) / 10 + rand() % 50);
    }
};

#endif
