#include "planet.h"
#include "settings.h"

const long double gravity = GRAVITY;

Planet::Planet(std::string name , long double mass, long double density, Vector2f position, Vector2f speed, int orbit_len):
    mass(mass),
    position(position),
    speed(speed),
    orbit(orbit_len),
    name(name),
    density(density)
{}

Planet::~Planet()
{

}

void Planet::MovePosition(long double delta_time)
{
    speed = speed + acceleration * delta_time;
    position = position + speed * delta_time;
}

void Planet::RegisterOrbit()
{
     orbit.push(position);
}

void Planet::CalcAcceleration(std::vector<Planet *> planets)
{
    acceleration = Vector2f(0.0,0.0);
    for(auto &p : planets)
    {
        if(p == this)continue;
        Vector2f position_delta = p->position - this->position ;
        long double dist = position_delta.Module();
        long double forge = p->mass * this->mass * gravity /  pow(dist,2);
        long double a_forge = forge / this->mass;

        Vector2f a = Vector2f::fromVector(a_forge ,  position_delta.x / dist , position_delta.y / dist  );

        acceleration=acceleration +a;
    }
}
