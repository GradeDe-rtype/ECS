/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Vector.hpp"


namespace gd
{
    template <typename T>
    Vector2<T>::Vector2(T x, T y)
        : x(x), y(y)
    {
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator+(const Vector2<T> &vector)
    {
        return Vector2<T>(x + vector.x, y + vector.y);
    }

    template <typename T>
    Vector2<T> &Vector2<T>::operator+=(const Vector2<T> &vector)
    {
        x += vector.x;
        y += vector.y;
        return *this;
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator-(const Vector2<T> &vector)
    {
        return Vector2<T>(x - vector.x, y - vector.y);
    }

    template <typename T>
    Vector2<T> &Vector2<T>::operator-=(const Vector2<T> &vector)
    {
        x -= vector.x;
        y -= vector.y;
        return *this;
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator*(const Vector2<T> &vector)
    {
        return Vector2<T>(x * vector.x, y * vector.y);
    }

    template <typename T>
    Vector2<T> &Vector2<T>::operator*=(const Vector2<T> &vector)
    {
        x *= vector.x;
        y *= vector.y;
        return *this;
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator/(const Vector2<T> &vector)
    {
        return Vector2<T>(x / vector.x, y / vector.y);
    }

    template <typename T>
    Vector2<T> &Vector2<T>::operator/=(const Vector2<T> &vector)
    {
        x /= vector.x;
        y /= vector.y;
        return *this;
    }

    template class Vector2<int>;
    template class Vector2<float>;
    template class Vector2<double>;
}
