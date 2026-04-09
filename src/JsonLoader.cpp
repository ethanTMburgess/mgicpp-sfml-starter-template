#include "JsonLoader.h"

nlohmann::json JsonLoader::loadJson(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "Error opening file" << path << std::endl;
		throw std::runtime_error("JSON file cannot be opened");
	}

	try 
	{
		nlohmann::json j;
		file >> j;
		return j;
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "Json parse error" << path << std::endl;
		std::cerr << e.what() << std::endl;
		throw;
	}
	

	
}

Map JsonLoader::LoadMapFromJson(std::string path)
{
	nlohmann::json j = loadJson(path);
	

	int tileSize = j.at("tileSize").get<int>();
	int mapWidth = j.at("mapWidth").get<int>();
	int mapHeight = j.at("mapHeight").get<int>();


	Map map(tileSize, mapWidth, mapHeight);

	if (!map.setSpriteSheet("../../../../Data/Images/spritesheet1.png"))
	{
		std::cout << "error loading sprite sheet" << std::endl;
	}
	

	for (auto& jsonLayer : j.at("layers"))
	{
		std::string name = jsonLayer.at("name").get<std::string>();
		bool collider = jsonLayer.at("collider").get<bool>();

		Layer layer(name, collider);

		for (auto& jsonTile : jsonLayer.at("tiles"))
		{
			int id = std::stoi(jsonTile.at("id").get<std::string>());
			int x = jsonTile.at("x").get<int>();
			int y = jsonTile.at("y").get<int>();

			layer.addTile(Tile(id, x, y, map.GetSpriteSheet()));
		}

		map.AddLayer(std::move(layer));

	}

	return map;
}