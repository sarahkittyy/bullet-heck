#include "Bullets/Bullet.hpp"

namespace Bullet
{

Bullet::Bullet()
	: mPosition(0, 0),
	  mVelocity(0, 0),
	  msLived(0),
	  mAlive(true)
{
}

void Bullet::setWindow(sf::RenderWindow* window)
{
	mWindow = window;
}

void Bullet::init()
{
}

bool Bullet::contains(sf::Vector2f pos)
{
	//Translate the point to body coords.
	pos -= mPosition;
	//For every box body..
	for (auto& body : mBoxBodies)
	{
		if (body.getGlobalBounds().contains(pos))
		{
			return true;
		}
	}
	//For every circlular body.
	for (auto& body : mCircularBodies)
	{
		//Get the center position.
		sf::Vector2f center = body.getPosition();
		//Get the radius
		float radius = body.getSize().x / 2.0f;
		//Get the distance from the center to pos.
		float dist = std::abs(std::hypotf(pos.x - center.x, pos.y - center.y));
		//If the radius is greater than or equal to the distance, they're colliding.
		if (dist <= radius)
		{
			return true;
		}
	}
	//Nothing is colliding.
	return false;
}

bool Bullet::intersects(sf::FloatRect body)
{
	//Translate the rect to body coords.
	sf::FloatRect rect = sf::Transform().translate(-mPosition).transformRect(body);

	//For every rectangular body.
	for (auto& rbody : mBoxBodies)
	{
		//Return true if they intersect.
		if (rbody.getGlobalBounds().intersects(rect))
		{
			return true;
		}
	}
	//For every circular body..
	for (auto& cbody : mCircularBodies)
	{
		//TODO-- implement actual circle->rect collision
		//For now, we'll just pretend these are rectangles.
		//True if they intersect.
		if (cbody.getGlobalBounds().intersects(rect))
		{
			return true;
		}
	}
	//Nothing intersects.
	return false;
}

void Bullet::update(float msElapsed)
{
	//Increment how long the bullet has lived for.
	msLived += static_cast<size_t>(std::max(msElapsed, 1.f));

	pushScriptData();
	//Push some extra globals
	mScript->push("_G", "msElapsed", msElapsed);
	//Run the script
	mScript->run();
}

void Bullet::pushScriptData()
{
	//GETTERS
	//position
	mScript->push<float>("Bullet", "getPos", {{"x", getPosition().x}, {"y", getPosition().y}});
	//velocity
	mScript->push<float>("Bullet", "getVel", {{"x", getVelocity().x}, {"y", getVelocity().y}});
	//Life
	mScript->push("Bullet", "getLife", getMsLived());

	//Window size
	mScript->push<unsigned>("_G", "winsize", {{"x", mWindow->getSize().x}, {"y", mWindow->getSize().y}});

	//SETTERS
	//position
	mScript->function("Bullet", "setPos", [this](float x, float y) -> void { this->setPosition({x, y}); });
	//vel
	mScript->function("Bullet", "setVel", [this](float x, float y) -> void { this->setVelocity({x, y}); });
	//delete
	mScript->function("Bullet", "delete", [this]() -> void { this->del(); });
}

void Bullet::setPosition(sf::Vector2f new_pos)
{
	mPosition = new_pos;
}

sf::Vector2f Bullet::getPosition()
{
	return mPosition;
}

void Bullet::setVelocity(sf::Vector2f new_vel)
{
	mVelocity = new_vel;
}

sf::Vector2f Bullet::getVelocity()
{
	return mVelocity;
}

size_t Bullet::getMsLived()
{
	return msLived;
}

void Bullet::del()
{
	mAlive = false;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Translate all bodies by the current position.
	states.transform.translate(mPosition.x, mPosition.y);
	//Draw all box and circular bodies.
	for (auto& i : mBoxBodies)
	{
		target.draw(i, states);
	}
	for (auto& i : mCircularBodies)
	{
		target.draw(i, states);
	}
}

bool Bullet::shouldDelete()
{
	return !mAlive;
}

sf::RectangleShape* Bullet::createBoxBody()
{
	mBoxBodies.emplace_back(sf::RectangleShape());
	sf::RectangleShape* back = &mBoxBodies.back();
	return back;
}

sf::RectangleShape* Bullet::createCircularBody()
{
	mCircularBodies.emplace_back(sf::RectangleShape());
	sf::RectangleShape* back = &mCircularBodies.back();
	return back;
}

void Bullet::setScript(Script::Script* s)
{
	//Set the script
	mScript = s;
}

}