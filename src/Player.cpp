//
//  Player.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 1/28/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#
#include "include/Player.hpp"

Player::Player(float x, float y, sf::Texture& textureSheet)
{


    this->initComponents();
    this->initInventory();
    this->setPosition(x, y);
    this->addAnimationComponent(textureSheet);

    this->initAnimations();
    this->animationcomponet->getName(1);
    this->initSounds();
    this->initLight();
    //this->sprite.setScale(2, 2);
    this->default_color = this->sprite.getColor();
    
}

Player::~Player() = default;

Player::Player(const std::string& save_file, sf::Texture& textureSheet)
{
    this->setPosition(10.f, 10.f);
    this->addAnimationComponent(textureSheet);
    this->loadFromFile(save_file);
    this->initLight();
   
}





//initalizer functions

void Player::initComponents()
{
    this->addPhysicsComponent(100.f, 20000.f, 200.f);
    this->addHitboxComponent(this->sprite, 0, 0, 52.f, 42.f);
    
    this->addSkillComponent();
    this->addAttributeComponent(1);
}

void Player::initInventory()
{
   this->inventory = new Inventory(100);
}

void Player::initLight()
{
    this->player_ambient.setRange(50.f); 
    this->player_ambient.setIntensity(0.2);
    this->edges.emplace_back(sf::Vector2f(200.f, 100.f),
        sf::Vector2f(200.f, 300.f));
}




void Player::initVariables()
{
    //this->attacking = false; 
}

void Player::initAnimations()
{
 
    this->animationcomponet->add_animation("IDLE_BLINKING", 4.f, 0, 2, 15, 2, 62, 74); //first row, second* sprite across *iterator starts from unsigned 0
    this->animationcomponet->add_animation("WALK_RIGHT", 5.f, 1, 1, 15, 1, 62, 74);
    this->animationcomponet->add_animation("WALK_LEFT", 5.f, 0, 0, 15, 0, 62, 74);
    this->animationcomponet->add_animation("WALK_DOWN", 5.f, 0, 0, 15, 0, 62, 74);
    this->animationcomponet->add_animation("WALK_UP", 5.f, 0, 3, 2, 3, 62, 74);  

                  
    //lol
    //this->animtioncomponet->add_animation("PISSING_PANTS", 10.f, 0, 0, 5, 0, 16, 16);
    
}

void Player::initSounds()
{ 
   
}
    
//FUCK THIS FUCK THIS ASS THIS ASS IS RETARDED. FUCK FUCK FUCK I HATE THIS. KILL. KILL. KILL. IDIOT FART. IDIOT FART DICKS 
void Player::updateAnimation(const float& dt)
{
    /*!
    @brief Change the player's animations based on which direction they're walking in

    @param const float& dt

    @return void
     */

    this->physicsComponents->update(dt);
    //if there ever was a valid reason to shoot someone, it's this 
    //stupid useless hanging pointer error right here. 
    //FIX: (return an adress, not a pointer you fucking simpleton)
    if (this->physicsComponents->getStatus(IDLE))
    {
        this->animationcomponet->play("IDLE_BLINKING", dt);
        //this->soundcomponent->play("WALK", dt);

        // this->soundcomponent->stop("WALK");
    }

    else if (this->physicsComponents->getStatus(MOVING_RIGHT))
    {
        this->animationcomponet->play("WALK_RIGHT", dt);
        //this->soundcomponent->play("WALK", dt, 1.f); 
    }

    else if (this->physicsComponents->getStatus(MOVING_LEFT))
    {
        this->animationcomponet->play("WALK_LEFT", dt);

        //this->soundcomponent->play("WALK", dt, 1.f); 
    }

 //change the sprite's color to red if the player is loosing HP 
      



      
}




void Player::update(const float& dt, sf::Vector2f& MousePosView)
{
    this->attributes->update();

    this->attributes->updateMagic(dt); 

    this->physicsComponents->update(dt);
    
    this->updateLighting(dt);

    this->updateAnimation(dt);

   
    
    this->hitbox->update();
    
   
    
   
}

void Player::updateLighting(const float& dt)
{
    this->player_ambient.setPosition(sf::Vector2f(this->sprite.getGlobalBounds().left + (this->sprite.getGlobalBounds().width / 2 ), this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height));
    //this->player_ambient.setPosition(sf::Vector2f(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2));
    this->player_ambient.castLight(this->edges.begin(), this->edges.end()); 
}





void Player::render(sf::RenderTarget &target, sf::Shader* shader,const sf::Vector2f& light, const bool render_hitbox)
{
   
    const sf::Color testcolor2 = sf::Color(250, 250, 250, 250);
    
    if (shader)
    { 
       // spotlight light1();
        
       
       // shader->setUniform("lights", player_light.light_system.at(node_count))
          shader->setUniform("lightPos", light);
          shader->setUniform("hasTexture", true);
        //shader->setUniform("Intensity", sf::Glsl::Vec4(testcolor2));
       // shader->setUniform("color", sf::Glsl::vec)
       // shader->setUniform("Radius", sf::Vector2f(10.f, 10.f));
        
        target.draw(this->player_ambient);
        target.draw(this->sprite, shader);
        
       
    }
   

    else if(render_hitbox) {
        this->hitbox->render(target); 
    }


   
}

StatusComponet *Player::getStatusComponent()
{
    return this->attributes;
}


Inventory* Player::getInventory()
{
    return this->inventory; 
}


const std::string& Player::toString() const
{
    std::stringstream ss; 
    
    const StatusComponet* sc = this->attributes; 
   
    ss << "Level: " << sc->level << "\n"
        << "Exp: " << sc->exp << "\n"
        << "Exp next: " << sc->expNextlvl << "\n";
    
        return ss.str(); 

}

void Player::saveToFile(const std::string& filename)
{
    this->pt = new boost::property_tree::ptree; 
    ///int
    this->set_property<int>("pony.hp", this->getStatusComponent()->hpMax);
    ///int
    this->set_property<int>("pony.level", this->getStatusComponent()->level);
    ///int
    this->set_property<int>("pony.exp", this->getStatusComponent()->exp);
    ///const float
    this->set_property<float>("pony.physics.a", this->physicsComponents->getAcceleration());
    ///const float
    this->set_property<float>("pony.physics.-a", this->physicsComponents->getMaxVelocity());
    ///const float
    this->set_property<float>("pony.physics.mv", this->physicsComponents->getMaxVelocity());

    for (int x = 0; x < this->animationcomponet->getSize(); x++) {
        this->set_property<float>("pony.animations." + this->animationcomponet->getName(x) + ".time", this->animationcomponet->getTimer(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) +".start.x",this->animationcomponet->getStartX(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".start.y", this->animationcomponet->getStartY(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".start.width", this->animationcomponet->getStartRectWidth(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".start.height", this->animationcomponet->getStartRectHeight(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".width", this->animationcomponet->getWidth(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".height", this->animationcomponet->getHeight(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".end.x", this->animationcomponet->getEndX(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".end.y", this->animationcomponet->getEndY(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".end.width", this->animationcomponet->getEndRectWidth(x));
        this->set_property<int>("pony.animations." + this->animationcomponet->getName(x) + ".end.height", this->animationcomponet->getEndRectHeight(x));
    }  
    ///float
    this->set_property<float>("pony.hitbox.offset.y", this->hitbox->getOffset().y);
    ///float
    this->set_property<float>("pony.hitbox.offset.x", this->hitbox->getOffset().x); 
    ///float
    this->set_property<float>("pony.hitbox.width", this->hitbox->getSize().x);
    ///float
    this->set_property<float>("pony.hitbox.height", this->hitbox->getSize().y);
    ///float
    
    boost::property_tree::json_parser::write_json(filename, *pt);
}

void Player::loadFromFile(const std::string& filename)
{
    this->pt = new boost::property_tree::ptree;
    boost::property_tree::json_parser::read_json(filename, *this->pt);

    this->addPhysicsComponent(this->pt->get<float>("pony.physics.mv"), this->pt->get<float>("pony.physics.a"),
                              this->pt->get<float>("pony.physics.-a"));
    this->addHitboxComponent(this->sprite, this->pt->get<float>("pony.hitbox.offset.x"),
                             this->pt->get<float>("pony.hitbox.offset.y"), this->pt->get<float>("pony.hitbox.width"),
                             this->pt->get<float>("pony.hitbox.height"));
    this->addSkillComponent();
    this->addAttributeComponent(this->pt->get<int>("pony.level"));
    this->initInventory();
   

    for (boost::property_tree::ptree::value_type& animation : pt->get_child("pony.animations")) 
    {
         //LOG(INFO) << "Initializing animations...";
        //LOG(INFO) << animation.first << std::endl;
        this->animationcomponet->add_animation(animation.first, animation.second.get<float>("time"), animation.second.get<int>("start.x"), animation.second.get<int>("start.y"), animation.second.get<int>("end.x"), animation.second.get<int>("end.y"), animation.second.get<int>("width"), animation.second.get<int>("height"));
    }
}


