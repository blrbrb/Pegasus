#include "stdafx.h"
#include "ObjectTile.hpp"

ObjectTile::ObjectTile(float obX, float obY, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, short object_type) : Tile(TileTypes::OBJECT, obX, obY, gridsize_f, texture, texturerect, false)
{
    this->object_type = object_type;
    std::cout << "object type in init " << this->object_type << std::endl;
    this->rect.setTexture(texture);
    this->create_animation_componet();
    this->animationcomponent = new AnimationComponet(this->rect, texture);
    this->initAnimations();
    this->type = TileTypes::OBJECT; 
   this->rect.setTextureRect(sf::IntRect(0, 0, 9, 16));
   this->rect.setPosition(obX, obY); 

   // std::cout << "setting the object tile at position... " << obX << " " << obY << "\n"; 
   
}

ObjectTile::~ObjectTile()
{



}

const std::string ObjectTile::asString() const
{
    //std::cout << this->object_type << std::endl; 
    //std::cout << "Obj Tile Info: " << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->object_type << " " << std::setprecision(5) << std::setprecision(5) << this->rect.getPosition().x << " " << std::setprecision(5) << this->rect.getPosition().y;
    std::stringstream out; 
   
    out << std::hex << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->object_type << " " << std::setprecision(20) << this->rect.getPosition().x << " " <<  std::setprecision(20) << this->rect.getPosition().y;
    return out.str(); 
}



const sf::Texture* ObjectTile::getTexture() const
{
    return this->rect.getTexture(); 
}

const sf::Vector2f& ObjectTile::getObjectposition() const
{
    return this->rect.getPosition(); 
}

void ObjectTile::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f LightPosition)
{

   
    

    if (shader)
    {
       
        
        shader->setUniform("lightPos", LightPosition);
        
        //shader->setUniform  ("ambientColor", sf::Glsl::Bvec4(100, 100, 40, 20));
        //shader->setParameter("lightIntensity", sf::Vector2f(0.02, 0.02)); 
        //shader->setParameter("fragmentUV", LightPosition); 
        //shader->setParameter("fragmentColor", sf::Vector2f(0.02, 0.02)); 
        //shader->setParameter("fragmentPosition", LightPosition); 


        target.draw(this->rect, shader);
    }

    else
    {
        target.draw(this->rect);

    }
}

void ObjectTile::update(const float& dt)
{
   // std::cout << "object animation " << std::endl; 
    this->animationcomponent->play("GLOW", dt, true);
}
void ObjectTile::savetoFile(std::ofstream& out)
{
    out << std::hex << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->object_type << " " << std::hexfloat << this->rect.getPosition().x << " " << std::hexfloat << this->rect.getPosition().y << " ";
    


}


void ObjectTile::initAnimations()
{
   
    this->animationcomponent->add_animation("GLOW", 50.f, 0, 0, 7, 0, 9, 16);
   
}



void ObjectTile::create_animation_componet()
{
    
    this->animationcomponent = new AnimationComponet(this->rect, this->texture);


}

