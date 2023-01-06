//
//  AnimationComponet.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 1/30/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "stdafx.h"
#include "AnimationComponet.hpp" 



AnimationComponet::AnimationComponet(sf::Sprite& sprite, sf::Texture& texturesheet) :
sprite(sprite), texturesheet(texturesheet), lastAnimation(NULL), priorityAnimation(NULL)
{

    
   
    
}

AnimationComponet::~AnimationComponet()
{
    
    for (auto &i : this->Animations.left)
    {
        delete i.second;
        
    }
    
}

//*Functions*
void AnimationComponet::add_animation(const std::string& key, float animationtimer,int start_x, int start_y, int end_x, int end_y, int width, int height)
{
   
    this->Animations.insert(animation(key, new Animation(this->texturesheet, this->sprite, animationtimer, start_x, start_y, end_x, end_y, width, height)));
    this->names.push_back(this->Animations.right.at(this->Animations.left.at(key)));

}

const bool& AnimationComponet::play(const std::string& key, const float& dt, const bool priority )
{
    
    if(this->priorityAnimation) //*if a priority animation exists, play it first
    {
        
        if (this->priorityAnimation == this->Animations.left.at(key))
        {
          
          if (this->lastAnimation != this->Animations.left.at(key))
          {
              
              if (this->lastAnimation == NULL)
                  this->lastAnimation = this->Animations.left.at(key);
              
              
              else
              {
                  this->lastAnimation->reset();
                  this->lastAnimation = this->Animations.left.at(key);
              }
          }
            //if the priority animation is finished 
            if(this->Animations.left.at(key)->play(dt))
            {
                this->priorityAnimation = NULL;
            }
            
        }
        
    }
    
    else // Play an animation if no other priority animations exist
    {
        if (priority)
        {
            this->priorityAnimation = this->Animations.left.at(key);
        }
        
    if (this->lastAnimation != this->Animations.left.at(key))
    {
        
        if (this->lastAnimation == NULL)
            this->lastAnimation = this->Animations.left.at(key);
        
        
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->Animations.left.at(key);
        }
    }
    
        this->Animations.left.at(key)->play(dt);
        
    }
    return this->Animations.left.at(key)->getDone();
}

const bool& AnimationComponet::play(const std::string& key, const float& dt, const float& speed, const float& speed_max, const bool priority)
{
    if(this->priorityAnimation) //*if a priority animation exists, play it first
    {
           
           if (this->priorityAnimation == this->Animations.left.at(key))
           {
             
             if (this->lastAnimation != this->Animations.left.at(key))
             {
                 
                 if (this->lastAnimation == NULL) 
                 {
                     this->lastAnimation = this->Animations.left.at(key);
                 }
                 else
                 {
                     this->lastAnimation->reset();
                     this->lastAnimation = this->Animations.left.at(key);
                 }
             }

                    
        
            if(this->Animations.left.at(key)->play(dt, abs(speed / speed_max)))
               {
                this->priorityAnimation = NULL;
               }
            }
    }
               
    else
        {
            //if there is a priority animation, set true 
            if (priority)
            {
                this->priorityAnimation = this->Animations.left.at(key);
            }
            
    if (this->lastAnimation != this->Animations.left.at(key))
    {
        if (this->lastAnimation == NULL)
            this->lastAnimation = this->Animations.left.at(key);
        
        
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->Animations.left.at(key);
        }
    }
    
    this->Animations.left.at(key)->play(dt, abs(speed / speed_max));
    
}
    return this->Animations.left.at(key)->getDone();
} 

//*End Functions*

//*Accessors*
const bool& AnimationComponet::getDone(const std::string key)
{
    return this->Animations.left.at(key)->getDone();
    
}

const std::string& AnimationComponet::getName(int index)
{
    if (this->names.empty())
        return "empty";
    else
        return names.at(index);
    
}

const int& AnimationComponet::getWidth(int index)
{
  return this->Animations.left.at(names.at(index))->getAnimationWidth();
}

const int& AnimationComponet::getHeight(int index)
{
    return this->Animations.left.at(names.at(index))->getAnimationHeight();
}

const int& AnimationComponet::getStartRectLeft(int index)
{
    return this->Animations.left.at(names.at(index))->getStartRectLeft();
}

const int& AnimationComponet::getStartRectTop(int index)
{
    return this->Animations.left.at(names.at(index))->getStartRectTop();
}
const int& AnimationComponet::getStartRectWidth(int index)
{
    return this->Animations.left.at(names.at(index))->getStartRectWidth(); 
}

const int& AnimationComponet::getStartRectHeight(int index)
{
    return this->Animations.left.at(names.at(index))->getStartRectHeight();
}

const float& AnimationComponet::getTimer(int index)
{
    return this->Animations.left.at(names.at(index))->getTimer();
}

const int& AnimationComponet::getEndRectLeft(int index)
{
    return this->Animations.left.at(names.at(index))->getEndRectLeft();
}

const int& AnimationComponet::getEndRectTop(int index)
{
    return this->Animations.left.at(names.at(index))->getEndRectTop();
}

const int& AnimationComponet::getEndRectWidth(int index)
{
    return this->Animations.left.at(names.at(index))->getEndRectWidth();
}

const int& AnimationComponet::getEndRectHeight(int index)
{
    return this->Animations.left.at(names.at(index))->getEndRectHeight();
}

const int& AnimationComponet::getSize() const
{
    return this->Animations.left.size(); 
}

const int& AnimationComponet::getStartX(int index) const
{
    return this->Animations.left.at(names.at(index))->getStartX();
}

const int& AnimationComponet::getStartY(int index) const
{
    return this->Animations.left.at(names.at(index))->getStartY();
}

const int& AnimationComponet::getEndX(int index) const
{
    return this->Animations.left.at(names.at(index))->getEndX(); 
}

const int& AnimationComponet::getEndY(int index) const
{
    return this->Animations.left.at(names.at(index))->getEndY();
}

