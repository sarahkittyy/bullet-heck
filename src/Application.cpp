#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(800, 600), "Bullet Heck"),
	  mResources(),
	  mAppState(&mWindow, &mResources, new States::Menu())
{
}

int Application::run()
{
	sf::Clock appClock;   //The application time manager.

	while (mWindow.isOpen())   //App loop
	{
		//Poll events
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{
			default:
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
			}
		}
		//Time elapsed since last frame.
		float msElapsed = appClock.restart().asSeconds() * 1000.f;

		//Update the app state.
		mAppState.update(msElapsed);

		//Clear the window
		mWindow.clear(mAppState.getState()->getBackgroundColor());

		//Draw the app state.
		mWindow.draw(mAppState);

		//Display the drawn-to window
		mWindow.display();
	}

	return 0;
}