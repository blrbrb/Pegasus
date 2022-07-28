//
//  LightTile.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/14/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef LightTile_hpp
#define LightTile_hpp
#include "Tile.hpp"
class Tile;

class LightTile : public Tile
{
    
public:
    
    LightTile(short type, int x, int y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect);
    virtual ~LightTile();
    
    //Acessors
    const std::string asString() const;
   
    
    //Functions
    void update();
    void render(sf::RenderTarget & target, sf::Shader* shader = NULL,sf::Vector2f LightPosition = sf::Vector2f());
    
    //Modifiers 
    void add_object(short type, sf::Vector2f& object_position);
private: 
    
    
    
};

#endif /* LightTile_hpp */
