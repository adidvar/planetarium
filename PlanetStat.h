#pragma once

#include <mutex>

#include "PlanetHandle.h"
#include "RenderHandle.h"
#include "Font.h"

template <typename number>
class InfoHandle : public PlanetHandle<number>  {
	std::mutex mutex;
	Planet<number> start;
	Planet<number> prevframe;
	number max_speed = 0;
	number min_speed = std::numeric_limits<number>::max();
	std::chrono::duration<number> min_speed_time;
	std::chrono::duration<number> max_speed_time;
	std::chrono::duration<number> period{};
	number speed;
	
	number distance;
public:
	InfoHandle() {};
	virtual ~InfoHandle() {};
	virtual void Update(Planet<number> planet , std::chrono::duration<number> delay , std::chrono::duration<number> time_point) 
	{
		std::lock_guard guard(mutex);
		prevframe = planet;
		speed = planet.GetSpeedV().Module();
		if (max_speed < speed) {
			max_speed = speed;
			max_speed_time = time_point;
		}
		if (min_speed > speed) {
			min_speed = speed;
			min_speed_time = time_point;
		}
		period = 2 * abs(min_speed_time - max_speed_time);
		distance += planet.GetPositionV().Module();
	};
	virtual void Reset(Planet<number> planet) 
	{
		std::lock_guard guard(mutex);
		start = planet;
	};
	number GetSpeed() {
		std::lock_guard guard(mutex);
		return speed;
	};
	number GetMaxSpeed() {
		std::lock_guard guard(mutex);
		return max_speed;
	};
	number GetMinSpeed() { 
		std::lock_guard guard(mutex);
		return min_speed; 
	};
	std::chrono::duration<number> GetPeriod() {
		std::lock_guard guard(mutex);
		return period;
	};
	number GetAllDistance();
	number GetOrbitLen();
};

template <typename number>
class InfoRender : public RenderHandle<number>  {
	std::shared_ptr<InfoHandle<number>> proxy;
public:
	InfoRender():
		proxy(new InfoHandle<number>())
	{}
	virtual ~InfoRender() {

	}
	virtual void Render(sf::RenderWindow& window , const PTransformer<number> &pt)
	{
		sf::Text text(std::to_string(proxy->GetPeriod().count()), mfont, 20);
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Regular);

		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.width / 2, textRect.height * 1.35f);
		text.setPosition(width / 2, height / 2);
		window.draw(text);
	}
	virtual std::shared_ptr<PlanetHandle<number>> GetPlanetHandle() { return std::dynamic_pointer_cast<PlanetHandle<number>>(proxy); };
};
