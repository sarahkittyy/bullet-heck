#include "Bullets/Factory.hpp"

namespace Bullet
{

void Factory::init(sf::RenderWindow* window, ResourceManager* resources, Script::Manager* sm)
{
	//Init the window pointer.
	mWindow = window;
	//Init the resource manager.
	mResources = resources;
	//Init the script manager.
	mScripts = sm;

	namespace fs = std::filesystem;
	using nlohmann::json;

	//Iterate over all files in resource/bullets/defs
	for (auto& def : fs::directory_iterator("resource/bullets/defs"))
	{
		//Continue if this file is not a .json file.
		if (def.path().extension().string() != ".json")
		{
			continue;
		}

		//Get the name & data.
		std::string name = def.path().stem();
		json data		 = getData(def.path());

		//Store the name & data.
		mBulletDefinitions[name] = data;
	}
}

std::shared_ptr<Bullet> Factory::createBullet(std::string definition)
{
	using nlohmann::json;

	//Get the bullet data.
	json data;
	try
	{
		data = mBulletDefinitions.at(definition);
	}
	catch (const std::out_of_range& e)
	{
		sf::err() << "Could not load bullet definition "
				  << definition
				  << ".\nException: "
				  << e.what() << std::endl;
		return nullptr;
	}

	//Create the return bullet.
	std::shared_ptr<Bullet> b(new Bullet());
	
	//Set the bullet window pointer.
	b->setWindow(mWindow);

	//Load the bullet bodies
	loadBulletBodies(b, data);
	//Load the bullet script
	b->setScript(
		mScripts->script(
			"resource/bullets/scripts/" +
			data.at("behavior").get<std::string>()));


	//Init the bullet
	b->init();

	//Return the created bullet.
	return b;
}

void Factory::loadBulletBodies(std::shared_ptr<Bullet> b, nlohmann::json& data)
{
	using nlohmann::json;

	//For every bullet body...
	for (auto& i : data.at("bodies").get<json::array_t>())
	{
		//Get the type.
		std::string type = i.at("type");
		//Get the texture.
		sf::Texture* t = mResources->texture(
			"resource/bullets/graphics/" +
			i.at("image").get<std::string>());
		//Get the body offset from bullet position
		sf::Vector2f offset = {i.at("offset")[0], i.at("offset")[1]};

		if (type == "circle")
		{
			float radius = i.at("radius");   //Bullet radius
			//Create & configure the body.
			sf::RectangleShape* body = b->createCircularBody();
			body->setTexture(t, true);
			body->setSize(sf::Vector2f(radius * 2, radius * 2));
			body->setOrigin(
				body->getLocalBounds().width / 2.f, body->getLocalBounds().height / 2.f);
			body->setPosition(offset);
		}
		else if (type == "box")
		{
			//Box size
			sf::Vector2f size = {i.at("size")[0], i.at("size")[1]};
			//Create & configure
			sf::RectangleShape* body = b->createBoxBody();
			body->setTexture(t, true);
			body->setSize(size);
			body->setOrigin(
				body->getLocalBounds().width / 2.f, body->getLocalBounds().height / 2.f);
			body->setPosition(offset);
		}
		else
		{
			throw std::runtime_error("Bullet body type " + type + "not found.");
		}
	}
}

nlohmann::json Factory::getData(std::string path)
{
	using nlohmann::json;

	//Open the file
	std::ifstream file(path);
	if (!file)   //If the file didn't load, return an empty json object
	{
		return json();
	}
	//Load the data from the file..
	json data = json::parse(std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()));

	//Return the data.
	return data;
}

}