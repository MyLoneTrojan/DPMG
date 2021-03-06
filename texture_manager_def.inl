#ifndef GLOBALDEF_H_INCLUDED
#define GLOBALDEF_H_INCLUDED

/////////////////////////
///
/// TEXTURE  HELPERS
///
/// \# Texture management
///
/////////////////////////

    ////////////////
    ///
    /// FUNCTIONS
    ///
    /////////////

        //////////////////////////////
        /// check if file is loaded
        /// \param file path
        /// \return position (-1 means not loaded)
    txmg::TexPos txmg::isLoaded (const std::string& file) {
        TexPos param;
        param.it = tex.begin();
        param.good = false;

        for (; param.it != tex.end(); param.it++)
            if (param.it->path == file) {
                param.good = true;
                return param;
            }

        return param;
    }

    /* DEAD CODE    -- superseded by dereferencing member  it  inside TexPos
                        //////////////////////////////
                        /// \param position in tex
                        /// \return texture of object in tex
                    sf::Texture& txmg::getTex (std::size_t n) {
                        return tex.at(n).tex;
                    }
    */

        //////////////////////////////
        /// \param file path of texutre to creat
        /// \param constructor args for the texture
        ///     \# if texture with the same source file is found, then its position is returned
        ///
        /// \return position of created object in tex
    txmg::TexPos txmg::makeTex (const std::string& file) {
        TexPos pos = isLoaded(file);

        if (pos.good)
            return pos;

        tex.emplace_back(file);
        if (tex.back().error.bad()) {
            tex.pop_back();
            return pos;
        }

        pos.it = tex.end();
        pos.it--;
        pos.good = true;
        return pos;
    }

        //////////////////////////////
        /// \param index of element to be deleted from tex
    void txmg::remove (txmg::TexPos index) {
        if (!index.good || index.it == tex.end())
            return; //invalid iterator

        tex.erase(index.it);
    }

    //////////////
    ///
    /// CLASS - TexLoc
    ///
    //////////////

    txmg::TexLoc::TexLoc (const std::string& p) {
        path = p;
        error = loadTex(p);
    }

    err::Error txmg::TexLoc::loadTex (const std::string& p) {
        err::Error param;
        if (!tex.loadFromFile(p)) {
            param.setLine(__LINE__).setFile(__FILE__).setText("Invalid File Name.");

            param.setProb(true);
            param.setWarn(true);
        }
        return param;
    }

    ///////////////////
    ///
    /// CLASS - TexPtr
    ///
    ///     \@ used to share ownership of a global texture
    ///
    ////////////////////


        ////////////
        ///
        /// Helper / static member
        ///
        ////////////

            /// deletion procedure for a sf::Texture in the global scope
    void txmg::TexPtr::del (TexPos* tp) {
        if (tp != nullptr && tp->good)
            remove(*tp);
        delete tp;
    }

            /// clear all variables as if new
    void txmg::TexPtr::clear () {
        ptr.reset();
        tex_p = nullptr;
    }

        //////////////
        ///
        /// Constructor
        ///
        ///////////////

            //////////////
        /// default -- set deleter as TexPtr::del
    txmg::TexPtr::TexPtr () : ptr(nullptr, del) {
        /*--- EMPTY ---*/
    };

    txmg::TexPtr::TexPtr (const TexPos& tp) {
        loadTex(tp);
    }

        ////////////////
        ///
        /// Setup
        ///
        ////////////////

            ////////////
        /// set TexPos to obtain sf::texture* and to later delete it from the global scope
    void txmg::TexPtr::loadTex (TexPos tp) {
        ptr = std::shared_ptr<TexPos>(new TexPos(tp), del);
        tex_p = tp.good ? &tp.it->tex : nullptr;
    }

        ////////////////
        ///
        /// Info / Conversion
        ///
        ////////////////

        /// Get internal TexPos
    txmg::TexPos txmg::TexPtr::getTexPos () {
        return *ptr;
    }

        /// Get internal sf::Texture*
    sf::Texture* txmg::TexPtr::getBase () {
        return tex_p;
    }

    sf::Texture& txmg::TexPtr::getBaseRef () {
        return (*getBase());
    }


#endif // GLOBALDEF_H_INCLUDED
