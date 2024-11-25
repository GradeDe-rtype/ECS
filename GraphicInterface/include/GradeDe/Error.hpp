/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_ERROR_SFML_HPP_
    #define GRADE_DE_ERROR_SFML_HPP_

    /*  ---- INCLUDES ---- */
    #include "GradeDe/Includes.hpp"

    /*  ---- CLASS ---- */
namespace gd
{
    class Error: public std::exception
    {
        public:
            Error(const std::string &what, const std::string &where = "");
            ~Error() = default;

            const char *what() const noexcept override;
            const std::string &where() const noexcept;
            static void read(const Error &error);

        private:
            std::string _what;
            std::string _where;
    };
}

#endif /* !GRADE_DE_FRAMERATE_SFML_HPP_ */
