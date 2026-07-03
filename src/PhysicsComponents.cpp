//
//  PhysicsComponents.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 1/29/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#
#include "include/PhysicsComponents.hpp"


PhysicsComponents::PhysicsComponents(sf::Sprite& sprite, float maxVelocity, float Acceleration, float Deceleration) : sprite(sprite), maxVelocity(maxVelocity), Acceleration(Acceleration), Deceleration(Deceleration), movement_time(0), movement_timeMax(7.f)
{
    this->Velocity.x = 0.f;
    this->Velocity.y = 0.f;
    

}

PhysicsComponents::~PhysicsComponents()
{
    
}



/**
   move the object by supplying an incriment for the X and Y Velocity, and then apply Delta Time.
                   
   @param The X-Velocity and Y-Velocity values to move the object with. Mult by the deltaTime Param, and then combined alongside Y param into a float vector.
   @param
   @param delta Time
   @returns void

*/
void PhysicsComponents::move(const float& x , const float& y, const float& dt)
{

    this->Velocity.x += this->Acceleration * x * dt;
    this->Velocity.y += this->Acceleration *  y * dt;

}



void PhysicsComponents::updateMoveTime(const float& dt)
{
    
    if (this->movement_time < this->movement_timeMax)
       {
           this->movement_time += 10.f * dt;
       }

}

void PhysicsComponents::update(const float& dt)
{

    /*SLOWS DOWN THE SPRITE*/
    if (this->Velocity.x > 0.f) // Check for positive x
    {
        //Max velocity check
        if(this->Velocity.x > maxVelocity)
        {
           this->Velocity.x = this->maxVelocity;
        }
      
        //Deceleration
        this->Velocity.x -= Deceleration * dt;
       
        if(this->Velocity.x < 0.f)
        {
            this->Velocity.x = 0.f;
        }

    }
    else if (this->Velocity.x < 0.f) //Check for negative x
    {
        //Max Velocity Check
        if(this->Velocity.x < -maxVelocity)
        {
            this->Velocity.x = -this->maxVelocity;
        }
        
        //Decelreation
        this->Velocity.x += Deceleration * dt;
        
        if(this->Velocity.x > 0.f)
        {
            this->Velocity.x = 0.f;
        }
    }
    
    if (this->Velocity.y > 0.f) // check for positive y
    {
        //Max velocity check
        if(this->Velocity.y > maxVelocity)
        {
           this->Velocity.y = this->maxVelocity;
        }
      
        //Deceleration
        this->Velocity.y -= Deceleration * dt;
       
        if(this->Velocity.y < 0.f)
        {
            this->Velocity.y = 0.f;
        }
        
        
    }
    else if (this->Velocity.y < 0.f) //Check for negative y
    {
        //Max Velocity Check
        if(this->Velocity.y < -maxVelocity)
        {
            this->Velocity.y = -this->maxVelocity;
        }
        
        //Decelreation
        this->Velocity.y += Deceleration * dt;
        
        if(this->Velocity.y > 0.f)
        {
            this->Velocity.y = 0.f;
        }
    }
    
    //Final Move of the entity, most important expression
    this->sprite.move(this->Velocity * dt);
    
}


void PhysicsComponents::move_rand(const float& dt, int seed)
{
    this->updateMoveTime(dt);
    
    switch (seed) {
            
        case 1: 
            
            if(this->getMoveTime())
            {
                this->move(0, 4, dt);
            }
            
            break;
            
        case 2:
            
            if(this->getMoveTime())
            {
                this->move(0, -4, dt);
            }
                       
            break;
            
            
       case 3:
                       
          if(this->getMoveTime())
          {
            this->move(4, 0, dt);
          }
                                  
        break;
            
            
       case 4:
                           
         if(this->getMoveTime())
         {
           this->move(-4, 0, dt);
         }
                                      
         break;
        
            
        default:
            break;
    }
    
    
}

/**
           @brief Retrieve wether or not an object is moving in a particular direction
           @param One of the directions, supplied by the directions enumerator; to test the object against.
           @returns a true, or false depending on wether or not the object is moving in the supplied direction

*/
bool PhysicsComponents::getStatus(const short unsigned& state) const
{
    switch(state)
    {
        
        case movements::IDLE:
           
            if(this->Velocity.x == 0.f && this->Velocity.y == 0.f)
            {
                return true;
            }
            
            
            break;
            
        case movements::MOVING:
            
            if (this->Velocity.x !=0 || this->Velocity.y !=0)
               {
                   return true;
               }
               
            break;
            
        case movements::MOVING_LEFT:
           
            if (this->Velocity.x < 0.f)
            {
                return true;
            }
            
            break;
            
        case movements::MOVING_RIGHT:
           
            if(this->Velocity.x > 0.f)
            {
                return true;
            }
            
            break;
            
        case movements::MOVING_UP:
            
            if(this->Velocity.y < 0.f)
            {
                return true;
            }
           
            
            break;
            
        case movements::MOVING_DOWN:
            
            
            if (this->Velocity.y > 0.f)
            {
                return true;
            }
                    break;

        default:
            break;

    }
    
    return false;
}

const float& PhysicsComponents::getMaxVelocity() const
{
    return this->maxVelocity;
}

void PhysicsComponents::stopVelocity()
{
    this->Velocity.x = 0.f;
    this->Velocity.y = 0.f;
}

void PhysicsComponents::stopVelocityX()
{
    this->Velocity.x = 0.f;
}

void PhysicsComponents::stopVelocityY()
{
    this->Velocity.y = 0.f;
}

const float & PhysicsComponents::getAcceleration() const
{
    return this->Acceleration;
}

const float& PhysicsComponents::getDecceleration() const
{
    return this->Deceleration;
}

bool PhysicsComponents::getMoveTime()
{
    if (this->movement_time >= this->movement_timeMax)
       {
           this->movement_time = 0.f;
           return true;
       }

       return false;
    
}

const sf::Vector2f& PhysicsComponents::getVelocity() const
{
    return this->Velocity;

}
