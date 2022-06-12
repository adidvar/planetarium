#ifndef INIT_H
#define INIT_H
#include <vector>
#include <planet.h>
#include <string>
#include <mutex>
#include "ship.h"
#include "time_counter.h"
#include <mutex>
/**
 * @brief Описує стан системи
 */
struct init_result
{
    std::vector<Planet*> planets;
    Ship* trackingStar = nullptr;
    long double delta_time = 1.0;
    long double vector_scale=0.0;
    long double default_scale=0.0;
    int calc_per_graphic_tick = 120;
    bool cycle = true;
    TimeCounter time;
};
/**
 * @brief Загружає систему
 * @return система
 */
init_result initplanets();

#endif // INIT_H
