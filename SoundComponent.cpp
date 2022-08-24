#include "stdafx.h"
#include "SoundComponent.h"
#include "SoundComponent.h"

SoundComponent::SoundComponent()
{
}

SoundComponent::~SoundComponent()
{
    for (auto& i : this->sounds)
    {
        delete i.second;

    }
}

void SoundComponent::add_sound(const std::string& key, float timer, sf::SoundBuffer& buffer)
{
    
    this->sounds[key] = new Sound(buffer,timer);
}


const bool& SoundComponent::play(const std::string& key, const float& dt, const float& speed)
{
    this->sounds[key]->play(dt, speed); 
    return true;
}



void SoundComponent::update(const float& dt)
{ 
  
}

const bool& SoundComponent::getDone(const std::string key)
{
    return false; 
}
