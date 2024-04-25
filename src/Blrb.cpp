//
//  Blrb.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 3/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#
#include "include/Blrb.hpp"


void Blrb::initVariables()
{
    this->addAttributeComponent(1);
    this->addPhysicsComponent(150.f, 2000.f, 500.f);
    this->addHitboxComponent(this->sprite, 0, 0, 17.f, 17.f);
    
    
}

void Blrb::initanimations()
{
     this->animationcomponet->add_animation("IDLE", 25.f, 0, 0, 6, 0, 17, 17);
     this->animationcomponet->add_animation("LEFT", 25.f, 0, 0, 6, 0, 17, 17);
     this->animationcomponet->add_animation("RIGHT", 25.f, 0, 0, 6, 0, 17, 17);
     this->animationcomponet->add_animation("UP", 25.f, 0, 3, 6, 0, 17, 17);
     this->animationcomponet->add_animation("DOWN", 25.f, 0, 4, 6, 0, 17, 17);
     this->animationcomponet->add_animation("ATTACKED", 25.f, 0, 2, 6, 0, 17, 17);
    

}


Blrb::Blrb(float x, float y, sf::Texture &texturesheet, EnemySpawner& enemyspawner) : Enemy(enemyspawner)
{
    this->initVariables();
    this->addAnimationComponent(texturesheet);
    this->initanimations();
    this->addSkillComponent();
    //this->sprite.setScale(2.f, 2.f);
    this->sprite.setPosition(x,y);

}



Blrb::~Blrb()
{
    
}

void Blrb::updateAnimation(const float &dt)
{
   
          if (this->physicsComponents->getStatus(IDLE))
          {
              
              this->animationcomponet->play("IDLE", dt, false);
              
          }

            if (this->physicsComponents->getStatus(MOVING_LEFT))
            {
                 
               this->animationcomponet->play("LEFT", dt, false);
                 
            }
    
   
    if (this->physicsComponents->getStatus(MOVING_UP))
    {
        
        this->animationcomponet->play("UP", dt, false);
        
    }
    
    if (this->physicsComponents->getStatus(MOVING_DOWN))
    {
        
        this->animationcomponet->play("DOWN", dt, false);
        
    }
    
    if (this->physicsComponents->getStatus(MOVING_RIGHT))
    {
        
        this->animationcomponet->play("RIGHT", dt, false);
        
    }
        
}




void Blrb::update(const float &dt, sf::Vector2f &MousePosView)
{
       this->physicsComponents->update(dt);
       this->attributes->update();
       this->attributes->UpdateStats(false);
       this->updateAnimation(dt);
       this->hitbox->update();
}





void Blrb::render(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f &light, const bool render_hitbox)
{
    if (shader)
      {
          //shader->setUniform("hasTexture", true);
          shader->setUniform("lightPos", light);
         
          target.draw(this->sprite, shader);
      }
    
    else if (!shader)
    {
        
        target.draw(this->sprite);
    }
      
      if(render_hitbox) {
          this->hitbox->render(target); }
}


StatusComponet* Blrb::getStatusComponent()
{
    
    return this->attributes;
}
