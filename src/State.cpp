#include "State.hpp"

State::State()
{
}

void State::init()
{
}

State::~State()
{
}

sf::Color State::getBackgroundColor()
{
	return sf::Color::White;
}

void State::update(float msElapsed)
{
}

sf::RenderWindow* const State::window()
{
	return mWindow;
}

ResourceManager* const State::resources()
{
	return mResources;
}

void State::changeState(State* new_state)
{
	mChangeState(new_state);
}

void State::setWindow(sf::RenderWindow* window)
{
	mWindow = window;
}

void State::setResourceManager(ResourceManager* rm)
{
	mResources = rm;
}

void State::setStateChanger(StateChanger sc)
{
	mChangeState = sc;
}

void State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}