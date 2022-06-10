#include "ship.h"
#include <iostream>

Ship::Ship(std::string name, long double mass, long double density, Vector2f position, Vector2f speed, int orbit_len):
    Planet(name,mass,density,position,speed,orbit_len)
{}

void Ship::addAccel(Vector2f f)
{
    acceleration = acceleration + f;
}

void Ship::ChangeSpeed(long double k)
{
    speed = speed * k;
};
