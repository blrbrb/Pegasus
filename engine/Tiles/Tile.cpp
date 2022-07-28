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
    this->is_object = false;
    this->type = 0;
    
    
}

                                                                                        
Tile::Tile(short type, int x, int y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled)
{
    //this->rect.setSize(sf::Vector2f(gridsize_f, gridsize_f));
    
    this->rect.setTexture(texture);
    this->is_object = false; 
    //this->rect.setScale(2, 2);
    this->rect.setPosition(static_cast<float>(x) * gridsize_f.x, static_cast<float>(y) * gridsize_f.y);

   
    this->rect.setTextureRect(texturerect);
    this->collison_enabled = collision_enabled;
    short fart;
    fart = type;
    this->type = fart; 
   // this->object_type = object; 

    //this->hasobject = has_object;
    //this->type = type;
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



