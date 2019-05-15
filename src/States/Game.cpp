#include "States/Game.hpp"

namespace States
{

void Game::init()
{
	f.init(window(), resources());
	m.init(&f);

	auto b = m.createBullet("default");
}

void Game::update(float msElapsed)
{
	m.update(msElapsed);
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m, states);
}

}