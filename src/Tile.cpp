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

Tile::Tile(short type,int gid, sf::Vector2f gridsizeF, sf::Texture& texture, bool collision_enabled)
    : rect(texture),type(type),gid(gid)
{

    //sf::Vector2i position(0,0);

    //std::cout << "setting tile GID -> " << gid << std::endl;
    int columns = static_cast<int>(this->rect.getTexture().getSize().x) / static_cast<int>(gridsizeF.x);
    int rows = static_cast<int>(this->rect.getTexture().getSize().y) / static_cast<int>(gridsizeF.y);
   // int column = gid % columns;
   // int row = gid / columns;
    //int posX = column * static_cast<int>(gridsizeF.x);
   // int posY = row * static_cast<int>(gridsizeF.y);

    //this->calcGid(gridsizeF);
    this->collison_enabled = collision_enabled;


    //if (object_type) {
     //   this->object_type = object_type;
    //}
     //calculate the Tile's GID within the texture (tmx stuff)
     int tilesX = 10;//static_cast<int>(texture.getSize().x) / static_cast<int>(gridsizeF.x);
     //std::cout << "number of horizontal tiles " << tilesX << std::endl;
    int col =  static_cast<int>(rect.getGlobalBounds().size.x) / static_cast<int>(gridsizeF.x);
   //  std::cout << "number of columns " << col << std::endl;
    int row = static_cast<int>(rect.getGlobalBounds().size.y)  / static_cast<int>(gridsizeF.y);
   // std::cout << "number of rows " << row << std::endl;
   // this->gid = (row * tilesX) + col;
    //this->rect.setTextureRect(this->calcRect(gid,sf::Vector2i(static_cast<int>(gridsizeF.x),static_cast<int>(gridsizeF.y))));

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

const sf::Vector2i Tile::getTextureCoords() const
{
    sf::Vector2i test;
    test.x = this->rect.getTextureRect().position.x;
    test.y = this->rect.getTextureRect().position.y;

    return test;
}

const short& Tile::getObjectType() const
{
    return this->object_type;
}
