#include "stdafx.h"
#include "Lantern.hpp"

Lantern::Lantern(float x, float y)
{
    this->type = ObjectTypes::LANTERN; 
    this->initvariables(); 
    this->create_animation_componet(texture);
    this->setposition(x, y);
    this->initanimations();
}

Lantern::~Lantern()
{
}

void Lantern::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light, const bool render_hitbox)
{ 
    if (shader)
    {

        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light);
        target.draw(this->sprite, shader);


    }

    else if (render_hitbox) {
        this->hitbox->render(target);
    }

}

void Lantern::update(const float& dt, sf::Vector2f& MousePosView)
{
	this->updateAnimation(dt);
}

const std::string Lantern::asString() const
{
    std::stringstream out;
   
    out << this->type << " " << this->is_object << " " << this->getPosition().x << " " << this->getPosition().y;
    return std::string();
}

void Lantern::initanimations()
{
    this->animationcomponet->add_animation("GLOW", 10.f, 0, 0, 8, 0, 9, 16);  
    this->animationcomponet->add_animation("GLOW2", 10.f, 0, 0, 8, 0, 9, 16);
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