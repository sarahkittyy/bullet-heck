#include "StateMachine.hpp"

StateMachine::StateMachine(sf::RenderWindow* window, ResourceManager* rm, State* initial_state)
	: mWindow(window),
	  mResources(rm)
{
	setState(initial_state);
}

void StateMachine::setState(State* new_state)
{
	mCurrentState.reset(new_state);
	mCurrentState->setWindow(mWindow);
	mCurrentState->setResourceManager(mResources);
	mCurrentState->setStateChanger(std::bind(
		&StateMachine::setState,
		this,
		std::placeholders::_1));

	//Init the state last, after we've configured the necessary pointers.
	mCurrentState->init();
}

void StateMachine::update(float msElapsed)
{
	//Update the current state
	mCurrentState->update(msElapsed);
}

State* const StateMachine::getState()
{
	return mCurrentState.get();
}

void StateMachine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw the current state.
	target.draw(*mCurrentState, states);
}