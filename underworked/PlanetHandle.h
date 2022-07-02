#pragma once

#include <chrono>

#include "Planet.h"

class PlanetHandle
{
public:
	virtual ~PlanetHandle() {};
	virtual void Update(Planet planet , std::chrono::duration<number> delay, std::chrono::duration<number> time_point) {};
	virtual void Reset(Planet planet) {};
};
