//
//  NormalTile.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "stdafx.h"
#include "NormalTile.hpp"


NormalTile::NormalTile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled) : Tile(type, x, y, gridsize_f,texture, texturerect, collision_enabled)
{

} 
NormalTile::NormalTile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture,bool collision_enabled) : Tile(type, x, y, gridsize_f, texture,collision_enabled)
{

}


NormalTile::~NormalTile()
{
    
}


const sf::FloatRect NormalTile::getGlobalBounds() const
{
    return this->rect.getGlobalBounds();
}

const std::string NormalTile::asString() const
{
    std::stringstream out;
    //std::cout << "pooping" << std::endl; 
    out << std::hex << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->collison_enabled;
       
       
       return out.str();
}

const TileData NormalTile::asData()
{
   // this->tiledata->collision = this->collison_enabled;
    this->tiledata.texturerect = this->rect.getTextureRect();
    this->tiledata.type = this->type;
  
    return this->tiledata;

} 


void NormalTile::savetoFile(std::ofstream& out) 
{
    //DEPRECIATED
   
   //will this work? 
   
  //bin is not going to work bc different machines will have different endianess 

  //re-write the toString function to export a hexidecimal value instead. 
  //it will be easier to read and write on different machines

    out.write(reinterpret_cast<const char*>(&this->type), sizeof(this->type));
    out.write(reinterpret_cast<const char*>(&this->rect.getTextureRect().left), sizeof(this->rect.getTextureRect().left));
    out.write(reinterpret_cast<const char*>(&this->rect.getTextureRect().top), sizeof(this->rect.getTextureRect().top));
    out.write(reinterpret_cast<const char*>(&this->collison_enabled), sizeof(this->collison_enabled));


}

void NormalTile::update(const float& dt)
{
    
}

void NormalTile::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f LightPosition)
{
    const sf::Color testcolor = sf::Color(250, 250, 250, 50); 
    if (shader)
    { 
        
        shader->setUniform("lightPos", LightPosition); 
        shader->setUniform("ambientData", sf::Glsl::Vec4(testcolor));
    
        target.draw(this->rect, shader);
    }

    else
    {
        target.draw(this->rect);

    }
}


void NormalTile::add_object(short type, sf::Vector2f& object_position)
{ 
  
}
