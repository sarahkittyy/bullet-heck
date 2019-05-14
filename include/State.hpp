#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

#include "ResourceManager.hpp"

/**
 * @brief State machine forward declaration.
 * 
 */
class StateMachine;

/**
 * @brief A state class for an application FSM
 * 
 */
class State : public sf::Drawable
{
public:
	//Function type to call to change the state machine's state from the active state itself.
	typedef std::function<void(State*)> StateChanger;

	/**
	 * @brief Construct the state.
	 * 
	 */
	State();

	/**
	 * @brief Function called after state is configured with the window, resource manager, etc..
	 * 
	 */
	virtual void init();

	/**
	 * @brief Destroy the State object
	 * 
	 */
	virtual ~State();

	/**
	 * @brief Update the state.
	 * 
	 * @param msElapsed The milliseconds since the last update.
	 * 
	 */
	virtual void update(float msElapsed);

	/**
	 * @brief Get the Background Color of the state.
	 * 
	 * @return sf::Color The state's background color.
	 */
	virtual sf::Color getBackgroundColor();

protected:
	/**
	 * @brief Returns a reference to the app window to the child state.
	 * 
	 * @return sf::RenderWindow* A const pointer to the app window.
	 */
	sf::RenderWindow* const window();

	/**
	 * @brief Returns a const pointer to the resource manager.
	 * 
	 * @return ResourceManager* const The resource manager.
	 */
	ResourceManager* const resources();

	/**
	 * @brief Used to change the app state using mChangeState
	 * 
	 * @param new_state The new app state.
	 */
	void changeState(State* new_state);

private:
	/**
	 * @brief Draw whatever must be drawn in this state.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Pointer to the app window.
	 * 
	 */
	sf::RenderWindow* mWindow;

	/**
	 * @brief Pointer to the app resource manager.
	 * 
	 */
	ResourceManager* mResources;

	/**
	 * @brief The function reference to change the app's state.
	 * 
	 */
	StateChanger mChangeState;

	/**
	 * @brief Used by StateMachine to set the state's window ptr.
	 * 
	 * @param window The window ptr to use for the state.
	 */
	void setWindow(sf::RenderWindow* window);

	/**
	 * @brief Used by StateMachine to set the state's resource manager pointer.
	 * 
	 * @param rm The app resource manager. 
	 */
	void setResourceManager(ResourceManager* rm);

	/**
	 * @brief Used by StateMachine to set the state-changing function.
	 * 
	 * @param sc The state changer.
	 */
	void setStateChanger(StateChanger sc);

	//Allows statemachine to access setWindow() and setResourceManager()
	friend class StateMachine;
};