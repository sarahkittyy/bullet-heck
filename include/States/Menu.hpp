#pragma once

#include <SFML/Graphics.hpp>

#include "States/States.hpp"

namespace States
{

/**
 * @brief Main menu state
 * 
 */
class Menu : public State
{
public:
	/**
	 * @brief Update the menu
	 * 
	 * @param msElapsed Time since last frame
	 */
	void update(float msElapsed);

	/**
	 * @brief Get the Background Color of the state
	 * 
	 */
	sf::Color getBackgroundColor();

private:
	/**
	 * @brief Draw the state's drawable objects
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}