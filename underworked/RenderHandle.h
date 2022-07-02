#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "PlanetHandle.h"
#include "PositionTransformer.h"

class RenderHandle {
public:
	virtual ~RenderHandle(){};
	virtual void Render(sf::RenderWindow& window , const PTransformer &pt) = 0;
	virtual std::shared_ptr<PlanetHandle> GetPlanetHandle() = 0;
};