#include "ship.h"
#include <iostream>

Ship::Ship(std::string name, long double mass, long double density, Vector2f position, Vector2f speed, int orbit_len):
    Planet(name,mass,density,position,speed,orbit_len)
{}

Ship::~Ship()
{

}

void Ship::addSpeed(Vector2f f)
{
    speed = speed + f;
}

void Ship::ChangeSpeed(long double k)
{
    speed = speed * k;
}

long double Ship::Distance()
{
    return distance;
}

long double Ship::AverageSpeed()
{
    return average_speed_sum / average_speed_count;
}

void Ship::MovePosition(long double delta_time)
{
    Planet::MovePosition(delta_time);
    average_speed_sum += speed.Module();
    average_speed_count++;
    distance += (speed*delta_time).Module();
};
