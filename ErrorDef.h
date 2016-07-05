#ifndef __ERRORDEF_H_INCLUDED
#define __ERRORDEF_H_INCLUDED

#include "Error.h"

///////////////////
///
/// ERROR   CLASS
///
/// \@ Exception and error management
///
/////////////////

    ////////////////////
    ///
    /// CONSTRUCTORS
    ///
    /// \param str - set file as str
    /// \param co  - set line as co
    ///     \# Default -- everything zeroed
    ///     \# Other wise -- prob set as true. everything else zeroed
    ///
    ////////////////

    err::Error::Error (const std::string& str, const std::string& f = "", int co = 0) : text(str), line(co), file(f), prob(true), warn(true) {
        /*--- EMPTY ---*/
    };
    err::Error::Error () : line(0), prob(false), warn(false) {
        /*--- EMPTY ---*/
    };

    /////////////
    ///
    /// SETUP
    ///
    /////////

    err::Error& err::Error::setLine (int c) {
        prob = warn = true;
        line = c;
        return *this;
    }
    err::Error& err::Error::setText (const std::string& t) {
        prob = warn = true;
        text = t;
        return *this;
    }
    err::Error& err::Error::setFile (const std::string& f) {
        prob = warn = true;
        file = f;
        return *this;
    }

    void err::Error::setProb (bool p) {
        prob = p;
    }
    void err::Error::setWarn (bool p) {
        warn = p;
    }

    ///////////
    ///
    ///INFO
    ///
    ///////

        //////////////
        /// Severity
    bool err::Error::good () const {
        return !prob && !warn;
    }
    bool err::Error::fail () const {
        return prob;
    }
    bool err::Error::bad () const {
        return warn || prob;
    }

        ////////////////
        /// Specifics
    const char * err::Error::what    () const noexcept {
        return text.c_str();
    }
    const int    err::Error::getLine () const noexcept {
        return line;
    }
    const char * err::Error::getFile () const noexcept {
        return file.c_str();
    }

#endif // __ERRORDEF_H_INCLUDED
