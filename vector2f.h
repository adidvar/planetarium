#ifndef VECTOR2F_H
#define VECTOR2F_H
#include "math.h"
#include <SFML/System/Vector2.hpp>

struct Vector2f
{
    Vector2f(long double x , long double y):
        x(x) , y(y){}
    Vector2f():
        x(0.0) , y(0.0){}
    Vector2f(const Vector2f&) = default;
    long double x;
    long double y;
    static Vector2f fromVector(long double forge , long double cos, long double sin );

    long double Module() const {return sqrt(pow(x,2) + pow(y,2));}
    Vector2f Nomalize() const {return Vector2f(x/Module(),y/Module());} // повертає співнаправлений вектор довжиною в 1
    Vector2f operator +(Vector2f v2){return Vector2f(this->x + v2.x , this->y + v2.y);}
    Vector2f operator -(Vector2f &v2){return Vector2f(this->x - v2.x , this->y - v2.y);}
    Vector2f operator *(long double f){return Vector2f(this->x *f , this->y *f);}
    Vector2f operator /(long double f){return Vector2f(this->x /f , this->y /f);}
    operator sf::Vector2f() const;
};

inline Vector2f::operator sf::Vector2f() const
{
   return sf::Vector2f(x,y);
}

inline Vector2f Vector2f::fromVector(long double forge, long double cos, long double sin)
{
    return Vector2f(forge * cos , forge * sin );
}

#endif // VECTOR2F_H
