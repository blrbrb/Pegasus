//
//  TileMap.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include "Entity.hpp"
#include "Blerb.hpp"
#include "Blrb.hpp" 
#include "EnemySystem.hpp"
#include "Tile.hpp"
#include "NormalTile.hpp"
#include "ObjectTile.hpp"
#include "easylogging++.h"



//TO DO
//create an object that dynamically and randomly creates a new tilemap using some kind of noise, then save it as a slmp, load it.


class EnemySpawner; 
class Tile;
class NormalTile; 

class Entity;


 enum Level_Types { OVERWORLD = 0, DUNGEON };



class TileMap
{
private:
    
    //unsigned grid_sizeU;
    //float grid_sizeF;
    // 
    // 
    // 
    //int gridsizeI; 
 
  //  tile_grid
  
   // tile_gridS tile_grid[]; 
    int layers; 
    short level_type;
    sf::Vector2i gridsizeI; 
    sf::Vector2f grid_sizeF; 
    sf::Vector2u grid_sizeU;
    size_t texturefilesize; 
   
    

    std::string texture_file;
    sf::Vector2i MaxSizeWorldGrid;
    sf::Vector2f MaxSizeWorld_F;
    
    //Defered Render stack thingy
    std::stack<Tile*> renderdefered;
    

    
    
    sf::RectangleShape physicsrect; 
   
    //TileMap vector
    std::vector< std::vector< std::vector< std::vector<Tile*> > > > Map;

    int level_index; 
  
    
    sf::Font font; 
    sf::Texture tileTextureSheet;
    sf::Texture tilegenerationSheet; 
    std::map<std::string, sf::Texture> object_textures;
    std::map<std::string, sf::Vector2i> geometry;


    //boost test 
    boost::property_tree::ptree pt; 



    //Private Functions
    void clear();
    void initobjecthandler();
    void initgeometry(); 
    void init_object_textures();
    void initvariables();
    void initloggingthread(); 

    
    //tile culling
    int FromX;
    int ToX;
    int ToY;
    int FromY;
    int layer;
    
    //tile shader culling
    
public:
    


    /// <summary>
    /// Default Tilemap constructor
    /// </summary>
    /// <param name="gridSize"></param>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <param name="texture_file"></param>
    TileMap(sf::Vector2f gridSize, int width, int height, std::string texture_file); 

    /// <summary>
    /// Load tilemapdata from file
    /// </summary>
    /// <param name="map_file"></param>
    TileMap(const std::string map_file);     
    /// <summary>
    /// non_
    /// </summary>
    TileMap(); 
    virtual ~TileMap();
    
    
    //Variables
    bool  lock_layer;
    bool isEntityColliding;  

   
    
    //Acessors 

    /// <summary>
    /// Get a pointer to the tilemap texture
    /// </summary>
    /// <returns>sf::Texture*</returns>
    const sf::Texture* getTileSheet() const;

 
    /// <summary>
    ///  Return wether or not a particular tile in the four dimensional vector is null
    /// </summary>
    /// <param name="x">the X-postion(width in tiles)</param>
    /// <param name="y">the Y-postion(height in tiles)</param>
    /// <param name="z">the Z-position</param>
    /// <returns>const bool</returns>
    const bool TileEmpty(const int x, const int y, const int z) const;
    /// <summary>
    /// Get the type of a particular tile in the four dimensional vector
    /// </summary>
    /// <param name="x">the X-Position</param>
    /// <param name="y">the Y-Position</param>
    /// <param name="z">the Z-Position</param>
    /// <param name="type">unsigned type of tile</param>
    /// <returns>const bool</returns>
    const bool checktype(const int x, const int y, const int z, const int type) const;
 
    /// <summary>
    ///  get how many tiles are placed on the Z-axis (depth) of the tilemap vector in a certian spot.
    /// </summary>
    /// <param name="x">the X-Position</param>
    /// <param name="y">the Y-Position</param>
    /// <param name="layer">the layer</param>
    /// <returns>const int how many layers</returns>
    const int getLayerSize(const int x, const int y, const int layer) const;
   
    /// <summary>
    /// Helper function. Get the Maximum size of the tilemap in tiles
    /// </summary>
    /// <returns>&sf::Vector2i the Maximum allowed size of the tilemap in tiles</returns>
    const sf::Vector2i& getMaxSizeGrid() const;
  
    /// <summary>
    /// Helper function. Get the Maximum size of the tilemap in float
    /// </summary>
    /// <returns>sf::Vector2f the maximum size of the tilemap in float</returns>
    const sf::Vector2f getMaxSize() const; 

    
   const sf::Vector2f get_objectTile();  


   const sf::Texture* getGenerationSheet() const; 

   const std::string getLevelType() const;
   
   int getLevelIndex();
    
   
    
   
    
    //render functions
    void render(sf::RenderTarget& target,const sf::View& view, const sf::Vector2i& gridposition, const bool render_collision = false, sf::Shader* shader = NULL,const sf::Vector2f PlayerPosition = sf::Vector2f());
    void DefferedRender(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f PlayerPosition = sf::Vector2f());
   
   
    //Modifiers
    void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool& collision, const short& type);
    void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const int enemytype, const int enemyamount, const int timeToSpawn, const int MaxDistance);
    void addTile(const int x, const int y, const int z, float obX, float obY, const short type); 
    void addObject(const short type, const int x, const int y); 
    void setLevelIndex(int index); 
    void setType(short level_type); 

    void RemoveTile(const int x, const int y, const int z, const int type);
    bool savetofile(const std::string filename, bool json=false);   
   
    bool loadfromfile(const std::string filename, bool json=false);
    void addGenerationTexture(const std::string texture_filename);
    
    //update functions
    void update(Entity* entity, const float& dt);
    void updateWorldBoundsCollision(Entity* entity, const float& dt);
    void updateTiles(Entity* entity, const float& dt, EnemySystem& enemysystem);
    void updateTileCollision(Entity* entity, const float& dt); 

    //testing functions 
    void randomGeneration();
    Tile* genTile(int x, int y, int z); 
    
};



#endif /* TileMap_hpp */
