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