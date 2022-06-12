#pragma once

#include <chrono>

#include "Planet.h"

template <typename number>
class PlanetHandle
{
public:
	virtual ~PlanetHandle() {};
	virtual void Update(Planet<number> planet , std::chrono::duration<number> delay) {};
	virtual void Reset(Planet<number> planet) {};
};

template <typename number>
class InfoHandle : PlanetHandle<number>  {
public:
	virtual ~InfoHandle() {};
	virtual void Update(Planet<number> planet , std::chrono::duration<number> delay) {};
	virtual void Reset(Planet<number> planet) {};

	number GetMaxSpeed();
	number GetMinSpeed();
	std::chrono::duration<number> GetPeriod();
	number GetAllDistance();
	number GetOrbitLen();
};