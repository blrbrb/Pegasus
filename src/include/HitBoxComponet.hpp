//
//  HitBoxComponet.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/1/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef HitBoxComponet_hpp
#define HitBoxComponet_hpp
#include <SFML/Graphics.hpp>

class HitBoxComponet {
public:

    /////////////////////////////////////////////////
    /// \brief construct the hitbox
    ///
    /// \param sprite sf::Sprite&
    /// \param offset_x float
    /// \param offset_y float
    /// \param width float
    /// \param height float
    ///
    /////////////////////////////////////////////////
    HitBoxComponet(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    virtual ~HitBoxComponet();


    void update();

    void render(sf::RenderTarget& target);
    /////////////////////////////////////////////////
    /// \brief does the hitbox intersect with [rect]
    ///
    /// \param rect const sf::FloatRect&
    /// \return bool
    ///
    /////////////////////////////////////////////////
    bool intersects(const sf::FloatRect& rect);



    /////////////////////////////////////////////////
    /// \brief set the pixel position of the hitbox
    ///
    /// \param positon const sf::Vector2f
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setposition(const sf::Vector2f positon);

    /////////////////////////////////////////////////
    /// \brief set the pixel screen position of the hitbox
    ///
    /// \param x const float
    /// \param y const float
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setposition(const float x, const float y);



    /////////////////////////////////////////////////
    /// \brief the global bounding box
    ///
    /// \return const sf::FloatRect
    ///
    /////////////////////////////////////////////////
    const sf::FloatRect getGlobalBounds() const;
    /////////////////////////////////////////////////
    /// \brief pixel size
    ///
    /// \return const sf::Vector2f
    ///
    /////////////////////////////////////////////////
    const sf::Vector2f getSize() const;
    /////////////////////////////////////////////////
    /// \brief pixel screen position for the current frame
    ///
    /// \return const sf::Vector2f
    ///
    /////////////////////////////////////////////////
    const sf::Vector2f getPosition() const;

    /////////////////////////////////////////////////
    /// \brief the offset of the hitbox over the entity
    ///
    /// \return const sf::Vector2f&
    ///
    /////////////////////////////////////////////////
    const sf::Vector2f& getOffset() const;
    /////////////////////////////////////////////////
    /// \brief the pixel screen position next frame
    ///
    /// \param velocity const sf::Vector2f&
    /// \return const sf::FloatRect&
    ///
    /////////////////////////////////////////////////
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;

    float offsetX;
    float offsetY;
    sf::FloatRect nextpos;
};

#endif /* HitBoxComponet_hpp */
