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
    gbl::TexPos gbl::isLoaded (const std::string& file) {
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
                    sf::Texture& gbl::getTex (std::size_t n) {
                        return tex.at(n).tex;
                    }
    */

        //////////////////////////////
        /// \param file path of texutre to creat
        /// \param constructor args for the texture
        ///     \# if texture with the same source file is found, then its position is returned
        ///
        /// \return position of created object in tex
    gbl::TexPos gbl::makeTex (const std::string& file) {
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
    void gbl::remove (gbl::TexPos index) {
        if (!index.good || index.it == tex.end())
            return; //invalid iterator

        tex.erase(index.it);
    }

    //////////////
    ///
    /// CLASS - TexLoc
    ///
    //////////////

    gbl::TexLoc::TexLoc (const std::string& p) {
        path = p;
        error = loadTex(p);
    }

    err::Error gbl::TexLoc::loadTex (const std::string& p) {
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
    void gbl::TexPtr::del (TexPos* tp) {
        if (tp != nullptr && tp->good)
            remove(*tp);
        delete tp;
    }

        //////////////
        ///
        /// Constructor
        ///
        ///////////////

            //////////////
        /// default -- set deleter as TexPtr::del
    gbl::TexPtr::TexPtr () : ptr(nullptr, del) {
        /*--- EMPTY ---*/
    };

    gbl::TexPtr::TexPtr (const TexPos& tp) {
        loadTex(tp);
    }

        ////////////////
        ///
        /// Setup
        ///
        ////////////////

            ////////////
        /// set TexPos to obtain sf::texture* and to later delete it from the global scope
    void gbl::TexPtr::loadTex (TexPos tp) {
        ptr = std::shared_ptr<TexPos>(new TexPos(tp), del);
        tex_p = tp.good ? &tp.it->tex : nullptr;
    }

        ////////////////
        ///
        /// Info / Conversion
        ///
        ////////////////

        /// Get internal TexPos
    gbl::TexPos gbl::TexPtr::getTexPos () {
        return *ptr;
    }

        /// Get internal sf::Texture*
    gbl::TexPtr::operator sf::Texture* () {
        return tex_p;
    }


#endif // GLOBALDEF_H_INCLUDED
