#pragma once

#include <mutex>

#include "PlanetHandle.h"
#include "RenderHandle.h"
#include "Font.h"

class InfoHandle : public PlanetHandle  {
public:
	std::mutex mutex;
	Planet start;
	Planet prevframe;
	number speed;

	number distance;
public:
	InfoHandle() {};
	virtual ~InfoHandle() {};
	virtual void Update(Planet planet , std::chrono::duration<number> delay , std::chrono::duration<number> time_point) 
	{
		std::lock_guard guard(mutex);
		prevframe = planet;
		speed = planet.GetSpeedV().Module();
		distance += planet.GetPositionV().Module();
	};
	virtual void Reset(Planet planet) 
	{
		std::lock_guard guard(mutex);
		start = planet;
	};
	void Lock() { mutex.lock(); };
	void Unlock() { mutex.unlock (); };
};

class InfoRender : public RenderHandle  {
	std::shared_ptr<InfoHandle> proxy;
public:
	InfoRender():
		proxy(new InfoHandle())
	{}
	virtual ~InfoRender() {

	}
	virtual void Render(sf::RenderWindow& window , const PTransformer &pt)
	{
		std::lock_guard guard(this->proxy->mutex);


	}
	virtual std::shared_ptr<PlanetHandle> GetPlanetHandle() { return std::dynamic_pointer_cast<PlanetHandle>(proxy); };
};
