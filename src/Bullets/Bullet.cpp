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
	initScript();
}

void Bullet::initScript()
{
	//GETTERS
	//msLived
	mScript.function("Bullet", "getLife", [this]() {
		return this->getMsLived();
	});
	//position
	mScript.function("Bullet", "getPos", [this]() {
		return sol::as_table(
			std::unordered_map<std::string, float>{{"x", this->getPosition().x}, {"y", this->getPosition().y}});
	});
	//velocity
	mScript.function("Bullet", "getVel", [this]() {
		return sol::as_table(
			std::unordered_map<std::string, float>{{"x", this->getVelocity().x}, {"y", this->getVelocity().y}});
	});

	//SETTERS
	//position
	mScript.function("Bullet", "setPos", [this](float x, float y) {
		this->setPosition({x, y});
	});
	//velocity
	mScript.function("Bullet", "setVel", [this](float x, float y) {
		this->setVelocity({x, y});
	});

	//OTHER
	//delete
	mScript.function("Bullet", "delete", [this]() {
		this->del();
	});

	//GLOBALS
	mScript.function("_G", "winsize", [this]() {
		//what a mess of a line of code oml
		return sol::as_table(std::unordered_map<std::string, size_t>{{"x", this->mWindow->getSize().x}, {"y", this->mWindow->getSize().y}});
	});
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

float Bullet::getMsLived()
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

void Bullet::setScript(std::string file)
{
	//Set the script
	mScript.init(file);
}
}