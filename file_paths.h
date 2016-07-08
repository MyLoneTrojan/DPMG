#ifndef FILE_PATHS_H_INCLUDED
#define FILE_PATHS_H_INCLUDED

/// STD
#include <string>   // maybe change so files are #define instead of strings

namespace fp {
    using namespace std;

    /// BASE of files
    const string base_f = "C:/Users/222222day/cpp/Source/DPMG-master/";

        // base of room
    const string room_f = base_f + "image/Room/";

    const string  bed_i = room_f + "bed_head-on.png";
    const string desk_i = room_f + "pc_desk_45_clockwise.png";
    const string room_i = room_f + "empty_room.jpg";


    // base of font
    const string font_f = base_f + "font/";

    const string framd_font = font_f + "framd.ttf";
}

#endif // FILE_PATHS_H_INCLUDED
