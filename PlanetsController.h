#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <chrono>
#include <vector>
#include <sstream>

#include "Planet.h"
#include "Options.h"
#include "PlanetHandle.h"

template<typename number>
class PlanetsController {
protected:

    constexpr static number gravity =  6.67384e-11;

    number* mass{};
    number* x{};
    number* y{};
    number* speed_x{};
    number* speed_y{};
    number* accel_x{};
    number* accel_y{};
    number* density{};
    std::string* name{};
    const size_t count;
    Options options;

    std::chrono::duration<number> time{};
	std::chrono::duration<number> time_peer_takt; // time to one takt

    std::vector<std::pair<size_t, std::weak_ptr<PlanetHandle<number>>>> handles;

    PlanetsController(size_t count) :
        count(count)
    {
        try {
            mass = new number[count];
            x = new number[count];
            y = new number[count];
            speed_x = new number[count];
            speed_y = new number[count];
            accel_x = new number[count];
            accel_y = new number[count];
            density = new number[count];
            name = new std::string[count];
        }
        catch (...) {
            delete[] mass;
            delete[] x;
            delete[] y;
            delete[] speed_x;
            delete[] speed_y;
            delete[] accel_x;
            delete[] accel_y;
            delete[] density;
            delete[] name;
            throw;
        }
    }
public:
    PlanetsController(const PlanetsController<number>&) = delete;
    PlanetsController(PlanetsController<number>&&) = delete;
    ~PlanetsController()
    {
        delete[] mass;
        delete[] x;
        delete[] y;
        delete[] speed_x;
        delete[] speed_y;
        delete[] accel_x;
        delete[] accel_y;
        delete[] density;
        delete[] name;
    }

    size_t Count() const { return count; };

    const Options& Options() const { return options; };

    Planet<number> operator [](size_t i) const {
        return Planet<number>(name[i],mass[i],density[i], x[i], y[i], speed_x[i], speed_y[i], accel_x[i], accel_y[i]);
    }

    void ConnectHandle(size_t planet_index, std::shared_ptr<PlanetHandle<number>> handle) {
        handle->Reset((*this)[planet_index]);
        handles.emplace_back(planet_index, std::move(handle));
    }

public:
    void ExecuteHandles() {
        for(auto&& [planet_index,handle] : handles)
            handle->lock()->Get((*this)[planet_index]);
    }
    void ClearHandles() {
        for(auto&& [planet_index,handle] : handles)
            handle->lock()->Reset((*this)[planet_index]);
    }
	
    void SetTaktTime(std::chrono::duration<number> dtime)
    {
		time_peer_takt = dtime;
	}

    std::string GetTimeDump() {
        size_t second = time.count();
        size_t minutes = second / 60;
		size_t hours = minutes/60;
		size_t days = hours/24;
		size_t years = days/365;

		second %= 60;
		minutes %= 60;
		hours %= 24;
		days %=  365;

		std::stringstream ss;
		 ss<< "Years:  " << years << std::endl
		   << "Days:   " << days << std::endl
		   << "Hours:  " << hours << std::endl
		   << "Minutes:" << minutes << std::endl
		   << "Second: " << second << std::endl;
		return ss.str();
    }

	void Calculate(std::chrono::duration<number> delta) {
		size_t takts = delta / time_peer_takt;
		std::chrono::duration<number> least = delta - time_peer_takt * takts;
		for (size_t i = 0; i < takts; i++)
			CalculateStep(time_peer_takt);
		CalculateStep(least);
	}

    void CalculateStep(std::chrono::duration<number> delay) {

        for (size_t i = 0; i < count; i++) {
            accel_x[i] = 0; accel_y[i] = 0;
        }

        for (size_t i = 0; i < count; i++) {
            for (size_t j = 0; j < count; j++) {
                if (i == j) continue;
                number dx = x[j] - x[i], dy = y[j] - y[i];
                number distance_squad = dx * dx + dy * dy;
                number accel = mass[j] * gravity / distance_squad;
                number distance = sqrt(distance_squad);
                accel_x[i] += accel * dx / distance;
                accel_y[i] += accel * dy / distance;
            }
        }

        for (size_t i = 0; i < count; i++) {
			speed_x[i] += accel_x[i] * delay.count();
			speed_y[i] += accel_y[i] * delay.count();
			x[i] += speed_x[i] * delay.count();
			y[i] += speed_y[i] * delay.count();
        }
        time += delay;
    }
public:
    [[deprecated]]
    static std::unique_ptr<PlanetsController<number>> FromFile(std::string filename) {
        std::ifstream file;
        file.open(filename.c_str());

        size_t count;
        file >> count;
        auto planets = new PlanetsController<number>(count);
        std::string delta_time, orbit_len, vector_scale, default_scale;
        file >> delta_time >> orbit_len >>vector_scale >> default_scale;

        for (size_t i = 0; i < count; i++) {
            if (!file)std::exit(1);
            file >> planets->name[i] >> planets->mass[i] >> planets->density[i] >> planets->x[i] >> planets->y[i] >> planets->speed_x[i] >> planets->speed_y[i];
        }

        file.close();
        return std::unique_ptr<PlanetsController<number>>(planets);
    }
};
