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


class Entity; 

class Player : public Entity
{
private:
    
    //initalizer functions
    void initvariables();
    void initcomponets();
    void initanimations(); 
    void initinventory();
    
    
    
   
    
    Inventory* inventory;
    
    //Variables
 

public:

    Player(float x, float y, sf::Texture& texturesheet);
    virtual ~Player();
    
    //Accessors
    ///Retrieve a pointer to the Player's status component through Entity
    StatusComponet* getStatusComponet();
    ///Retrieve a pointer to the Player's Inventory
    Inventory* getInventory();
    const std::string  InfoString() const; 

   
    
    ///  Update the Player
    /// @param dt Delta-Time
    /// @param MousePosView sf::Vector2f, the mouse's position relative to the view
     void update(const float& dt, sf::Vector2f& MousePosView);
    
    /// Update the Player's animation component
    /// @param dt Delta-Time
     void updateAnimation(const float& dt);
    
    /// Render the entity to either an OpenGL object, or an sf::RenderTarget
    /// @param target the intended target to render to
     void render(sf::RenderTarget& target,sf::Shader* shader = nullptr,const sf::Vector2f light = sf::Vector2f(), const bool render_hitbox = false);

    
};

#endif /* Player_hpp */
