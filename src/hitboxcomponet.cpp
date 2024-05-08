#include "include/HitBoxComponet.hpp"

HitBoxComponet::HitBoxComponet(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height) : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{

    this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);

    this->hitbox.setSize(sf::Vector2f(width, height));

    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Green);

    this->nextpos.left = 0.f;

    this->nextpos.top = 0.f;
    this->nextpos.width = width;
    this->nextpos.height = height;
}

HitBoxComponet::~HitBoxComponet()
{
}

void HitBoxComponet::update()
{

    this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

/**
 *  render the hitbox on a specified SFML render
 * target.
 * 
 * @param target 
 */
void HitBoxComponet::render(sf::RenderTarget &target)
{

    target.draw(this->hitbox);
}

/**
 * The function checks if the hitbox of a component intersects with a given rectangle.
 * 
 * @param rect The `rect` parameter is a `sf::FloatRect` object representing a rectangular area in a 2D
 * space.
 * 
 * @return The function `intersects` is returning a boolean value indicating whether the hitbox
 * associated with the `HitBoxComponent` object intersects with the provided `sf::FloatRect` rectangle.
 */
bool HitBoxComponet::intersects(const sf::FloatRect &rect)
{

    return this->hitbox.getGlobalBounds().intersects(rect);
}

/**
 * The function `setPosition` in the `HitBoxComponent` class sets the position of the hitbox and sprite
 * based on the given position and offsets.
 * 
 * @param positon The `positon` parameter is a `sf::Vector2f` object representing the new position to
 * set for the `HitBoxComponent`.
 */
void HitBoxComponet::setposition(const sf::Vector2f positon)
{
    this->hitbox.setPosition(positon);
    this->sprite.setPosition(positon.x - this->offsetX, positon.y - this->offsetY);
}

/**
 * @brief sets the position of the hitbox
 * 
 * @param x The `x` pixel-coordinate  to set the
 * HitBoxComponent and its associated sprite. 
 * @param y The `y` pixel-cordinate to set the hitbox and sprite.
 * 
 * @note (the `x` and `y' cordinates represent the width and height of the window respectively.)
 */
void HitBoxComponet::setposition(const float x, const float y)
{
    this->hitbox.setPosition(x, y);
    this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

/**
 * @brief get's  global bounding rectangle of the hitbox
 * 
 * @return An sf::FloatRect() representing the global bounds of the hitbox
 */
const sf::FloatRect HitBoxComponet::getGlobalBounds() const
{

    return this->hitbox.getGlobalBounds();
}

/**
 * @brief get's the size of the hitbox component.
 * 
 * @return An sf::Vector2f representing the size of the hitbox.
 */
const sf::Vector2f HitBoxComponet::getSize() const
{
    return this->hitbox.getSize();
}

/**
 * @brief calculates the next position of the hitbox based on a given velocity
 * 
 * @return  a constant reference to a `sf::FloatRect`
 * object, which represents the next position of the hitbox after applying the given velocity.
 */
const sf::FloatRect &HitBoxComponet::getNextPosition(const sf::Vector2f &velocity)
{

    this->nextpos.left = this->hitbox.getPosition().x + velocity.x;
    this->nextpos.top = this->hitbox.getPosition().y + velocity.y;

    return this->nextpos;
}

/**
 * The function `getPosition` returns the position of the hitbox in a constant reference to a
 * `sf::Vector2f`.
 *
 * @return A constant reference to a `sf::Vector2f` representing the position of the hitbox component.
 */
const sf::Vector2f &HitBoxComponet::getPosition() const
{
    return this->hitbox.getPosition();
}

const sf::Vector2f &HitBoxComponet::getOffset() const
{
    return sf::Vector2f(this->offsetX, this->offsetY);
}
