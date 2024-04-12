#ifndef Levels_hpp
#define Levels_hpp 


#include "TileMap.hpp"


class TileMap; 

//type definitions for the levels storage container 
typedef boost::bimaps::bimap<std::string, TileMap*> Map;
typedef boost::bimaps::bimap<std::string, TileMap*>::value_type level;
typedef boost::bimaps::bimap<std::string, TileMap*>::left_map::iterator name; 
typedef boost::bimaps::bimap<std::string, TileMap*>::right_map::iterator tilemap;



class Levels
{
public:

	Levels(sf::Vector2f gridsize);
	virtual ~Levels();

	void add_level(std::string name);
	void add_level(std::string name, int width, int height, std::string texture_file = 0);


	void remove_level(std::string index);

	void set_current_level(std::string index);
	//sf::RenderTarget& target,
    void render(sf::RenderTarget& target, const sf::View& view, const sf::Vector2i& gridposition, const bool render_collision = false, sf::Shader* shader = NULL, const sf::Vector2f PlayerPosition = sf::Vector2f());
	void DefferedRender(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f PlayerPosition = sf::Vector2f());

	 void update(const float& dt, Entity* entity, EnemySystem& enemysystem);
	 bool saveLevel(std::string index, std::string filename); 
	 bool loadLevel(std::string index, std::string filename); 
	 bool  saveLevelsBatch(std::string filename); 

	 TileMap* getCurrent(); 

	 void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool& collision, const short& type);
	 void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const int enemytype, const int enemyamount, const int timeToSpawn, const int MaxDistance);
	 void addTile(const int x, const int y, const int z, float obX, float obY, const short type);

	 void RemoveTile(const int x, const int y, const int z, const int type);

	 const int size_total();  

	 std::string get_name(int index); 
	 std::string get_size(std::string name);
	 std::string get_type(std::string name);
	 std::vector<std::string> names;
		
	
private:

	// std::map<std::string, TileMap*> levels; 
	//std::map<std::string, int> level_indexes;
	//boost::bimaps::bimap<TileMap* ,std::string > levels;
	
	//std::vector<TileMap*> levels; 
	Map map;
	std::string curr_level;
	sf::Vector2f gridSize;
	int width;
	int height;
	std::string texture_file;

	
};

#endif