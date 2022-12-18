#include "stdafx.h"
#include "Levels.h"

Levels::Levels(sf::Vector2f gridsize)
{
	this->gridSize = gridsize; 
}

Levels::~Levels()
{
}

void Levels::add_level(std::string name)
{
	this->map.insert(level(name, new TileMap(this->gridSize, 100, 100, "Resources/Assets/Tiles/sheet.png")));
	this->map.left.at(name)->setLevelIndex(this->map.left.size());

   std::cout << map.right.at(map.left.at(name)).c_str() << std::endl;

   this->names.push_back(map.right.at(map.left.at(name))); 
 


}

void Levels::add_level(std::string name, int width, int height, std::string texture_file)
{

	this->map.insert(level(name, new TileMap(this->gridSize, width, height, texture_file)));
	this->map.left.at(name)->setLevelIndex(this->map.left.size());     
	


	std::cout << map.right.at(map.left.at(name)).c_str() << std::endl; 
	this->names.push_back(map.right.at(map.left.at(name)));
	//	names.push_back(this->map.right.at(&name).c_str());

	

	std::cout << "adding a new level with the index  " << this->map.left.at(name)->getLevelIndex() << std::endl;
	std::cout << "Level name registered as   " << names.at(1) << std::endl; 

}
	

void Levels::remove_level(std::string index)
{
	//this->levels.erase(index); 
	//this->map.left.erase(index);
}

void Levels::set_current_level(std::string index)
{
	this->curr_level = index; 
	//std::cout << this->curr_level << std::endl; 
}

void Levels::render(sf::RenderTarget& target, const sf::View& view, const sf::Vector2i& gridposition, const bool render_collision, sf::Shader* shader, const sf::Vector2f PlayerPosition)
{
	if (shader)
		this->map.left.at(curr_level)->render(target, view, gridposition, render_collision, shader, PlayerPosition);
		//this->levels[curr_level]->render(target, view, gridposition, render_collision, shader, PlayerPosition);
	else
		this->map.left.at(curr_level)->render(target, view, gridposition, render_collision);

}

void Levels::DefferedRender(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f PlayerPosition)
{
	if (shader)
		this->map.left.at(curr_level)->DefferedRender(target, shader, PlayerPosition);
	else
		this->map.left.at(curr_level)->DefferedRender(target);
}

void Levels::update(const float& dt, Entity* entity, EnemySystem& enemysystem)
{ 

	this->map.left.at(curr_level)->update(entity, dt);
	this->map.left.at(curr_level)->updateWorldBoundsCollision(entity, dt);
	this->map.left.at(curr_level)->updateTileCollision(entity, dt);
	this->map.left.at(curr_level)->updateTiles(entity, dt, enemysystem);

}

bool Levels::saveLevel(std::string index, std::string filename)
{
	std::cout << filename << std::endl; 
	if (this->map.left.at(index)->savetofile(filename, true))
		return true;
	else
		return false; 
}

bool Levels::loadLevel(std::string index, std::string filename)
{ 
	return this->map.left.at(index)->loadfromfile(filename, true);
	
}

bool  Levels::saveLevelsBatch(std::string filename)
{
	std::ofstream out;

	// this->randomGeneration();
	out.open(filename, std::ios::out | std::ios::hex | std::ios::app);

	if (out.is_open())
	{

	
		//out << std::hex << map.left << "\n";
		//out << std::hex << this-



		for (auto& map : this->map) 
		{
			//map.left.
			//map.left.at(map.left) 
			//map
			//out << map.right->streamAsdata(filename).str(); 

		}
		for(int x = 0; x < this->map.left.size(); x++)
		{
			//this->map.left.at(this->map.right.at(this->get_name(x)))->savetofile(filename); ///// 

			 
			//std::cout << map.left.at(this->map.left.aa)->getLevelIndex() << " this is the title of the level being saved currently..." << std::endl;

			//this->map.left.at(x)->savetofile(filename);
			//{
			//	std::cout << "POO POO!!!" << std::endl; 
			//}
		
		}



	
		return true;
	}


	out.close(); 
	return false;
}

TileMap* Levels::getCurrent()
{
	return this->map.left.at(curr_level);
}

void Levels::addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool& collision, const short& type)
{
	this->map.left.at(curr_level)->addTile(x, y, z, texture_rect, collision, type); 
}

void Levels::addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const int enemytype, const int enemyamount, const int timeToSpawn, const int MaxDistance)
{
	this->map.left.at(curr_level)->addTile(x, y, z, texture_rect, enemytype, enemyamount, timeToSpawn, MaxDistance);

}

void Levels::addTile(const int x, const int y, const int z, float obX, float obY, const short type)
{
	this->map.left.at(curr_level)->addTile(x, y, z, obX, obY, type);
}

void Levels::RemoveTile(const int x, const int y, const int z, const int type)
{
	this->map.left.at(curr_level)->RemoveTile(x, y, z, type);
}

const int Levels::size_total() 
{
	return this->map.size(); 


}

std::string Levels::get_name(int index)
{
	if (this->names.empty())
		return "empty"; 
	else
	return names.at(index);
}
std::string Levels::get_size(std::string name)
{

	return std::to_string(this->map.left.at(name)->getMaxSizeGrid().x) + " " + std::to_string(this->map.left.at(name)->getMaxSizeGrid().y); 

}

std::string Levels::get_type(std::string name)
{
	return this->map.left.at(name)->getLevelType(); 
}
