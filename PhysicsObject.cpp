#include "stdafx.h"
#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(float x, float y,const sf::Texture& texture)
{
	this->object.setTexture(texture);
	this->object.setPosition(x, y); 
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light)
{
}

void PhysicsObject::update(const float& dt, const sf::Vector2f MousePosView)
{
}

void PhysicsObject::inithitbox()
{
}


void PhysicsObject::create_animation_component(sf::Texture& texture)
{
	this->animationcomponent->create
}
