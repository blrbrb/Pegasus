//
//  State.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#
#include "include/State.hpp"


State::State(StateData* state_data) :state_ID(0)  {
    

    if (state_data != nullptr) {
        this->state_data = state_data;
        std::cout << "state data working as normal" << std::endl; 
    } 
    else 
    {
        //LOG(WARNING) << "the state data was nullptr..."; 
    }
    this->window = state_data->window; 
    this->supportedKeys = state_data->supportedKeys;
    this->states = state_data->states;
    this->quit = false;
    this->paused = false;
    this->keyTime = 0.f;
    this->keyTimeMax = 2.3f;
    this->gridSize = *state_data->gridSize;
   
   
     
}

State::~State() {
    delete this->state_data;
}


bool State::getKeyTime()
{
  
    
    if (this->keyTime >= this->keyTimeMax)
    {
        this->keyTime = 0.f;
        return true;
    }
    
    return false;
}

void State::log(std::string stat, std::string log_instance)
{ 
   

   
}

  

const bool & State::getQuit()const
{
   
    
    return this->quit;
    
}

void State::endState()
{   
    
    //LOG(INFO) << &this->quit;
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

    if(this->state_data->gridSize->y)
        this->MousePosGridI = sf::Vector2i(static_cast<int>(this->MousePosView.x) / static_cast<int>(this->gridSize.x),
            static_cast<int>(this->MousePosView.y) / static_cast<int>(this->gridSize.y));


    this->MousePosGridF = sf::Vector2f(this->MousePosView.x / static_cast<int>(this->gridSize.x),
        this->MousePosView.y / static_cast<int>(this->gridSize.y));
    
    /*else 
    this->MousePosGrid = sf::Vector2i(static_cast<int>(this->MousePosView.x) / static_cast<int>(this->gridSize.x),
                                      static_cast<int>(this->MousePosView.y) / static_cast<int>(this->gridSize.y)); */
   
   
    this->window->setView(this->window->getDefaultView());
}

void State::updateKeyTime(const float& dt)
{
 
    if (this->keyTime < this->keyTimeMax)
    {
        this->keyTime += 10.f * dt;
    }

}

void State::initFiles()
{


}



void State::pause()
{
   
    this->paused = true;
}


void State::unpause()
{
    
  
    this->paused = false; 
    
}

