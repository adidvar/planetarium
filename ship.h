#ifndef SHIP_H
#define SHIP_H
#include "planet.h"
#include <mutex>

class Ship : public Planet
{
public:
    Ship(std::string name , long double mass , long double density , Vector2f position , Vector2f speed , int orbit_len);
    void addAccel(Vector2f);
    void ChangeSpeed(long double);
};

#endif // SHIP_H
