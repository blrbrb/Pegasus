//
//  Entity.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/23/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "include/Entity.hpp"


Entity::Entity()
{

    this->initVariables();
    
}
const sf::Vector2f &Entity::getPosition() const
{
    /*!
                            
               @interface Entity();
     
                @class Entity
     
                @brief  Fetch the position of the entity relative to the window
    
                @param  void
     
                @return const sf::Vector2f&     The position of the entity
     
                @see getGridPosition();

     */

    if(this->hitbox) {
        return this->sprite.getPosition(); }
    
    return this->sprite.getPosition();
        
}


const sf::Vector2f Entity::getCenter() const
{
    /*!
     @class Entity
     
     @brief Fetch the center of the entity's sprite
     
     @param void
     
     @return const sf::Vector2f     The Center
     
     */
    
  if (this->hitbox)
      return this->hitbox->getPosition() +
      sf::Vector2f
      (
          this->hitbox->getGlobalBounds().width / 2.f,
          this->hitbox->getGlobalBounds().height / 2.f
      );

  return
      this->sprite.getPosition() +
      sf::Vector2f
      (
          this->sprite.getGlobalBounds().width / 2.f,
          this->sprite.getGlobalBounds().height / 2.f
      );
}

// Apply the final movements and animations to the entity
void Entity::update(const float& dt, sf::Vector2f& MousePosView) {
   
    if (this->physicsComponents)
    {
        this->physicsComponents->update(dt);
    }
    
}

Entity::~Entity() {
    
    delete this->hitbox;
    delete this->physicsComponents;
    delete this->animationcomponet;
    delete this->attributes;
    delete this->skillcomponent;
   
}

void Entity::initVariables()
{
    this->texture = nullptr;
   
    this->hitbox = nullptr;
    this->attributes = nullptr;
    this->physicsComponents = nullptr;
    this->skillcomponent = nullptr;

}

void Entity::setTexture(sf::Texture& texture)
{
    this->texture = &texture;
    this->sprite.setTexture(texture);
    
}



void Entity::rotate(float angle)
{
    this->sprite.rotate(angle); 
    
}

void Entity::setOrigin(sf::Vector2f origin)
{
    this->sprite.setOrigin(origin); 
}

void Entity::setColor(sf::Color color)
{
    this->sprite.setColor(color);
}

void Entity::setScale(float scale_x, float scale_y)
{
    this->sprite.setScale(sf::Vector2f(scale_x, scale_y));
}




void Entity::addPhysicsComponent(const float maxVelocity, const float Acceleration, const float Deceleration)
{
    
    this->physicsComponents = new PhysicsComponents(this->sprite, maxVelocity, Acceleration, Deceleration);
    
}

void Entity::addAnimationComponent(sf::Texture& texturesheet)
{
    
    this->animationcomponet = new AnimationComponet(this->sprite, texturesheet);
    
    
}


void Entity::setPosition(const float& x, const float& y)
{
    if(this->hitbox) {
        this->sprite.setPosition(x, y); }

    else {
        
        this->sprite.setPosition(x, y); }
}


void Entity::render(sf::RenderTarget& target,sf::Shader* shader,const sf::Vector2f light, const bool render_hitbox)
{
    
}

void Entity::move(const float& dt, const float& x, const float& y) {
    
    if(this->hitbox)
        this->physicsComponents->move(x, y, dt);
        
    else
        this->sprite.move(x,y);
    
}

void Entity::addAttributeComponent(const unsigned level)
{
    this->attributes = new StatusComponet(level);
    
}



void Entity::addHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{

    this->hitbox = new HitBoxComponet(sprite, offset_x, offset_y, width, height);
    
    
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    if(this->hitbox) {
        return this->hitbox->getGlobalBounds(); }
    else 
    return this->sprite.getGlobalBounds();
    

    
}

const sf::Vector2i Entity::getGridPosition(const int& gridSizeI) const
{
    /**
                            
        @class Entity
     
        @brief Retrieve the position of an Entity relative to the tile grid
     
        @discussion If the entity has a hitbox element attached, the function will return the position of the hitbox divided by the gridSize, if not and there is only an entity present .The function will return the sprite's position divided by the gridSize
     
        @param const int        GridSize
     
        @return const sf::Vector2i      The position of the entity relative to the grid
     
     */
   
    if(this->hitbox)
        return sf::Vector2i(static_cast<int>(this->hitbox->getPosition().x) / gridSizeI, static_cast<int>(this->hitbox->getPosition().y) / gridSizeI);
    
    else
        return
        sf::Vector2i(static_cast<int>(this->sprite.getPosition().x) / gridSizeI, static_cast<int>(this->sprite.getPosition().y) / gridSizeI);
}



const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
    if(this->hitbox && this->physicsComponents)
    {
        return this->hitbox->getNextPosition(this->physicsComponents->getVelocity() * dt);
    }
    
 else
    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}



void Entity::stopVelocity()
{
    //important to make sure stopVelocityY() is called here to ensure proper collision
    
    if (this->physicsComponents)
        this->physicsComponents->stopVelocityY();
}



void Entity::stopVelocityX()
{
     //important to make sure stopVelocityX() is called here to ensure proper collision
    if (this->physicsComponents)
        this->physicsComponents->stopVelocityX();
}



void Entity::stopVelocityY()
{
    if (this->physicsComponents)
        this->physicsComponents->stopVelocityY();
}




void Entity::addSkillComponent()
{
    this->skillcomponent = new SkillComponent(); 
}

void Entity::setRotation(float rot)
{
    this->sprite.setRotation(rot); 
}



void Entity::move_rand(const float &dt, int seed)
{
    if(this->hitbox)
        this->physicsComponents->move_rand(dt, seed);
           
       else
           this->sprite.move(0,0);
    
    
}



const float Entity::getDistance(const Entity& entity) const
{
    return sqrt(pow(this->getCenter().x - entity.getCenter().x, 2) + pow(this->getCenter().y - entity.getCenter().y, 2));
    
}

const sf::Texture* Entity::getTexture() const
{
    return this->sprite.getTexture();
}

const sf::Color& Entity::getColor() const
{
    return this->sprite.getColor(); 
}




