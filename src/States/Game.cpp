#include "States/Game.hpp"

namespace States
{

void Game::init()
{
	f.init(window(), resources(), &sm);
	m.init(&f);
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