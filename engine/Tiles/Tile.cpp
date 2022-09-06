//
//  Tile.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 
#include "stdafx.h"
#include "Tile.hpp"




Tile::Tile()
{
    this->collison_enabled = false;
    this->type = 0;
    
    
}

                                                                                        
Tile::Tile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled)
{
   //Tile constructor that needs to be called if there is a tile object/object tile on the map.
    this->type = type;
    this->rect.setTexture(texture);
   
    this->rect.setTextureRect(texturerect);
     // this->rect.setPosition(obX, obY);
     this->rect.setPosition(x * gridsize_f.x, y * gridsize_f.y);
    
         
   
    this->collison_enabled = collision_enabled;
    
    
    
  
   // this->object_type = object; 

    //this->hasobject = has_object;
    //this->type = type;
}

Tile::Tile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture, bool collision_enabled)
{
    this->rect.setTexture(texture);
   

    //  
    sf::Vector2f gridPosition = sf::Vector2f(gridsize_f.x * x, gridsize_f.y * y); 
    this->rect.setPosition(x, y);


   // this->rect.setTextureRect(texturerect);
    this->collison_enabled = collision_enabled;
    short fart;
    fart = type;
    this->type = fart; 
    //this->rect.get
}




Tile::~Tile()
{
    

}

//Functions

const sf::Vector2f &Tile::getposition() const
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

const sf::IntRect Tile::gettexturerect() const
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




