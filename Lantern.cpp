#include "stdafx.h"
#include "Lantern.hpp"

Lantern::Lantern(float x, float y)
{
    std::cout << "creating the lantern object... " << std::endl; 
    this->type = ObjectTypes::LANTERN;  
   
    this->initvariables(); 
    this->create_animation_componet(this->textures["LANTERN"]);
    this->setposition(x, y);
    this->initanimations(); 
    this->sprite.setScale(10, 10); 
}

Lantern::~Lantern()
{
}

void Lantern::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light, const bool render_hitbox)
{ 
    if (shader)
    {
       // std::cout << "rendering the object with a shader... " << std::endl;
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light);
        target.draw(this->sprite, shader);


    }

     if (render_hitbox) { 
        //std::cout << "rendering the object without a shader... " << std::endl; 
        this->hitbox->render(target);
    } 

     else 
     {
         //std::cout << "rendering the object without a shader... " << std::endl;
         target.draw(this->sprite);
     }

}

void Lantern::update(const float& dt, sf::Vector2f& MousePosView)
{
	//this->updateAnimation(dt);
}

const std::string Lantern::asString() const
{
    std::stringstream out;
    std::cout << this->type << " " << this->getPosition().x << " " << this->getPosition().y << std::endl; 
    out << this->type << " "<< this->getPosition().x << " " << this->getPosition().y;
    return std::string();
}


void Lantern::initanimations()
{
   // this->animationcomponet->add_animation("GLOW", 10.f, 0, 0, 8, 0, 10, 16);  
    //this->animationcomponet->add_animation("GLOW2", 10.f, 0, 0, 8, 0, 10, 16);
    std::cout << this->animationcomponet << std::endl; 
}


void Lantern::initvariables()
{
    this->create_hitbox_componet(this->sprite, 0, 0, 9.f, 16.f); 

}


void Lantern::updateAnimation(const float& dt)
{
    this->animationcomponet->play("GLOW", dt); 
   

}