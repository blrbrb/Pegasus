//
//  Tile.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#ifndef Tile_hpp
#define Tile_hpp


#include "GUI.hpp"


//enum TileTypes {DEFAULT=0, UNPASSABLE, OBJECT, SPAWNER, LIGHT, NORMAL};
static const char * EnumStrings[] = { "Default", "Unpassable", "Object", "Spawner", "Light", "Stop", "YOU FOOL", "NO" };
/**
 * @enum Types of in game tile. 
*/
 enum TileTypes : int {
    DEFAULT=0,
    UNPASSABLE,
    OBJECT,
    SPAWNER,
    LIGHT,
    NORMAL
};

/**
 * @brief  Base abstract tile object. Contains pure virtual method definitions for rendering, collisions, and basic on screen transformations 
 * @class Tile() 
 * @
 */
class Tile
{
private:
    
   
protected:
    
    sf::Sprite rect;
    short type;
    short object_type;
    
   
  
public:
   
    Tile();
    Tile(short type, float x, float y, sf::Vector2f gridsizeF, sf::Texture& texture, const sf::IntRect& textureRect, bool collisionEnabled = false );
    Tile(short type, float x, float y, sf::Vector2f gridsizeF, sf::Texture& texture, bool collision_enabled = false);
    virtual ~Tile();
    
    //Accessors
    virtual const std::string asString() const =0;
    virtual const short& gettype() const;
    virtual const sf::Vector2f& getPosition() const;
    virtual const bool& getCollision() const;
    virtual const bool intersects(const sf::FloatRect bounds) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::Vector2f getCenter() const;
    virtual const sf::IntRect getTextureRect() const;
    virtual const sf::Vector2i getTextureCoords() const;
    virtual const short& getObjectType() const;
    virtual void savetoFile(std::ofstream& out) = 0;

    
    //Functions
    virtual void update(const float& dt) =0;
    virtual void render(sf::RenderTarget & target, sf::Shader* shader = nullptr, sf::Vector2f LightPosition = sf::Vector2f())=0;
   
    bool collison_enabled;
};


#endif /* Tile_hpp */
