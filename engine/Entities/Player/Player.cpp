//
//  Player.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/28/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "stdafx.h"
#include "Player.hpp"

//Constructors, Destructors
/* 
WORKING ANIMATIONS FOR CHARACTERSHEET2
    this->animtioncomponet->add_animation("IDLE_LEFT", 10.f, 0, 0, 0, 0, 24, 24); //first row, second* sprite across *iterator starts from unsigned 0
    this->animtioncomponet->add_animation("WALK_RIGHT", 10.f, 0, 2, 2, 2, 24, 24);
    this->animtioncomponet->add_animation("WALK_LEFT", 10.f, 0, 1, 2, 1, 24, 24);
    this->animtioncomponet->add_animation("WALK_DOWN", 10.f, 0, 0, 2, 0, 24, 24);
    this->animtioncomponet->add_animation("WALK_UP", 10.f, 0, 3, 2, 3, 24, 24);


*/
Player::Player(float x, float y, sf::Texture& texturesheet)
{
    
    
    this->initcomponets();
    this->initinventory(); 
    this->setposition(x, y);
    this->create_animation_componet(texturesheet);
    this->initanimations();
    this->sprite.setScale(2, 2);

}

Player::~Player()
{
    
   // delete this->inventory; 
  
    
}


//initalizer functions

void Player::initcomponets()
{
    this->createmovementcomponet(100.f ,2000.f, 200.f);    
    this->create_hitbox_componet(this->sprite, 5, 5, 24.f, 24.f);    //Note: is lower because cropped for more accurate collision
    this->create_attribute_componet(1);
    this->create_skill_component();
  
    

}

void Player::initinventory()
{
   this->inventory = new Inventory(100);
}




void Player::initvariables()
{
    //this->attacking = false; 
}

void Player::initanimations()
{
    
    this->animtioncomponet->add_animation("IDLE_LEFT", 10.f, 0, 0, 0, 0, 62, 71); //first row, second* sprite across *iterator starts from unsigned 0
    this->animtioncomponet->add_animation("WALK_RIGHT", 10.f, 0, 2, 2, 2, 62, 71);
    this->animtioncomponet->add_animation("WALK_LEFT", 10.f, 0, 1, 2, 1, 62, 71);
    this->animtioncomponet->add_animation("WALK_DOWN", 10.f, 0, 0, 2, 0, 62, 71);
    this->animtioncomponet->add_animation("WALK_UP", 10.f, 0, 3, 2, 3, 62, 71);  
   
    
    //lol
    //this->animtioncomponet->add_animation("PISSING_PANTS", 10.f, 0, 0, 5, 0, 16, 16);
    
}
    

void Player::updateAnimation(const float& dt)
{
    /*!
    @brief Change the player's animations based on which direction they're walking in
        
    @param const float& dt
     
    @return void
     */
       
       this->movementcomponets->update(dt);
       
       if (this->movementcomponets->getStauts(IDLE))
       {
           
       this->animtioncomponet->play("IDLE_LEFT", dt);
           
       }

       else if(this->movementcomponets->getStauts(MOVING_RIGHT))
       {
           this->animtioncomponet->play("WALK_RIGHT", dt);
           
       }
       
       else if (this->movementcomponets->getStauts(MOVING_LEFT))
       {
           this->animtioncomponet->play("WALK_LEFT", dt);
           
       }
       
       else if (this->movementcomponets->getStauts(MOVING_DOWN))
       {
           
           this->animtioncomponet->play("WALK_DOWN", dt);
           
       }
       
       else if (this->movementcomponets->getStauts(MOVING_UP))
       {
           this->animtioncomponet->play("WALK_UP", dt);
       }

}




void Player::update(const float& dt, sf::Vector2f& MousePosView)
{
    this->attributes->update();
    
    this->movementcomponets->update(dt);
    
    this->updateAnimation(dt);
    
    this->hitbox->update();
    
   
    
   
}





void Player::render(sf::RenderTarget &target, sf::Shader* shader,const sf::Vector2f light, const bool render_hitbox)
{
    
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light);
        target.draw(this->sprite, shader);
        
       
    }

    else if(render_hitbox) {
        this->hitbox->render(target); }
    
}

StatusComponet *Player::getStatusComponet()
{
    return this->attributes;
}


Inventory* Player::getInventory()
{
    return this->inventory; 
}

const std::string Player::InfoString() const
{
    std::stringstream ss; 
    
    const StatusComponet* sc = this->attributes; 
   
    ss << "Level: " << sc->level << "\n"
        << "Exp: " << sc->exp << "\n"
        << "Exp next: " << sc->expNextlvl << "\n";
    
        return ss.str(); 

}


