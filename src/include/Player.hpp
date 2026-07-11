//
//  Player.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/28/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Player_hpp
#define Player_hpp

#include "Entity.hpp"

class Entity;

class Player : public Entity {
private:
    void initVariables();
    void initComponents();
    void initAnimations();

    void initInventory();

public:

    /////////////////////////////////////////////////
    /// \brief player
    ///
    /// \param x float
    /// \param y float
    /// \param textureSheet sf::Texture&
    ///
    /////////////////////////////////////////////////
    Player(float x, float y, sf::Texture& textureSheet);

    virtual ~Player();


    /////////////////////////////////////////////////
    /// \brief read saved player config from disk (unimplemented)
    /// \overload
    /// \param save_file const std::string&
    /// \param textureSheet sf::Texture&
    ///
    /////////////////////////////////////////////////
    Player(const std::string& save_file, sf::Texture& textureSheet);


    /////////////////////////////////////////////////
    /// \brief the player's status component
    ///
    ///
    /// \return StatusComponet*
    ///
    /////////////////////////////////////////////////
    StatusComponet* getStatusComponent();

    /////////////////////////////////////////////////
    /// \brief stream player config in plaintext (unimplemented)
    /// \return const std::string&
    ///
    /////////////////////////////////////////////////
    const std::string& toString() const;

    /////////////////////////////////////////////////
    /// \brief write player config to disk (unimplemented)
    ///
    /// \param filename const std::string&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void saveToFile(const std::string& filename);

    /////////////////////////////////////////////////
    /// \brief read player config from disk (unimplemented)
    ///
    /// \param filename const std::string&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void loadFromFile(const std::string& filename);


    /////////////////////////////////////////////////
    /// \brief final update
    ///
    /// \param dt const float&
    /// \param MousePosView sf::Vector2f&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void update(const float& dt, sf::Vector2f& MousePosView);

    void updateLighting(const float& dt);
    void mirrorAnimation(sf::Texture& texture);

    /////////////////////////////////////////////////
    /// \brief update the player's animations
    ///
    /// \param dt const float&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void updateAnimation(const float& dt);

    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f& light = sf::Vector2f(), const bool render_hitbox = false);
};

#endif /* Player_hpp */
