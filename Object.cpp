#include "stdafx.h"
#include "Object.hpp"

Object::Object()
{
	this->type = ObjectTypes::EMPTY; 
	this->is_object = true; 
	this->inittextures(); 

}

Object::Object(float x, float y)
{
	this->type = type; 
}

Object::~Object()
{
}



void Object::updateAnimation(const float& dt)
{
}

void Object::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light, const bool render_hitbox)
{
}


void Object::inittextures()
{
	if (!this->textures["LANTERN"].loadFromFile("Resources/Assets/Entity/Objects/lantern.png"))
	{
		std::cout << "ERROR Could not load lantern object texture GameState lin 171" << std::endl;

	}
}


