#include "stdafx.h"
#include "ObjectTile.hpp"

ObjectTile::ObjectTile(float obX, float obY, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, short object_type) : Tile(TileTypes::OBJECT, obX, obY, gridsize_f, texture, texturerect, false)
{
   
    this->rect.setTexture(texture);
    this->create_animation_componet();
    this->animationcomponent = new AnimationComponet(this->rect, texture);
    this->initAnimations();
    this->object_type = ObjectTypes::LANTERN;
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
   
    out << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->object_type << " " << std::setprecision(20) << this->rect.getPosition().x << " " <<  std::setprecision(20) << this->rect.getPosition().y;
    return out.str(); 
}

const TileData ObjectTile::asData() { 
    this->tiledata.collision = this->collison_enabled; 
    this->tiledata.obX = this->rect.getPosition().x; 
    this->tiledata.obY = this->rect.getPosition().y; 
    this->tiledata.texturerect = this->rect.getTextureRect(); 
    this->tiledata.type = this->type; 
    this->tiledata.object_type = this->object_type; 

    return this->tiledata; 
  
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
  
    out.write(reinterpret_cast<const char*>(&this->type), sizeof(this->type));
    out.write(reinterpret_cast<const char*>(&this->rect.getTextureRect().left), sizeof(this->rect.getTextureRect().left));
    out.write(reinterpret_cast<const char*>(&this->rect.getTextureRect().top), sizeof(this->rect.getTextureRect().top));
    out.write(reinterpret_cast<const char*>(&this->collison_enabled), sizeof(this->collison_enabled));  
    out.write(reinterpret_cast<const char*>(&this->object_type), sizeof(this->object_type));
    out.write(reinterpret_cast<const char*>(&this->rect.getPosition().x), sizeof(this->rect.getPosition().x));
    out.write(reinterpret_cast<const char*>(&this->rect.getPosition().y), sizeof(this->rect.getPosition().y));
    


}


void ObjectTile::initAnimations()
{
   
    this->animationcomponent->add_animation("GLOW", 50.f, 0, 0, 7, 0, 9, 16);
   
}


void ObjectTile::create_animation_componet()
{
    
    this->animationcomponent = new AnimationComponet(this->rect, this->texture);


}
