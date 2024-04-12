//
//  Player.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/28/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Player_hpp
#define Player_hpp

#include "Entity.hpp"
#include "Inventory.hpp"
#include "Item.hpp" 
#include "easylogging++.h"
#include <Candle/LightSource.hpp>
#include <Candle/RadialLight.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class Entity; 

class Player : public Entity
{
private:
    
    
    void initVariables();
    void initcomponets();
    void initanimations(); 
    void initsounds(); 
    void initinventory(); 
    void initlight();

    
    sf::Color default_color; 
    candle::RadialLight player_ambient; 
    candle::EdgeVector edges;
    Inventory* inventory;
    //spotlight* render_light; 
    
     
    std::vector<sf::SoundBuffer> sounds; 

   
 

public:

    /// <summary>
    /// Default Player constructor. Overrides Entity() inherits abstracts
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="texturesheet"></param>
    /// <param name="level"></param>
    Player(float x, float y, sf::Texture& texturesheet);
   
    virtual ~Player();
    
    /// <summary>
    /// Load Player data from file, Entity info is constructed from saved data
    /// </summary>
    /// <param name="save_file"></param>
    Player(const std::string save_file, sf::Texture& texturesheet); 

    //Accessors

    /// <summary>
    /// Fetch a pointer to the Player's Staus Component.
    /// </summary>
    /// <returns>StatusComponent*</returns>
    /// <remarks><seealso cref="StatusComponent"/></remarks>
    /// <remarks><seealso cref="Entity"/></remarks>
    StatusComponet* getStatusComponet();
    /// <summary>
    /// Fetch a pointer to the Player's Inventory 
    /// </summary>
    /// <returns>Inventory*</returns>
    Inventory* getInventory();


    const std::string  InfoString() const; 
                                                                               
    void saveToFile(const std::string filename);
    void loadFromFile(const std::string filename); 
   
    
     /// <summary>
     /// Update the player (Calls all other Player class update functions)
     /// </summary>
     /// <param name="dt"></param>
     /// <param name="MousePosView"></param>
     void update(const float& dt, sf::Vector2f& MousePosView);



     void updateLighting(const float& dt); 
    
     /// <summary>
     /// Update the Player's animation
     /// </summary>
     /// <param name="dt"></param>
     void updateAnimation(const float& dt);
   
    
     /// <summary>
     /// Render the Player's sprite to the active context
     /// </summary>
     /// <param name="target"></param>
     /// <param name="shader"></param>
     /// <param name="light"></param>
     /// <param name="render_hitbox"></param>
     void render(sf::RenderTarget& target,sf::Shader* shader = nullptr,const sf::Vector2f light = sf::Vector2f(), const bool render_hitbox = false);

    



};

#endif /* Player_hpp */
