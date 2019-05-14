#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "Scripts/Script.hpp"

namespace Bullet
{
//Forward declaration of factory class.
class Factory;

/**
 * @brief A graphical, scriptable, update-able bullet.
 * 
 */
class Bullet : public sf::Drawable
{
public:
	/**
	 * @brief Construct a new Bullet object
	 * 
	 */
	Bullet();

	/**
	 * @brief Set the bullet's new base position.
	 * 
	 * @param new_pos The new bullet position.
	 */
	void setPosition(sf::Vector2f new_pos);

	/**
	 * @brief Set the bullet's new velocity.
	 * 
	 * @param new_vel The new bullet velocity.
	 */
	void setVelocity(sf::Vector2f new_vel);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	size_t getMsLived();

	/**
	 * @brief Update the bullet.
	 * 
	 * @param msElapsed The milliseconds since the last frame.
	 */
	void update(float msElapsed);

	/**
	 * @brief True if the bullet should be deleted.
	 * 
	 * @remarks Usually set by the lua script.
	 * 
	 */
	bool shouldDelete();

	/**
	 * @brief Flag the bullet for deletion.
	 * 
	 */
	void del();

	/**
	 * @brief Checks if any of the bullet boundary boxes contain point pos.
	 * 
	 * @param pos The position to check
	 * 
	 * @return True if the position is contained. 
	 */
	bool contains(sf::Vector2f pos);

	/**
	 * @brief Checks if any of the bullet boundary boxes intersect the given rectangle.
	 * 
	 * @param body The AABB collision to check
	 * @return true If the bullet intersects that body.
	 * @return false Otherwise.
	 */
	bool intersects(sf::FloatRect body);

private:
	/**
	 * @brief SFML's draw() override. Draws all attached bodies.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief For the bullet factory -- initializes the bullet.
	 * 
	 */
	void init();

	/**
	 * @brief Push live script data, such as position and data.
	 * 
	 */
	void pushScriptData();

	/**
	 * @brief The bullet behavior script.
	 * 
	 */
	Script::Script* mScript;

	/**
	 * @brief The position of the bullet, where offset bodies are centered around.
	 * 
	 */
	sf::Vector2f mPosition;

	/**
	 * @brief The bullet's velocity.
	 * 
	 */
	sf::Vector2f mVelocity;

	/**
	 * @brief How long the bullet has been alive for, in ms.
	 * 
	 */
	size_t msLived;

	/**
	 * @brief Whether or not the bullet is alive.
	 * 
	 */
	bool mAlive;

	/**
	 * @brief All the rectangular bodies attached to this bullet.
	 * 
	 */
	std::vector<sf::RectangleShape> mBoxBodies;

	/**
	 * @brief All the circular bodies attached to this bullet.
	 * 
	 * @remarks Bodies are stored as rectangleshapes due to the nature of textures, but will be calculated in intersects() and contains() as if they were circles.
	 * 
	 * //TODO: Refactor this into one sf::VertexArray, for higher performance.
	 * 
	 */
	std::vector<sf::RectangleShape> mCircularBodies;

	/**
	 * @brief Create a new uninitialized rectangular body.
	 * 
	 * @return sf::RectangleShape* A pointer to that body.
	 */
	sf::RectangleShape* createBoxBody();

	/**
	 * @brief Create a new uninitialized circular body.
	 * 
	 * @return sf::RectangleShape* A pointer to that body.
	 */
	sf::RectangleShape* createCircularBody();

	/**
	 * @brief Set the bullet's behavior script.
	 * 
	 * @param s A pointer to the script to use.
	 */
	void setScript(Script::Script* s);

	/**
	 * @brief Pointer to the app window.
	 * 
	 */
	sf::RenderWindow* mWindow;

	/**
	 * @brief Set the pointer to the app window.
	 * 
	 * @param window The window pointer.
	 */
	void setWindow(sf::RenderWindow* window);

	//Allows the factory to access private bullet configuration functions.
	friend class Factory;
};

}