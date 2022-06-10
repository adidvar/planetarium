#ifndef PLANET_H
#define PLANET_H
#include <math.h>
#include <vector>
#include <string>
#include <vector2f.h>
#include <orbit_queue.h>

class Planet
{
protected:
    long double mass;
    Vector2f position;
    Vector2f speed;
    Vector2f acceleration;
    orbit_queue orbit;
    std::string name;
    long double density;
public:
    Planet(std::string name , long double mass , long double density , Vector2f position , Vector2f speed , int orbit_len);
    void CalcAcceleration(std::vector<Planet*> planets);
    void MovePosition(long double delta_time);

    Vector2f GetPosition() const {return position;}
    Vector2f GetSpeed() const {return speed;}
    Vector2f GetAccel()const {return acceleration;}
    const orbit_queue& GetOrbit() const {return orbit;}
    long double GetMass() const {return mass;}
    long double GetDestiny()const {return density;}
    std::string GetName()const {return name;}
};

#endif // PLANET_H
