#include "stdafx.h"
#include "ObjectTile.hpp"

ObjectTile::ObjectTile(short type, int x, int y,float obX, float obY,  sf::Vector2f gridsize_f, short object_type, bool collision_enabled)
{  
    
   
  
}

ObjectTile::~ObjectTile()
{



}

const std::string ObjectTile::asString() const
{
    std::stringstream out; 

    out << this->type << " " << this->collison_enabled << " " << this->type; 
    return std::string();
}

void ObjectTile::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f LightPosition)
{
}

void ObjectTile::update()
{
}
