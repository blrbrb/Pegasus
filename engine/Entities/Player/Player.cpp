//
//  Player.cpp
//  Project Pegasus
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
Player::Player(float x, float y, sf::Texture& texturesheet, int level) : level(level)
{
    
   
    this->initcomponets();
    this->initinventory(); 
    this->setposition(x, y);
    this->create_animation_componet(texturesheet);
    this->initanimations(); 
    this->initsounds(); 
    //this->sprite.setScale(2, 2);
    this->default_color = this->sprite.getColor(); 
}

Player::~Player()
{
    
   // delete this->inventory; 
  
    
}


//initalizer functions

void Player::initcomponets()
{
    this->createmovementcomponet(100.f, 20000.f, 200.f);
    this->create_hitbox_componet(this->sprite, 0, 0, 52.f, 42.f);
    
    this->create_skill_component(); 
    this->create_sound_component();  
    if (this->level)
    {
        this->create_attribute_componet(level);

    }//Note: is lower because cropped for more accurate collision
    else
        this->create_attribute_componet(1);
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
 
    this->animationcomponet->add_animation("IDLE_BLINKING", 4.f, 0, 2, 15, 2, 62, 74); //first row, second* sprite across *iterator starts from unsigned 0
    this->animationcomponet->add_animation("WALK_RIGHT", 5.f, 1, 1, 15, 1, 62, 74);
    this->animationcomponet->add_animation("WALK_LEFT", 5.f, 0, 0, 15, 0, 62, 74);
    this->animationcomponet->add_animation("WALK_DOWN", 5.f, 0, 0, 15, 0, 62, 74);
    this->animationcomponet->add_animation("WALK_UP", 5.f, 0, 3, 2, 3, 62, 74);  

                  
    //lol
    //this->animtioncomponet->add_animation("PISSING_PANTS", 10.f, 0, 0, 5, 0, 16, 16);
    
}

void Player::initsounds()
{ 
    if (!this->walking_sound.loadFromFile("Resources/Assets/Sounds/Player/walk_grass.wav")) 
    {
        //you are a moron, and you should be very ashamed of yourself you waste of seminal fluid
        throw std::runtime_error("unable to load player sounds walk_grass.wav"); 
    }  

    this->soundcomponent->add_sound("WALK", 25.f, this->walking_sound); 
}
    
//FUCK THIS FUCK THIS ASS THIS ASS IS RETARDED. FUCK FUCK FUCK I HATE THIS. KILL. KILL. KILL. IDIOT FART. IDIOT FART DICKS 
void Player::updateAnimation(const float& dt)
{
    /*!
    @brief Change the player's animations based on which direction they're walking in

    @param const float& dt

    @return void
     */

    this->movementcomponets->update(dt);
    //if there ever was a valid reason to shoot someone, it's this 
    //stupid useless hanging pointer error right here. 
    //FIX: (return an adress, not a pointer you fucking simpleton)
    if (this->movementcomponets->getStauts(IDLE))
    {
        this->animationcomponet->play("IDLE_BLINKING", dt);
        //this->soundcomponent->play("WALK", dt);

        // this->soundcomponent->stop("WALK");
    }

    else if (this->movementcomponets->getStauts(MOVING_RIGHT))
    {
        this->animationcomponet->play("WALK_RIGHT", dt);
        //this->soundcomponent->play("WALK", dt, 1.f); 
    }

    else if (this->movementcomponets->getStauts(MOVING_LEFT))
    {
        this->animationcomponet->play("WALK_LEFT", dt);

        //this->soundcomponent->play("WALK", dt, 1.f); 
    }

 //change the sprite's color to red if the player is loosing HP 
      



      
}




void Player::update(const float& dt, sf::Vector2f& MousePosView)
{
    this->attributes->update();

    this->attributes->updateMagic(dt); 

    this->movementcomponets->update(dt);
    
    this->updateAnimation(dt);
    
    this->hitbox->update();
    
   
    
   
}





void Player::render(sf::RenderTarget &target, sf::Shader* shader,const sf::Vector2f light, const bool render_hitbox)
{
   
    const sf::Color testcolor2 = sf::Color(250, 250, 250, 250);
    
    if (shader)
    { 
       
        
       

        shader->setUniform("lightPos", light);
        shader->setUniform("lightData", sf::Glsl::Vec4(testcolor2));
        shader->setUniform("lightSize", sf::Vector2f(1.f, 10.f));
        target.draw(this->sprite, shader);
        
       
    }

    else if(render_hitbox) {
        this->hitbox->render(target); }


    if (this->using_vertices) 
    {
       // target.draw(this->verticies); 
    }
    
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


