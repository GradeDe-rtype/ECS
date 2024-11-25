/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Error.hpp"


namespace gd
{
    Error::Error(const std::string &what, const std::string &where)
        : _what(what), _where(where)
    {
    }

    const char *Error::what() const noexcept
    {
        return _what.c_str();
    }

    const std::string &Error::where() const noexcept
    {
        return _where;
    }

    void Error::read(const Error &error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        if (!error.where().empty())
            std::cerr << "At: " << error.where() << std::endl;
    }
}
