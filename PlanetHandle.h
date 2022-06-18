#pragma once

#include <chrono>

#include "Planet.h"

template <typename number>
class PlanetHandle
{
public:
	virtual ~PlanetHandle() {};
	virtual void Update(Planet<number> planet , std::chrono::duration<number> delay, std::chrono::duration<number> time_point) {};
	virtual void Reset(Planet<number> planet) {};
};
