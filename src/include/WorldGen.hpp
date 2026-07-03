#ifndef WorldGen_hpp
#define WorldGen_hpp
#include "TileMap.hpp"
#include "Noise.h"
class WorldGen
{ 
public: 

	WorldGen(sf::Vector2f gridSize, int width, int height, std::string texture_file); 
	virtual ~WorldGen(); 

	const std::string generate_terrain(const float& dt) const; 
	const std::string sim_normalTiles(const float& dt) const; 
	 
	
	const int noiseInt(const float& dt, sf::Vector2i range) const; 
	const float noiseFloat(const float& dt, sf::Vector2f range) const; 

private: 
	int width; 
	int height; 
	sf::Vector2f gridsize; 
	int GridsizeX; 
	int GridSizeY; 
	int layers; 
	std::string texture_file; 
	short type; 
	int left; 
	int top; 
	bool collision; 
	
};
#endif 

