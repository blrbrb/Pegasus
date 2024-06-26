//
//  EnemySpawner.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "stdafx.h"
#include "EnemySpawner.hpp"


EnemySpawner::EnemySpawner(float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, int type, int amount, sf::Int32 time_to_spawn, float max_distance) : Tile(TileTypes::SPAWNER, x, y, gridsize_f, texture, texturerect, false)
{
    //Init variables
    this->Enemy_type = type;
   
    this->Enemy_amount = amount;
    this->Enemy_counter = 0;
    this->timer = time_to_spawn;
    this->maxDistance = max_distance;
    this->Spawned = false;
    this->maxDistance = max_distance;
    this->SpawnTimer.restart();
    
     
}
 
EnemySpawner::~EnemySpawner()
{
    
    

}

void EnemySpawner::clear()
{
    
}

void EnemySpawner::update(const float& dt)
{
    
    if (this->canSpawn())
    this->Spawned = false; 
}

void EnemySpawner::render(sf::RenderTarget& target, sf::Shader* shader,sf::Vector2f LightPosition)
{

    if (shader)
    {
       
        shader->setUniform("lightPos", LightPosition);
 
        target.draw(this->rect, shader);

    }

    else
    {
        target.draw(this->rect);
    }
}



const std::string EnemySpawner::asString() const 
{
    std::stringstream ss;

    std::cout << std::hex << "timer " <<  this->timer << std::endl;
   // std::cout << "writing an Enemy Spawaner Tile... " << std::endl; 
    ss << std::hex << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->Enemy_type
       << " " << this->Enemy_amount << " " << this->timer << " " << this->maxDistance;
    
    //std::cout << ss.str() << std::endl;
   // boost::hex; 

    return ss.str();
    
}


void EnemySpawner::savetoFile(std::ofstream& out)
{
    
    //DEPRECIATED
    out << std::hex << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->Enemy_type
        << " " << this->Enemy_amount << " " << this->timer << " " << this->maxDistance << " "; 

}

void EnemySpawner::SetSpawned(const bool spawned)
{
    this->Spawned = spawned;
    this->SpawnTimer.restart();
}

void EnemySpawner::add_object(short type, sf::Vector2f& object_position)
{
}

const bool &EnemySpawner::getSpawned() const
{
    return this->Spawned; 
}

const int & EnemySpawner::getEnemyCounter() const
{
    return this->Enemy_counter;
}

const float& EnemySpawner::getMaxDistance() const
{
    return this->maxDistance; 
}

const int& EnemySpawner::getEnemyType() const
{
    return this->type;
}

const sf::Int32& EnemySpawner::getTime() const
{
    return this->timer; 
}

const bool EnemySpawner::canSpawn() const
{
    if (this->SpawnTimer.getElapsedTime().asSeconds() >= this->timer)
    {

        return true;
    }
    return false;
}

void EnemySpawner::increaseEnemyCounter()
{
    if (this->Enemy_counter > this->Enemy_amount)
        this->Enemy_counter = this->Enemy_amount;
    else
        ++this->Enemy_counter;
}

void EnemySpawner::decreaseEnemyCounter()
{
    if (this->Enemy_counter < 0)
        this->Enemy_counter = 0;
    else
        --this->Enemy_counter;
}

const int &EnemySpawner::getEnemyAmount() const
{
    return this->Enemy_amount;
}


