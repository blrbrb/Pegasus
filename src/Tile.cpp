//
//  Tile.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#
#include "include/Tile.hpp"

Tile::Tile(sf::Texture* texture)
    : rect(*texture)
{
    this->collison_enabled = false;
    this->type = 0;
    this->object_type = 0;
}


Tile::Tile(short type, float x, float y, sf::Vector2f gridsizeF, sf::Texture& texture, const sf::IntRect& texturerect, bool collisionEnabled)
    : rect(texture)
{

    this->type = type;



    this->calcGid(texturerect.position,texturerect.size,texture.getSize());

    this->object_type = object_type;

    this->rect.setTexture(texture);

    this->rect.setTextureRect(texturerect);
    // this->rect.setPosition(obX, obY);
    this->rect.setPosition(sf::Vector2f(x * gridsizeF.x, y * gridsizeF.y));

    this->collison_enabled = collisionEnabled;
}

Tile::Tile(short type,int gid, sf::Texture& texture, bool collisionEnabled)
    : rect(texture),type(type),gid(gid),collison_enabled(collisionEnabled)
{

}

Tile::~Tile()
    = default;

// Functions

void Tile::calcGid(sf::Vector2i tileCoords, sf::Vector2i tileSize, sf::Vector2u textureSize)
{

    int columns = static_cast<int>(this->rect.getTexture().getSize().x) / static_cast<int>(tileSize.x);
    //int rows = static_cast<int>(this->rect.getTexture().getSize().y) / static_cast<int>(tileSize.y);
    int cellX = tileCoords.x / tileSize.x;
    int cellY = tileCoords.y / tileSize.y;
    int gridIndex = (cellY * columns) + cellX;

    this->gid = gridIndex; //tileCoords.x + (tileCoords.y * columns) + 1;
    //std::string debug = std::format("Grid Position -> X ({}/{})={} Y ({}/{})={}", textureSize.x,tileCoords.x,((textureSize.x - tileCoords.x) / tileSize.x),textureSize.y, tileCoords.y, (tileCoords.y / tileSize.y));
    //std::cout << "tile gid -> " << this->gid << std::endl;

}

const unsigned& Tile::getGid() const
{

    return this->gid;

}

const sf::Vector2f& Tile::getPosition() const
{
    return this->rect.getPosition();
}

const bool& Tile::getCollision() const
{
    return this->collison_enabled;
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
    std::optional<sf::FloatRect> result = this->rect.getGlobalBounds().findIntersection(bounds);
    return result.has_value();
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
    return sf::Vector2f(this->rect.getGlobalBounds().size.x / 2, this->rect.getGlobalBounds().size.y / 2);
}

const sf::IntRect Tile::getTextureRect() const
{
    return this->rect.getTextureRect();
}



const short& Tile::getObjectType() const
{
    return this->object_type;
}
