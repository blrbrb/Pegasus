#include "stdafx.h"
#include "ObjectHandler.hpp"

ObjectHandler::ObjectHandler(std::vector<Object*>& Objects, std::map<std::string, sf::Texture>& textures) : Objects(Objects), textures(textures)
{
   // this->init_textures(); 
    this->Objects = Objects;
}

ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::Place_Object(short type, const float x, const float y)
{
    switch (type)
    {
    case ObjectTypes::LANTERN: 
            std::cout << "farted" << std::endl; 
            this->Objects.push_back(new Lantern(x, y));
        break;

    default:

        throw std::invalid_argument("ObjectHandler::Place_Object" "Const Short Object Type: " + std::to_string(type) + " is not a valid Object type!");
        break;

    }
}

void ObjectHandler::Remove_Object(const int index)
{  
    delete this->Objects[index];
    this->Objects.erase(this->Objects.begin() + index);
}

void ObjectHandler::update(const float& dt)
{ 

}

void ObjectHandler::init_textures()
{


}

void ObjectHandler::render(sf::RenderTarget* target)
{
}

const int ObjectHandler::getSize()
{
    return this->Objects.size(); 
}
