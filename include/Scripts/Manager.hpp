#pragma once

#include <unordered_map>

#include "Scripts/Script.hpp"

#include "sol/sol.hpp"

namespace Script
{

/**
 * @brief Similar to resource manager, helping keep each script file loaded only once in memory.
 * 
 * @see include/ResourceManager.hpp
 */
class Manager
{
public:
	/**
	 * @brief Get a pointer to the script with the given path.
	 * 
	 * @param path The path to the script.
	 * @return Script* A pointer to that script..
	 */
	Script* script(std::string path);

private:
	/**
	 * @brief The internal map of scripts.
	 * 
	 */
	std::unordered_map<std::string, Script> mScripts;
};

}