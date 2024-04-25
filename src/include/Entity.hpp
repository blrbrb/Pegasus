//
//  Entity.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/23/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Entity_hpp
#define Entity_hpp
#include "HitBoxComponet.hpp"
#include "PhysicsComponents.hpp"
#include "AnimationComponet.hpp"
#include "StatusComponet.hpp"
#include "SkillComponent.hpp"
#include "AudioComponent.h"
#include "Item.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class SkillComponent;

class Entity {
    
public:
    
    ///The Movement Component
    PhysicsComponents* physicsComponents{};
    ///The Animation Component
    AnimationComponet* animationcomponet{};
    /// The Hitbox Component
    HitBoxComponet* hitbox{};
    ///The Status Component
    StatusComponet* attributes{};
    /// The Skill Component 
    SkillComponent* skillcomponent{};
    //Speaker attached to the entity to play sounds, etc
    Sound::Speaker* speaker{};
    // The Sound Component

    ///The entity's sprite
    sf::Sprite sprite;

    ///Sprites for visual effects, deffered rendering, body parts etc 
    std::map<std::string, sf::Sprite*> sprites; 
    ///the texture used to generate the entity's sprite
    sf::Texture* texture{};

  
   


    sf::Sound sound; 

    boost::property_tree::ptree* pt{};

    //Constructor et Destructor
    Entity();
    virtual ~Entity();
   
     //Modifiers (Position and Physics) 
    virtual void setPosition(const float& x, const float& y);
        //texture and transformations
    void setTexture(sf::Texture& texture);
    void rotate(float angle);
    void setOrigin(sf::Vector2f origin);
    void setColor(sf::Color color); 
    void setScale(float scale_x, float scale_y);

    
    template<typename T>
    inline void set_property(const std::string property_name, T value) 
    {
        this->pt->put(property_name, value);
    
    }
   
    
    
    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    
    virtual const sf::Vector2f getCenter() const; 
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::Vector2i getGridPosition(const int& gridSizeI) const;
    virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
    virtual const float getDistance(const Entity& entity) const;
    virtual const sf::Texture* getTexture() const;   
    virtual const sf::Color& getColor() const;
    


    //Functions
    ///  Move the entity in a particular direction
    /// @param dt const float Delta-Time
    /// @param x   const float X-Acceleration
    /// @param y const float Y-Acceleration
    virtual void move(const float& dt, const float& x, const float& y);
    ///  Move the entity at a random interval, in random directions
    /// @param dt Delta-Time
    /// @param seed a Seed
    virtual void move_rand(const float& dt, int seed);
    
    virtual void update(const float& dt, sf::Vector2f& MousePosView) = 0;
    
    virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f &light, const bool render_hitbox) = 0;
    
    ///  Bring the Entity to a complete stop
    virtual void stopVelocity();
    ///  Stop the X Velocity of the Entity
    virtual void stopVelocityX();
    /// Stop the Y Velocity of the Entity
    virtual void stopVelocityY();
    
  
    //Component init functions
    ///  @brief Create the Physics component, which allows on screen manipulation of the entity based on any number of variables.\n Attach to the player, and use the provided move(x,y) methods when the player presses a keyboard key or a controller input
    ///  to create a basic player movement controller. \n
    ///   This component will be used to determine all physics interactions between objects and the entity / other entites
    ///
    /// @param maxVelocity The maximum overall speed the entity should be able to reach
    /// @param Acceleration The rate of acceleration the entity should have
    /// @param Deceleration The rate of deceleration the entity should have
    
    void addPhysicsComponent(const float maxVelocity, const float Acceleration, const float Deceleration);
    
    /// Generate the animation component for the entity
    /// @param texturesheet A textureSheet to split into an animation
    void addAnimationComponent(sf::Texture& texturesheet);


   
    
    /// Generate the entity's hitbox
    /// @param sprite The sprite used to represent the entity on screen
    /// @param offset_x The X offset for the hitbox
    /// @param offset_y The Y-offset for the hitbox
    /// @param width The width of the hitbox
    /// @param height The height of the hitbox
    void addHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    
    /// Generate the Leveling, Status, etc values for the entity
    /// @param level const unsigned level to start the entity out on
    void addAttributeComponent(const unsigned level);
    
    /// Generate the entity's skill component.
    void addSkillComponent();
       
    
    //Modifiers 
    virtual void setRotation(float rot); 

private:
    void initVariables();
   


};



#endif /* Entity_hpp */

