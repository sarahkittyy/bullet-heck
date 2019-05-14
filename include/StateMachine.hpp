#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "ResourceManager.hpp"

#include "State.hpp"

/**
 * @brief A state machine for the state class
 * 
 */
class StateMachine : public sf::Drawable
{
public:
	/**
	 * @brief Construct a new StateMachine
	 * 
	 * @param window The main app window.
	 * @param rm The app resource manager.
	 * @param initial_state The initial state.
	 */
	StateMachine(sf::RenderWindow* window, ResourceManager* rm, State* initial_state);

	/**
	 * @brief Set the state of the machine
	 * 
	 * @param new_state The new machine state.
	 */
	void setState(State* new_state);

	/**
	 * @brief Update the active state
	 * 
	 * @param msElapsed The ms elapsed since last frame.
	 */
	void update(float msElapsed);

	/**
	 * @brief Get the currently active state
	 * 
	 * @return State* const A constant pointer to the active state.
	 */
	State* const getState();

private:
	/**
	 * @brief Draw the active state
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief The app window
	 * 
	 */
	sf::RenderWindow* mWindow;

	/**
	 * @brief The app resource manager.
	 * 
	 */
	ResourceManager* mResources;

	/**
	 * @brief The current app state.
	 * 
	 */
	std::shared_ptr<State> mCurrentState;
};