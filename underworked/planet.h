#ifndef PLANET_H
#define PLANET_H
#include <math.h>
#include <vector>
#include <string>
#include <vector2f.h>
#include <orbit_queue.h>
/**
 * @brief Описує планету
 */
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
    Planet(const Planet&) = default;
    virtual ~Planet();
    void CalcAcceleration(std::vector<Planet*> planets);
    virtual void MovePosition(long double delta_time);
    void RegisterOrbit();

    Vector2f GetPosition() const {return position;}
    long double Radius() const {return pow(  3.0*(GetMass() / GetDestiny() )/4.0 /M_PI, 0.333333);}
    void SetPosition(Vector2f p) {this->position = p;}
    Vector2f GetSpeed() const {return speed;}
    Vector2f GetAccel()const {return acceleration;}
    const orbit_queue& GetOrbit() const {return orbit;}
    orbit_queue& GetOrbit() {return orbit;}
    long double GetMass() const {return mass;}
    long double GetDestiny()const {return density;}
    std::string GetName()const {return name;}
};

#endif // PLANET_H
