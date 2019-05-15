#pragma once

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <unordered_map>

#include "sol/sol.hpp"

namespace Script
{

/**
 * @brief A generic lua script.
 * 
 */
class Script
{
public:
	/**
	 * @brief Construct the script.
	 * 
	 */
	Script();

	/**
	 * @brief Initialize the script with the lua script at the given path.
	 * 
	 * @param path The path to the script to use. 
	 */
	void init(std::string path);

	/**
	 * @brief Run the function.
	 * 
	 * @tparam Args The type of args to pass to the lua iterate() function itself.
	 * @param args The arguments to pass to iterate(..).
	 */
	template <typename... Args>
	void run(Args... args)
	{
		//Get the iterate() function (the main entry point.)
		auto function = mState["iterate"];
		//If it's not valid, throw an error.
		if (!function.valid())
		{
			throw std::runtime_error("Sol function `iterate` is not valid!");
		}
		//Otherwise, run it.
		function(args...);
	}

	/**
	 * @brief Push a function to the lua state.
	 * This is used for setters and getters, such as set/getPos(),
	 * so that the lua state doesn't have to be modified on every lua script run. 
	 * 
	 * @tparam Fn Lambda expression.
	 * @param table The name of the table to push the function into
	 * @param name The name of the function
	 * @param value The function itself
	 */
	template <typename Fn>
	void function(std::string table, std::string name, const Fn& value)
	{
		//Get the table
		sol::table t = getCreateTable(table);
		//Set the table function
		t.set_function(name, value);
		//Push the table to the state.
		mState[table] = t;
	}

private:
	/**
	 * @brief The lua state.
	 * 
	 */
	sol::state mState;

	/**
	 * @brief Get/Create a table in mState and return it.
	 * 
	 * @param name The name of the table.
	 * @return sol::table A copy of that table.
	 */
	sol::table getCreateTable(std::string name);
};

}