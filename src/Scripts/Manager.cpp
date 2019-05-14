#include "Scripts/Manager.hpp"

namespace Script
{

Script* Manager::script(std::string path)
{
	//Create the script if it doesn't yet exist.
	if (mScripts.find(path) == mScripts.end())
	{
		mScripts[path] = Script();
		mScripts[path].init(path);
	}
	//Return it.
	return &mScripts[path];
}

}