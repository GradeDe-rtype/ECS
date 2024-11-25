/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_VECTOR_SFML_HPP_
    #define GRADE_DE_VECTOR_SFML_HPP_

    /*  ---- INCLUDES ---- */
    #include "GradeDe/Includes.hpp"
    #include "GradeDe/KeyBoard.hpp"


    /*  ---- CLASS ---- */
namespace gd
{
    template <typename T>
    class Vector2
    {
        public:
            Vector2() = delete;
            Vector2(T x, T y);
            ~Vector2() = default;

            Vector2<T> operator+(const Vector2<T> &vector);
            Vector2<T> &operator+=(const Vector2<T> &vector);
            Vector2<T> operator-(const Vector2<T> &vector);
            Vector2<T> &operator-=(const Vector2<T> &vector);
            Vector2<T> operator*(const Vector2<T> &vector);
            Vector2<T> &operator*=(const Vector2<T> &vector);
            Vector2<T> operator/(const Vector2<T> &vector);
            Vector2<T> &operator/=(const Vector2<T> &vector);

            T x;
            T y;

        private:
    };
}

#endif /* !GRADE_DE_VECTOR_SFML_HPP_ */
