//
//  NormalTile.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef NormalTile_hpp
#define NormalTile_hpp
#include "Tile.hpp"

class Tile; 

class NormalTile : public Tile
{
   
public:
    NormalTile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled = false);
    NormalTile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture,bool collision_enabled = false);
    virtual ~NormalTile();
    
    //Accessors 
    const sf::FloatRect getGlobalBounds() const;
    const std::string asString() const;

   
    
  

    void savetoFile(std::ofstream& in);
    
    //Functions
    void update(const float& dt);
    void render(sf::RenderTarget & target, sf::Shader* shader = NULL, sf::Vector2f LightPosition = sf::Vector2f());
    
    //Modifiers 
    void add_object(short type, sf::Vector2f& object_position);
protected:
    
   
    
    
};

#endif /* NormalTile_hpp */
