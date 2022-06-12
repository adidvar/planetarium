#ifndef SHIP_H
#define SHIP_H
#include "planet.h"
#include <mutex>
/**
 * @brief Описує корабель
 */
class Ship : public Planet
{

    long double average_speed_sum = 0;
    long double average_speed_count = 1;
    long double distance = 0;
public:
    Ship(std::string name , long double mass , long double density , Vector2f position , Vector2f speed , int orbit_len);
    Ship(const Ship&) = default;
    ~Ship();
    void addSpeed(Vector2f);
    void ChangeSpeed(long double);
    long double Distance();
    long double AverageSpeed();
    virtual void MovePosition(long double delta_time);
};

#endif // SHIP_H
