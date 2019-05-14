#pragma once

#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <streambuf>
#include <string>

#include "nlohmann/json.hpp"
#include "sol/sol.hpp"

#include "Bullets/Bullet.hpp"

#include "ResourceManager.hpp"

#include "Scripts/Scripts.hpp"

namespace Bullet
{

/**
 * @brief Reads in all bullet defs from resource/bullets/defs,
 * loading them into memory, and allowing them to be created with
 * createBullet(def_name)
 * 
 */
class Factory
{
public:
	/**
	 * @brief Initializes mBulletDefinitions from all json files
	 * in resource/bullets/defs
	 * 
	 * @param window The application window.
	 * @param resources The application resource manager.
	 * @param sm The application script manager.
	 */
	void init(sf::RenderWindow* window, ResourceManager* resources, Script::Manager* sm);

	/**
	 * @brief Creates a new bullet, using the given definition name.
	 * 
	 * @remarks See resource/bullets/defs for definitions.
	 * 
	 * @param definition The bullet definition name.
	 * 
	 * @return std::shared_ptr<Bullet> The created bullet.
	 */
	std::shared_ptr<Bullet> createBullet(std::string definition);

private:
	/**
	 * @brief The main app window.
	 * 
	 */
	sf::RenderWindow* mWindow;

	/**
	 * @brief The application resource manager.
	 * 
	 */
	ResourceManager* mResources;

	/**
	 * @brief The app script manager.
	 * 
	 */
	Script::Manager* mScripts;

	/**
	 * @brief A map of bullet names to their definitions.
	 * 
	 */
	std::unordered_map<std::string, nlohmann::json> mBulletDefinitions;

	/**
	 * @brief Load the bullet's physical collision bodies.
	 * 
	 * @param b The bullet to load the bodies into
	 * @param data The bullet's data.
	 */
	void loadBulletBodies(std::shared_ptr<Bullet> b,
						  nlohmann::json& data);

	/**
	 * @brief Get the json data in the given file.
	 * 
	 * @param path The path to the file.
	 * @return json The json data contained in that file.
	 */
	nlohmann::json getData(std::string path);
};

}