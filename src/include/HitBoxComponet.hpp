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


class HitBoxComponet
{
public:
    
    //Constructors/Destructors 
    HitBoxComponet(sf::Sprite& sprite,float offset_x, float offset_y, float width, float height);
    virtual ~HitBoxComponet(); 
    
    
    //Functions
    /**
    * @brief Maintain the position of the hitbox component over the sprite + the offset as the sprite moves across the screen 
    * 
    */
    void update();
    
    void render(sf::RenderTarget& target);
    bool intersects(const sf::FloatRect& rect);
    
    //Modifiers
    
    void setposition(const sf::Vector2f positon);
    void setposition(const float x, const float y);
    
    //Accessors
   
    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f getSize() const;
    const sf::Vector2f& getPosition() const;
    /**
     * @brief returns a constant reference to a `sf::Vector2f` object containing the pixel offset (x, y) that the hitbox is to be attached to the entity with. 
     *  
     * 
     * @return A reference to a `sf::Vector2f` object containing the `offsetX` and `offsetY` values from
     * the `HitBoxComponent` class.
     */
    const sf::Vector2f& getOffset() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity); 
    
    
    
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    
    
    
    float offsetX;
    float offsetY;
    sf::FloatRect nextpos;
    
};

#endif /* HitBoxComponet_hpp */
