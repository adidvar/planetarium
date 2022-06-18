#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "PlanetHandle.h"
#include "PositionTransformer.h"

template<typename number>
class RenderHandle {
public:
	virtual ~RenderHandle(){};
	virtual void Render(sf::RenderWindow& window , const PTransformer<number> &pt) = 0;
	virtual std::shared_ptr<PlanetHandle<number>> GetPlanetHandle() = 0;
};