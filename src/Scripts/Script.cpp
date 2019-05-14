#include "Scripts/Script.hpp"

namespace Script
{

Script::Script()
{
}

void Script::init(std::string path)
{
	//Load the file from path.
	mState.open_libraries(sol::lib::base, sol::lib::math);
	mState.do_file(path);
}

void Script::run()
{
	//Get the iterate() function (the main entry point.)
	auto function = mState["iterate"];
	//If it's not valid, throw an error.
	if (!function.valid())
	{
		throw std::runtime_error("Sol function `iterate` is not valid!");
	}
	//Otherwise, run it.
	function();
}

sol::table Script::getCreateTable(std::string name)
{
	//Make the table if it's not valid.
	if (!mState[name].valid() || mState[name].get_type() != sol::type::table)
	{
		mState[name] = mState.create_table();
	}
	//Return the table.
	return mState[name];
}

}