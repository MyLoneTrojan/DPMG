#ifndef TEXTURE_MANAGER_H_INCLUDED
#define TEXTURE_MANAGER_H_INCLUDED

/// API
#include <SFML/Graphics.hpp>

/// STD
#include <vector>   // toDraw and few other times
#include <memory>   // garbage collection for texture pointers
//#include <utility>  // unneeded?
#include <list>     // tex

/// LOCAL
#include "Error.h"

namespace txmg {

struct TexLoc;
struct TexPos;

class  TexPtr;  // defined in this file
                // implicitly converts to *tex remove? make explicit?
                // designed to act as a garbage collector for texture*s in multiple classes pointing to the same point in memory

/////////////
///
/// DRAW
///
/////////

    std::vector<sf::Drawable*> toDraw;

///////////////
///
/// TEXTURE
///
/// \@ remove reuse of textures
///
/////////////////

    ////////////////
    ///
    /// OBJECTS
    ///
    ////////////

    std::list< TexLoc > tex;

    /////////////////
    ///
    /// FUCNTIONS
    ///
    //////////////

        //////////////////////////////
        /// check if file is loaded
        /// \param file path
        /// \return position (-1 means not loaded)
    TexPos isLoaded (const std::string&);

        //////////////////////////////
        /// \param file path of texture to create
        ///     \# if texture with the same source file is found, then its position is returned
        ///
        /// \return position of created object in tex
    TexPos makeTex (const std::string&);

        //////////////////////////////
        /// \param index of element to be deleted from tex
    void remove (TexPos);

    ////////////////
    ///
    /// CLASSES
    ///
    ////////////

        //////////////////////////////////
        ///Pair of texture and source file
    struct TexLoc {
        TexLoc(const std::string&);

        err::Error loadTex (const std::string&);

        err::Error error;

        sf::Texture tex;
        std::string path;
    };


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//



        ///////////////////////////////////////////////
        ///Wrapper class to access elements in gbl::tex
    struct TexPos {
        std::list<TexLoc>::iterator it;
        bool good;

        TexPos () : good(false) {};
        TexPos (decltype(it) i) : good(true), it(i) {};
    };


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//



            ///////////////////////////////////////////////////////////
        /// Minimal garbage collection for textures in the global space
    class TexPtr {
        static void del (TexPos*);

        std::shared_ptr<TexPos> ptr;
        sf::Texture * tex_p;
    public:
        TexPtr (); // sets ptr's deleter to function  del
        TexPtr (const TexPos&);

        void loadTex (TexPos);

        TexPos getTexPos ();

        void clear ();

        sf::Texture* getBase ();
        sf::Texture& getBaseRef ();
    };

}

/// Definitions
#include "texture_manager_def.inl"

#endif // GLOBAL_H_INCLUDED

