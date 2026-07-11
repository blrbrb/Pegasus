//
//  Entity.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/23/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Entity_hpp
#define Entity_hpp
#include "AnimationManager.hpp"
#include "HitBoxComponet.hpp"
#include "PhysicsComponents.hpp"
#include "SkillComponent.hpp"
#include "StatusComponet.hpp"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class SkillComponent;

class Entity{
public:

    std::unique_ptr<std::_NonArray<PhysicsComponents>> physicsComponents { };

    std::unique_ptr<std::_NonArray<AnimationManager>> animationcomponet { };

    std::unique_ptr<std::_NonArray<HitBoxComponet>> hitbox { };

    std::unique_ptr<std::_NonArray<StatusComponet>> attributes { };


    /// Sprites for visual effects, deffered rendering, body parts etc
    std::map<std::string, sf::Sprite*> sprites;
    /// the texture used to generate the entity's sprite



    /////////////////////////////////////////////////
    /// \brief construct an entity
    ///
    /// \param texture const sf::Texture&
    ///
    /////////////////////////////////////////////////
    Entity(const sf::Texture& texture);
    virtual ~Entity();


    /////////////////////////////////////////////////
    /// \brief move the entity forward for one frame by (x,y) pixels
    ///
    /// \param x const float&
    /// \param y const float&
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void setPosition(const float& x, const float& y);

    /////////////////////////////////////////////////
    /// \brief change the texture
    ///
    /// \param texture sf::Texture&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setTexture(sf::Texture& texture);
    /////////////////////////////////////////////////
    /// \brief rotate the sprite by angle degrees
    ///
    /// \param angle float
    /// \return void
    ///
    /////////////////////////////////////////////////
    void rotate(float angle);
    /////////////////////////////////////////////////
    /// \brief set the transform origin point (center) of the sprite
    ///
    /// \param origin sf::Vector2f
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setOrigin(sf::Vector2f origin);
    /////////////////////////////////////////////////
    /// \brief set the sprite's color
    ///
    /// \param color sf::Color
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setColor(sf::Color color);
    /////////////////////////////////////////////////
    /// \brief scale the sprite up by (x,y)
    ///
    /// \param scale_x float
    /// \param scale_y float
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setScale(float scale_x, float scale_y);


    /////////////////////////////////////////////////
    /// \brief the screen position of the entity this frame
    ///
    /// \return virtual const sf::Vector2f
    ///
    /////////////////////////////////////////////////
    virtual const sf::Vector2f  getPosition() const;

    /////////////////////////////////////////////////
    /// \brief the center of the entity's hitbox. If hitbox is nullptr this returns the
    /// center of the entity's sprite instead
    ///
    /// \return virtual const sf::Vector2f
    ///
    /////////////////////////////////////////////////
    virtual const sf::Vector2f getCenter() const;
    /////////////////////////////////////////////////
    /// \brief the global bounding box of the entity's hitbox. If hitbox is nullptr this returns the
    /// global bounding box of the entity's sprite instead
    ///
    /// \return virtual const sf::FloatRect
    ///
    /////////////////////////////////////////////////
    virtual const sf::FloatRect getGlobalBounds() const;
    /////////////////////////////////////////////////
    /// \brief the position of the entity relative to the tilemap grid this frame
    ///
    /// \param gridSizeI const int&
    /// \return virtual const sf::Vector2i
    ///
    /////////////////////////////////////////////////
    virtual const sf::Vector2i getGridPosition(const int& gridSizeI) const;
    /////////////////////////////////////////////////
    /// \brief the global bounding box of the entity's hitbox next frame. If hitbox is nullptr this returns
    /// the global bounding box of the entity's sprite instead
    ///
    /// \param dt const float&
    /// \return virtual const sf::FloatRect
    ///
    /////////////////////////////////////////////////
    virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

    /////////////////////////////////////////////////
    /// \brief this entity's pixel distance from another [entity]
    ///
    /// \param entity const Entity&
    /// \return virtual const float
    ///
    /////////////////////////////////////////////////
    virtual const float getDistance(const Entity& entity) const;
    /////////////////////////////////////////////////
    /// \brief the entity's texture
    ///
    /// \return virtual const sf::Texture*
    ///
    /////////////////////////////////////////////////
    virtual const sf::Texture* getTexture() const;

    /////////////////////////////////////////////////
    /// \brief the entity's color (if set)
    ///
    /// \return virtual const sf::Color&
    ///
    /////////////////////////////////////////////////
    virtual const sf::Color& getColor() const;

    /////////////////////////////////////////////////
    /// \brief move the entity (x,y) pixels for dt frames
    ///
    /// \param dt const float&
    /// \param x const float&
    /// \param y const float&
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void move(const float& dt, const float& x, const float& y);

    /////////////////////////////////////////////////
    /// \brief debug move the entity in random directions for dt frames
    /// \deprecated
    /// \param dt const float&
    /// \param seed int
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void move_rand(const float& dt, int seed);

    virtual void update(const float& dt, sf::Vector2f& MousePosView) = 0;

    virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f& light, const bool render_hitbox) = 0;


    /////////////////////////////////////////////////
    /// \brief hault all movement in any direction
    ///
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void stopVelocity();

    /////////////////////////////////////////////////
    /// \brief hault all movement in the x direction
    ///
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void stopVelocityX();

    /////////////////////////////////////////////////
    /// \brief hault all movement in the y direction
    ///
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void stopVelocityY();

    /////////////////////////////////////////////////
    /// \brief attach a physics component
    ///
    /// \param maxVelocity maximum possible speed const float
    /// \param Acceleration rate of acceleration const float
    /// \param Deceleration rate of deceleration const float
    /// \return void
    ///
    /////////////////////////////////////////////////
    void addPhysicsComponent(const float maxVelocity, const float Acceleration, const float Deceleration);


    /////////////////////////////////////////////////
    /// \brief attach an animation component
    ///
    /// \param texturesheet animations sf::Texture&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void addAnimationComponent(sf::Texture& texturesheet);

    /// Generate the entity's hitbox
    /// @param sprite The sprite used to represent the entity on screen
    /// @param offset_x The X offset for the hitbox
    /// @param offset_y The Y-offset for the hitbox
    /// @param width The width of the hitbox
    /// @param height The height of the hitbox

    /////////////////////////////////////////////////
    /// \brief attach a hitbox
    ///
    /// \param sprite sf::Sprite&
    /// \param offset_x float
    /// \param offset_y float
    /// \param width float
    /// \param height float
    /// \return void
    ///
    /////////////////////////////////////////////////
    void addHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);


    void addAttributeComponent(const unsigned level);


    // Modifiers
    virtual void setRotation(float rot);

protected:
    sf::Sprite sprite;

private:
    void initVariables();
};

#endif /* Entity_hpp */
