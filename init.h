#ifndef INIT_H
#define INIT_H
#include <vector>
#include <planet.h>
#include <string>
#include <mutex>
#include "ship.h"

struct init_result
{
    std::vector<Planet*> planets;
    Ship* trackingStar = nullptr;
    long double delta_time = 1.0;
    long double vector_scale=0.0;
    long double default_scale=0.0;
};

init_result initplanets();

#endif // INIT_H
