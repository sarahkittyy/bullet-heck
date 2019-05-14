#include "Bullets/Manager.hpp"

namespace Bullet
{

void Manager::init(Factory* factory)

{
	mFactory = factory;
}

std::shared_ptr<Bullet> Manager::createBullet(std::string definition)
{
	//Push the bullet, and return it.
	mBullets.push_back(mFactory->createBullet(definition));
	return mBullets.back();
}

void Manager::update(float msElapsed)
{
	//Update all bullets.
	for (auto b = mBullets.begin(); b != mBullets.end();)
	{
		(*b)->update(msElapsed);
		//Delete the bullet if necessary.
		if ((*b)->shouldDelete())
		{
			mBullets.erase(b);
		}
		else   //Increment if the bullet wasn't deleted.
		{
			++b;
		}
	}
}

void Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw all bullets.
	for (auto& b : mBullets)
	{
		target.draw(*b, states);
	}
}

}