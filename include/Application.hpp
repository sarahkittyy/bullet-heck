#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceManager.hpp"

#include "StateMachine.hpp"
#include "States/States.hpp"

/**
 * @brief Main app class
 * 
 */
class Application
{
public:
	/**
	 * @brief Default constructor, initializes objects
	 * 
	 */
	Application();

	/**
	 * @brief Runs the application.
	 * 
	 * @return int The program's exit code.
	 */
	int run();

private:
	/**
	 * @brief The main app window.
	 * 
	 */
	sf::RenderWindow mWindow;

	/**
	 * @brief The app resource manager.
	 * 
	 */
	ResourceManager mResources;

	/**
	 * @brief The application state.
	 * 
	 */
	StateMachine mAppState;
};