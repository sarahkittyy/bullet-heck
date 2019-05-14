#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "Bullets/Bullet.hpp"
#include "Bullets/Factory.hpp"

#include "nlohmann/json.hpp"

namespace Bullet
{

/**
 * @brief Stores & updates bullets.
 * 
 */
class Manager : public sf::Drawable
{
public:
	/**
	 * @brief Init the manager.
	 * 
	 * @param factory The bullet factory.
	 */
	void init(Factory* factory);

	/**
	 * @brief Spawn a bullet with the given definition.
	 * 
	 * @param definition The bullet's definition
	 * 
	 * @returns std::shared_ptr<Bullet> A pointer to the created bullet.
	 * 
	 * @remarks See Bullet::Factory::createBullet for definition info.
	 */
	std::shared_ptr<Bullet> createBullet(std::string definition);

	/**
	 * @brief Update the bullet manager.
	 * 
	 * @param msElapsed milliseconds since the last frame.
	 */
	void update(float msElapsed);

private:
	/**
	 * @brief SFML's draw() override -- draws all bullets.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Pointer to the app bullet factory.
	 * 
	 */
	Factory* mFactory;

	/**
	 * @brief The managed bullets.
	 * 
	 */
	std::vector<std::shared_ptr<Bullet>> mBullets;
};

}