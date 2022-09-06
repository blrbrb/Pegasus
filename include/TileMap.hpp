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


//TO DO 
//create an object that dynamically and randomly creates a new tilemap using some kind of noise, then save it as a slmp, load it.


class EnemySpawner; 
class Tile;
class NormalTile; 

class Entity;






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
    //if the union doesn't work 
   // std::vector< std::vector< std::vector< std::vector<std::pair<Tile*, Object*> > > > Map;
    //std::vector< std::vector< std::vector< std::vector<Tile*> > > > Map;
    
    
    sf::Font font; 
    sf::Texture tileTextureSheet;
    sf::Texture tilegenerationSheet; 
    std::map<std::string, sf::Texture> object_textures;
    std::map<std::string, sf::Vector2i> geometry;

    //Private Functions
    void clear();
    void initobjecthandler();
    void initgeometry(); 
    void init_object_textures();

    
    //tile culling
    int FromX;
    int ToX;
    int ToY;
    int FromY;
    int layer;
    
    //tile shader culling
    
public:
    
    TileMap(sf::Vector2f gridSize, int width, int height, std::string texture_file);
    TileMap(const std::string map_file);    
    TileMap(); 
    virtual ~TileMap();
    
    
    //Variables
    bool  lock_layer;
    bool isEntityColliding;  

   
    
    //Acessors 
    const sf::Texture* getTileSheet() const;

  
    /// TileEmpty
    /// @brief Return wether or not a particular tile in the four dimensional vector is null
    /// @param x the X-axis of the vector (width in tiles)
    /// @param y the Y-axis of the vector (height in tiles)
    /// @param z the Z-axis of the vector (depth)
    ///@returns const bool wether or not a certian tile is empty
    const bool TileEmpty(const int x, const int y, const int z) const;
    /// checktype
    /// @brief Get the type of a particular tile in the four dimensional vector
    /// @param x the X-axis of the vector (width in tiles)
    /// @param y the Y-axis of the vector (height in tiles)
    /// @param z the Z-axis of the vector (depth)
    /// @param type to check for
    ///@returns wether or not a certian tile is of the same type being checked for
    const bool checktype(const int x, const int y, const int z, const int type) const;
    /// getLayerSize
    /// @brief get how many tiles are placed on the Z-axis (depth) of the tilemap vector in a certian spot.
    /// @param x the X-axis of the vector (width in tiles)
    /// @param y the Y-axisof the vector (height in tiles)
    /// @param layer  of the Z-component
    ///@returns const int how many tiles are placed on the Z-axis in a particular place
    const int getLayerSize(const int x, const int y, const int layer) const;
    /// getMaxSizeGrid
    ///@brief Helper function to find the Maximum size of the map in tiles
    ///@returns the Maximum size of the map in tiles
    const sf::Vector2i& getMaxSizeGrid() const;
    /// getMaxSize
    ///@brief Get the Maximum size (in pixels) of the map
    ///@returns the maximum size of the map
    const sf::Vector2f getMaxSize() const; 
    
   const sf::Vector2f get_objectTile(); 


   const sf::Texture* getGenerationSheet() const;
   
    
    
   
    
   
    
    //render functions
    void render(sf::RenderTarget& target,const sf::View& view, const sf::Vector2i& gridposition, const bool render_collision = false, sf::Shader* shader = NULL,const sf::Vector2f PlayerPosition = sf::Vector2f());
    void DefferedRender(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f PlayerPosition = sf::Vector2f());
   
   
    //Modifiers
    void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool& collision, const short& type);
    void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const int enemytype, const int enemyamount, const int timeToSpawn, const int MaxDistance);
    void addTile(const int x, const int y, const int z, float obX, float obY, const short type); 
    void addObject(const short type, const int x, const int y); 


    void RemoveTile(const int x, const int y, const int z, const int type);
    bool savetofile(const std::string filename);
    bool loadfromfile(const std::string filename);
    void addGenerationTexture(const std::string texture_filename);
    
    //update functions
    void update(Entity* entity, const float& dt);
    void updateWorldBoundsCollision(Entity* entity, const float& dt);
    void updateTiles(Entity* entity, const float& dt, EnemySystem& enemysystem);
    void updateTileCollision(Entity* entity, const float& dt); 

    //testing functions 
    void randomGeneration();
    Tile* genTile(int x, int y, int z);

   

   // const bool good_geometry(sf::Vector2i texture_coords, std::string geometry_key) const;
   // const bool good_geometry(sf::Vector2i texture_coords) const;

    
    
    
    
};// this->Map[x][y][z].push_back(tile_gridS(new ObjectTile(x, y, ), nullptr);



#endif /* TileMap_hpp */
