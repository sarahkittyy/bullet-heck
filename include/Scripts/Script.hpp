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
 * @brief A generic lua script, for use with the script manager.
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
	 */
	void run();

	/**
	 * @brief Push data into a lua global table. 
	 * 
	 * @tparam T Some uniform value type that all properties of the return value return.
	 * 
	 * @param table The table to put the property into.
	 * @param name The name of the property.
	 * @param returns The list of data properties
	 * 
	 * @remarks table being "_G" will make `name()` global.
	 * 
	 * @remarks For example, if:
	 * table = table1
	 * name = data,
	 * returns = unordered_map is {x, 1},
	 * then it will be accessible in lua as table1.data().x == 1 
	 */
	template <typename T>
	void push(std::string table, std::string name, std::unordered_map<std::string, T> returns)
	{
		//Create the table and set the property.
		sol::table t = getCreateTable(table);
		//Create the return value with the values in `returns`
		sol::table ret = mState.create_table();
		for (auto& [key, value] : returns)
		{
			//Push the value into the table.
			ret[key] = value;
		}
		//Set the function `name()` to return table `ret`
		t.set_function(name, [ret]() -> decltype(ret) { return ret; });
	}

	/**
	 * @brief Push a value in the given table, under the given property name, with the given value.
	 * 
	 * @tparam T The value to return from the property getter.
	 * 
	 * @param table The table to push `name` into.
	 * @param name The name of the property.
	 * @param returns The value that name will equal.
	 * 
	 * @remarks table being "_G" will make `name` global.
	 * 
	 * @see push() (the other overload).
	 */
	template <typename T>
	void push(std::string table, std::string name, const T& returns)
	{
		//Create the table & set the property.
		sol::table t  = getCreateTable(table);
		t[name]		  = [returns]() -> T { return returns; };
		mState[table] = t;
	}

	/**
	 * @brief Append a function to the script.
	 * 
	 * @tparam Fn The lambda function type to append (usually deduced)
	 * 
	 * @param table The table to append the function to ("_G" for global.)
	 * @param name The name of the function. 
	 * @param fn The function itself.
	 */
	template <typename Fn>
	void function(std::string table, std::string name, const Fn& fn)
	{
		//Create the table.
		sol::table t = getCreateTable(table);
		//Set the function
		t.set_function(name, fn);
		//Set the table.
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