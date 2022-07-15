#pragma once

#include <cmath>

#include "Number.h"

struct Vector
{
    Vector(number x, number y):
        x(x) , y(y){}
    constexpr Vector():
        x(0.0) , y(0.0){}
    Vector(const Vector&) = default;
    number x;
    number y;

    static Vector fromVector(number forge , number cos, number sin );
    number Module() const {return sqrt(pow(x,2) + pow(y,2));}
    Vector Normalize() const {return Vector(x/Module(),y/Module());} // повертає співнаправлений вектор довжиною в 1
    Vector operator +(Vector v2){return Vector(this->x + v2.x , this->y + v2.y);}
    Vector operator -(Vector &v2){return Vector(this->x - v2.x , this->y - v2.y);}
    Vector operator *(number f){return Vector(this->x *f , this->y *f);}
    Vector operator /(number f){return Vector(this->x /f , this->y /f);}
};


inline Vector Vector::fromVector(number forge, number cos, number sin)
{
    return Vector(forge * cos , forge * sin );
}
