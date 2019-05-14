#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "sol/sol.hpp"

#include "States/States.hpp"

#include "Bullets/Bullets.hpp"

#include "Scripts/Scripts.hpp"

namespace States
{

class Game : public State
{
public:
	void init();

	void update(float msElapsed);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Script::Manager sm;

	Bullet::Factory f;
	Bullet::Manager m;
};

}