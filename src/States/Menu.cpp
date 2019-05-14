#include "States/Menu.hpp"

namespace States
{
sf::Color Menu::getBackgroundColor()
{
	return sf::Color::Black;
}

void Menu::update(float msElapsed)
{
	changeState(new Game());
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

}