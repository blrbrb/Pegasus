//
//  State.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#include "stdafx.h"
#include "State.hpp"


State::State(StateData* state_data)  {
    
    if (state_data != nullptr) {
        this->state_data = state_data;
        std::cout << "state data is working" << std::endl; 
    } 
    else 
    {
       
        std::cout << "statedata is nullptr" << std::endl; 
    }
    this->window = state_data->window; 
    this->supportedkeys = state_data->supportedkeys;
    this->states = state_data->states;
    this->quit = false;
    this->paused = false;
    this->keytime = 0.f; 
    this->keytime_MAX = 2.3f;
    this->gridsize = *state_data->gridsize;  
  
   
     
}

State::~State() {
    
    
}


const bool State::getkeytime()
{
  
    
    if (this->keytime >= this->keytime_MAX)
    {
        this->keytime = 0.f;
        return true;
    }
    
    return false;
}
    
    

const bool & State::getquit()const
{
   
    
    return this->quit;
    
}

void State::endstate()
{
   
    this->quit = true;
    
    
}
    
  
void State::updateInput(const float& dt)
{
        
        
}


void State::updateMousePosition(sf::View* view)
{
    
    
    this->MousePosScreen = sf::Mouse::getPosition();
    this->MousePosWindow = sf::Mouse::getPosition(*this->window);

    if(view)
      this->window->setView(*view);
    
    
    this->MousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));  

    if(this->state_data->gridsize->y) 
        this->MousePosGridI = sf::Vector2i(static_cast<int>(this->MousePosView.x) / static_cast<int>(this->gridsize.x),
            static_cast<int>(this->MousePosView.y) / static_cast<int>(this->gridsize.y)); 


    this->MousePosGridF = sf::Vector2f(this->MousePosView.x / static_cast<int>(this->gridsize.x),
        this->MousePosView.y / static_cast<int>(this->gridsize.y));
    
    /*else 
    this->MousePosGrid = sf::Vector2i(static_cast<int>(this->MousePosView.x) / static_cast<int>(this->gridsize.x),
                                      static_cast<int>(this->MousePosView.y) / static_cast<int>(this->gridsize.y)); */
   
   
    this->window->setView(this->window->getDefaultView());
}

void State::updatekeytime(const float& dt)
{
 
    if (this->keytime < this->keytime_MAX)
    {
        this->keytime += 10.f * dt;
    }

}




void State::Pause_State()
{
   
    this->paused = true;
}


void State::Unpause_State()
{
    
  
    this->paused = false; 
    
}

void State::create_sound_component()
{
    this->soundcomponent = new SoundComponent(); 

}


