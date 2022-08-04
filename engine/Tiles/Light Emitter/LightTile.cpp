//
//  LightTile.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 3/14/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "stdafx.h"
#include "LightTile.hpp"


LightTile::LightTile(short type, int x, int y, sf::Vector2f gridsize_f, sf::Texture &texture, const sf::IntRect &texturerect) : Tile(TileTypes::LIGHT, x, y, gridsize_f, texture, texturerect, false)
{
    
    
}

LightTile::~LightTile()
{
    
}

const std::string LightTile::asString() const
{
    std::stringstream out;
       
    out << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top;
       
       
       return out.str();
}




void LightTile::update(const float& dt)
{
    
}

void LightTile::render(sf::RenderTarget& target, sf::Shader* shader, const float& dt, sf::Vector2f LightPosition)
{
    if (shader)
    {
        shader->setUniform("LightSource", true);
        shader->setUniform("hasTexture", true);
        shader->setUniform("light2", LightPosition);
        shader->setUniform("time", dt); 
        target.draw(this->rect, shader);

    }

    else
    {

        target.draw(this->rect);


    }

}



void LightTile::add_object(short type, sf::Vector2f& object_position)
{
}

