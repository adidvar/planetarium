#pragma once
#include <cmath>
#include <vector>
#include <string>

#include "Vector.h"

template<typename number>
struct Planet
{
    number mass;
    number x, y;
    number speed_x, speed_y;
    number accel_x, accel_y;
    number density;
    std::string name;

    Planet(std::string name, number mass, number density, number x, number y, number speed_x, number speed_y, number accel_x, number accel_y):
		mass(mass),
        x(x),
        y(y),
        speed_x(speed_x),
        speed_y(speed_y),
        accel_x(accel_x),
        accel_y(accel_y),
		name(name),
		density(density)
    {}
    Vector<number> GetPositionV() const { return { x,y }; };
    Vector<number> GetSpeedV() const { return { speed_x,speed_y }; };
    Vector<number> GetAccelV() const { return { accel_x,accel_y }; };
    number GetRadius() const { return pow(3.0 * (mass / density) / 4.0 / 3.14, (number)1/3); };
};
