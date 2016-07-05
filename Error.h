#ifndef __ERROR_H_INCLUDED
#define __ERROR_H_INCLUDED

/// STD
#include <string>

namespace err {

////////////
///
/// ERROR
///
/// \@ exception and error management
///
/////////////

    class Error : public std::exception {   // remove std::exception inheritance?
        std::string text;
        std::string file;
        int line;
        bool prob;
        bool warn;

    public:
        Error (const std::string&, const std::string&, int);
        Error ();

        Error& setLine (int c);
        Error& setText (const std::string& t);
        Error& setFile (const std::string& f);

        void setWarn (bool);
        void setProb (bool);

        bool good () const; // !prob && !warn
        bool fail () const; //  prob
        bool bad () const;  //  prob ||  warn

        virtual const char * what () const noexcept;
        virtual const int getLine () const noexcept;
        virtual const char * getFile () const noexcept;
    } emergency_terminate;

}

#include "ErrorDef.h"

#endif // __ERRORDEF_H_INCLUDED
