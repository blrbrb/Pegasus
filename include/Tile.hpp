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


enum TileTypes {DEFAULT=0, UNPASSABLE, OBJECT, SPAWNER, LIGHT, NORMAL};
static const char * EnumStrings[] = { "Default", "Unpassable", "Object", "Spawner", "Light", "Stop", "YOU FOOL", "NO" };


typedef struct TileData
{
     float  obX, obY, maxDistance;
     short type, object_type;
    sf::IntRect texturerect;
     bool collision;
     sf::Int32* enemy_timer; 
    int Enemy_type, Enemy_amount;
    sf::Vector2f position;


};




class Tile
{
private:
    
   
protected:
    
    sf::Sprite rect;
    short type;
    





public:
    
    Tile();
    Tile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled = false);
    Tile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture,bool collision_enabled = false);
    virtual ~Tile();
    
    //Accessors
    virtual const std::string asString() const =0;
    virtual const TileData asData() = 0;
    virtual const short& gettype() const;
    virtual const sf::Vector2f& getposition() const;
    virtual const bool& getCollision() const;
    virtual const bool intersects(const sf::FloatRect bounds) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::Vector2f getCenter() const;
    virtual void savetoFile(std::ofstream& out) = 0; 
    
    //Functions
    virtual void update(const float& dt) =0;
    virtual void render(sf::RenderTarget & target, sf::Shader* shader = NULL, sf::Vector2f LightPosition = sf::Vector2f())=0;
   
    bool collison_enabled;

    //Modifiers 


    //Data 
    
};


#endif /* Tile_hpp */
