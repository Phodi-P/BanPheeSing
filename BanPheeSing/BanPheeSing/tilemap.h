#pragma once


#include "custom_utility.h"


class TileSet
{
public:
	std::string tilePath;
	sf::Vector2u tileSize;
	TileSet();
	TileSet(std::string, sf::Vector2u);
};
TileSet::TileSet()
{
	//Default
}
TileSet::TileSet(std::string tilePath, sf::Vector2u tileSize)
{
	this->tilePath = tilePath;
	this->tileSize = tileSize;
}

class TileMapData
{
public:
	std::vector<int> mapData;
	std::string layer;
	unsigned int mapWidth;
	unsigned int mapHeight;
	TileMapData();
	TileMapData(std::string, std::vector<int>, int, int);
};
TileMapData::TileMapData()
{
	//Default
}
TileMapData::TileMapData(std::string layer, std::vector<int> mapData, int mapWidth, int mapHeight)
{
	this->layer = layer;
	this->mapData = mapData;
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
}

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const TileSet tilesetTexture, const TileMapData &mapData)
	{
		const int* tiles = &mapData.mapData.front();
		std::string tileset = tilesetTexture.tilePath;
		sf::Vector2u tileSize = tilesetTexture.tileSize;
		unsigned int width = mapData.mapWidth;
		unsigned int height = mapData.mapHeight;

		// load the tileset texture
		if (!m_tileset.loadFromFile(tileset)) return false;

		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		// populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// get the current tile number
				int tileNumber = tiles[i + j * width];

				// find its position in the tileset texture
				int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}

		return true;
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

class Level
{
public:
	std::vector<int> tileMap;
	TileSet tileset;

	TileMapData topData;
	TileMapData midData;
	TileMapData botData;

	TileMap bot;
	TileMap mid;
	TileMap top;

	sf::Vector2f scale;

	std::vector<sf::Vector2f> objPos;
	std::vector<sf::Vector2f> objSize;
	std::vector<int> objType;

	void readFile(std::string, std::string, std::string);
	void readMapData(std::string, TileMapData &);
	void setTileset(TileSet);
	void setScale(sf::Vector2f);
	void update();
	void draw(sf::RenderWindow &);

};

void Level::setScale(sf::Vector2f scale)
{
	this->scale = scale;
}

void Level::readMapData(std::string filePath, TileMapData &output)
{

	std::ifstream map(filePath.c_str());
	std::string txtline;

	//Get map width and height
	getline(map, txtline);
	output.mapHeight = std::stoi(txtline);

	getline(map, txtline);
	output.mapWidth = std::stoi(txtline);

	while (getline(map, txtline))
	{
		std::stringstream lineStream(txtline);
		std::string curStrData;
		if (txtline.find(",") == -1) return;
		for(int i = 0 ; i < output.mapWidth; i++)
		{
			getline(lineStream, curStrData, ',');
			int curData = std::atoi(curStrData.c_str());
			output.mapData.push_back(curData);
		}
	}
	return;
}
void Level::readFile(std::string botPath, std::string midPath, std::string topPath)
{
	readMapData(botPath, botData);
	readMapData(midPath, midData);
	readMapData(topPath, topData);
}
void Level::setTileset(TileSet tileset)
{
	this->tileset = tileset;
}

void Level::update()
{
	bot.load(tileset, botData);
	mid.load(tileset, midData);
	top.load(tileset, topData);

	bot.setScale(scale);
	mid.setScale(scale);
	top.setScale(scale);
}

void Level::draw(sf::RenderWindow &window)
{
	window.draw(bot);
	window.draw(mid);
	window.draw(top);
}
