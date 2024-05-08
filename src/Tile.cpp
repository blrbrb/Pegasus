//
//  Tile.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 
#
#include "include/Tile.hpp"






Tile::Tile()
{
    this->collison_enabled = false;
    this->type = 0; 
    this->object_type = 0; 
   
}

                                                                                        
/**
 * @brief initializes a tile object with a specified type, position, texture, collision
 * 
 * @param type The type of tile to construct
 * @param x the x-coordinate position of the tile on the map grid. 
 * @details It is multiplied by the `gridsizeF.x` to determine the actual pixel position
 * of the tile on the screen.
 * @param y the y-coordinate position of the tile on the map grid. 
 * @details It is multiplied by the `gridsizeF.y` to determine the actual pixel position
 * of the tile on the screen.
 * @param gridsizeF the size of each grid cell in the map.
 * @details used to calculate the position of the tile  based on its grid coordinates `(x, y)`.
 * @param texture set the texture of the tile's sprite
 * @details (`this->rect.setTexture(texture)`). The texture contains the image data that will be displayed on
 * the tile in the game
 * @param texturerect the rectangular area of the tile sheet that should be displayed on the tile.
 * @param collisionEnabled flag that indicates whether collision is enabled for this particular tile. 
 * @details If `collisionEnabled` is set to `true`, it means that the tile will participate in collision detection and response within the game world. If set to `false
 */

Tile::Tile(short type, float x, float y, sf::Vector2f gridsizeF, sf::Texture& texture, const sf::IntRect& texturerect, bool collisionEnabled)
{
   
    this->type = type;
   
    this->object_type = object_type; 
    
    this->rect.setTexture(texture);
   
    this->rect.setTextureRect(texturerect);
     // this->rect.setPosition(obX, obY);
     this->rect.setPosition(x * gridsizeF.x, y * gridsizeF.y);
    
         
   
    this->collison_enabled = collisionEnabled;
    
    
    
  
  
}

Tile::Tile(short type, float x, float y, sf::Vector2f gridsizeF, sf::Texture& texture, bool collision_enabled)
{
    this->rect.setTexture(texture);
   

    //  
    sf::Vector2f gridPosition = sf::Vector2f(gridsizeF.x * x, gridsizeF.y * y);
    this->rect.setPosition(x, y);


   // this->rect.setTextureRect(textureRect);
    this->collison_enabled = collision_enabled;
    short fart;
    fart = type;
    this->type = fart; 

    if (object_type)
    {
        this->object_type = object_type;
    }
    //this->rect.get
}




Tile::~Tile()
= default;

//Functions

const sf::Vector2f &Tile::getPosition() const
{
    return this->rect.getPosition(); 
}

const bool& Tile::getCollision() const
{
    return this->collison_enabled;
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
    return this->rect.getGlobalBounds().intersects(bounds);
}

const sf::FloatRect Tile::getGlobalBounds() const 
{ 
    return this->rect.getGlobalBounds();
}

const short& Tile::gettype() const
{
    return this->type;

}

const sf::Vector2f Tile::getCenter() const
{
    return sf::Vector2f(this->rect.getGlobalBounds().width / 2, this->rect.getGlobalBounds().height / 2);
}

const sf::IntRect Tile::getTextureRect() const
{
    return this->rect.getTextureRect(); 
}

const sf::Vector2i Tile::getTextureCoords() const
{
    sf::Vector2i test; 
    test.x = this->rect.getTextureRect().left; 
    test.y = this->rect.getTextureRect().top; 

    return test;
}

const short& Tile::getObjectType() const
{
    return this->object_type; 
}





