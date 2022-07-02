#pragma once
#include <string>
#include <memory>
#include <chrono>
#include <sstream>

#include "Planet.h"
#include "Options.h"
#include "Number.h"

class PlanetsController {
protected:
    
    using number = number;
    using duration = std::chrono::duration<number>;
    constexpr static number gravity =  6.67384e-11;
    //without sync
    duration time{};
	duration time_peer_frame{};

    std::unique_ptr<number[]> x;
    std::unique_ptr<number[]> y;
    std::unique_ptr<number[]> speed_x;
    std::unique_ptr<number[]> speed_y;
    std::unique_ptr<number[]> accel_x;
    std::unique_ptr<number[]> accel_y;
    //const field without sync
    const size_t count;
    std::unique_ptr<const number[]> mass;
    std::unique_ptr<const number[]> density;
    //with their own sync
    std::unique_ptr<Options[]> planets_options;
    Options global_options;

public:
    PlanetsController(size_t count, number* mass, number* x, number* y, number* speed_x, number* speed_y, number* density , Options* planets_opts, const Options &global_opts) noexcept :
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
        time_peer_frame{},
		accel_x( new number[count] ),
		accel_y( new number[count] )
    {
    }
    PlanetsController(PlanetsController&&from) noexcept:
        count(from.count),
        mass(std::move(from.mass)),
        x(std::move(from.x)),
        y(std::move(from.y)),
        speed_x(std::move(from.speed_x)),
        speed_y(std::move(from.speed_y)),
        density(std::move(from.density)),
        planets_options(std::move(from.planets_options)),
        global_options(std::move(from.global_options)),
        time(from.time),
        time_peer_frame(from.time_peer_frame),
		accel_x(std::move( from.accel_x )),
		accel_y(std::move( from.accel_y ))
    {
    };

    Planet operator[](size_t index) const {
        return Planet(GetOption<std::string>(planets_options[index], "name"), mass[index], density[index], x[index], y[index], speed_x[index], speed_y[index], 0, 0);
    }
    
    void SetFrameTime(duration dtime) noexcept
    {
		time_peer_frame = dtime;
	}

    std::string GetTimeDump() const;

    void Play(duration delta);
private:
    void NextFrame(duration elapsed);
};
