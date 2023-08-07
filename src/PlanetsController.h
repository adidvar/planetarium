#pragma once
/*****************************************************************//**
 * \file   PlanetsController.h
 * \brief  Planets movement simulator
 * 
 * \author adidvar
 * \date   July 2022
 *********************************************************************/
#include <string>
#include <memory>
#include <chrono>
#include <sstream>

#include "Planet.h"
#include "Options.h"
#include "Number.h"
#include "Settings.h"

/**
 * Planets movement simulator
 */
class PlanetsController {
protected:
    
    using number = number;
    using duration = std::chrono::duration<number>;
    constexpr static number gravity =  6.6743015151515e-11;

    duration time;
	duration time_peer_frame;

    std::unique_ptr<number[]> x;
    std::unique_ptr<number[]> y;
    std::unique_ptr<number[]> speed_x;
    std::unique_ptr<number[]> speed_y;
    std::unique_ptr<number[]> accel_x;
    std::unique_ptr<number[]> accel_y;

    const size_t count;

    std::unique_ptr<const number[]> mass;
    std::unique_ptr<const number[]> density;

    std::unique_ptr<Options[]> planets_options;
    Options global_options;

public:
    PlanetsController(size_t count, number* mass, number* x, number* y, number* speed_x, number* speed_y, number* density, Options* planets_opts, const Options& global_opts) noexcept;
	PlanetsController(PlanetsController&& from) noexcept;

    /**
     * returns planet on index 
     */
    Planet operator[](size_t index) const;
    
    /**
     * skips some time
     * \param delta time to skip
     */
    void Play(duration delta);
    duration GetTime() const;
    /**
     * Set precision of calculations
     */
    void SetPrecision(duration dtime) noexcept;
private:
     void NextFrame(duration elapsed);
};


inline PlanetsController::PlanetsController(size_t count, number* mass, number* x, number* y, number* speed_x, number* speed_y, number* density, Options* planets_opts, const Options& global_opts) noexcept :
	count(count),
	mass(mass),
	x(x),
	y(y),
	speed_x(speed_x),
	speed_y(speed_y),
	density(density),
	planets_options(planets_opts),
	global_options(global_opts),
	time{},
	time_peer_frame(std::chrono::seconds(1)),
	accel_x(new number[count]),
	accel_y(new number[count])
{
}
