#include "stdafx.h"
#include "Object.hpp"

Object::Object()
{
	this->type = ObjectTypes::LANTERN; 
	

	this->inittextures(); 

}

Object::Object(float x, float y)
{
	this->type = type; 
	
	this->inittextures(); 
}

Object::~Object()
{
}



void Object::updateAnimation(const float& dt)
{
}

void Object::inittextures()
{
	std::cout << "the stupid fucking texture is being initalized " << std::endl; 
	if (!this->textures["LANTERN"].loadFromFile("Resources/Assets/Entity/Objects/lantern.png"))
	{
		std::cout << "ERROR Could not load lantern object texture GameState lin 171" << std::endl;

	}
}


