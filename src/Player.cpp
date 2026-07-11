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
    : Entity(textureSheet)
{
    this->mirrorAnimation(textureSheet);
    this->initAnimations();
    this->addHitboxComponent(this->sprite, 0, 0, 39.f, 57.f);
    this->addPhysicsComponent(100.f, 20000.f, 200.f);

    this->addAttributeComponent(1);
    this->setPosition(x, y);

}

Player::~Player() = default;

Player::Player(const std::string& save_file, sf::Texture& textureSheet)
    : Entity(textureSheet)
{

    this->addAnimationComponent(textureSheet);
    this->loadFromFile(save_file);

}

// initalizer functions

void Player::initComponents()
{

}


void Player::initVariables()
{

}

void Player::initAnimations()
{

    //this->animationcomponet->add_animation("IDLE_BLINKING", 4.f, 0, 2, 15, 2, 62, 74); // first row, second* sprite across *iterator starts from unsigned 0
    //this->animationcomponet->add_animation("WALK_RIGHT", 5.f, 1, 1, 15, 1, 62, 74);
   // this->animationcomponet->add_animation("WALK_LEFT", 5.f, 0, 0, 15, 0, 62, 74);
    //this->animationcomponet->add_animation("WALK_DOWN", 5.f, 0, 0, 15, 0, 62, 74);

      this->animationcomponet->add_animation("WALK_LEFT", 5.f, 0, 0, 15, 0, 39, 57);
       this->animationcomponet->add_animation("WALK_RIGHT", 5.f, 0, 1, 15, 0, 39, 57);
    //this->animationcomponet->add_animation("WALK_UP", 5.f, 0, 3, 2, 3, 62, 74);


}
// Importing a ponytown character will work by exporting the trotting animation to a 1x png image. In order to create animations for
// a character walking in both directions, we must resize the sprite's texture and paste the mirrored walking animation
void Player::mirrorAnimation(sf::Texture& texture)
{
  // 2. Convert the texture to an sf::Image for pixel manipulation
  sf::Image image = texture.copyToImage();

  // 3. Get original dimensions and calculate the new height
  sf::Vector2u origSize = image.getSize();
  sf::Vector2u newSize = { origSize.x, origSize.y * 2 };

  // 4. Create a new, larger image
  sf::Image combinedImage({newSize.x, newSize.y});

  // 5. Paste the original texture at the top
  combinedImage.copy(image, {0, 0});

  // 6. Copy and mirror the texture to the bottom half
  for (unsigned int y = 0; y < origSize.y; ++y) {
    for (unsigned int x = 0; x < origSize.x; ++x) {
      // Read from the top, mirror horizontally, write to the bottom
      sf::Color pixel = image.getPixel({ x, y });
      combinedImage.setPixel({ origSize.x - 1 - x, origSize.y + y }, pixel);
    }
  }

  if(!combinedImage.saveToFile("character-test.png"))
  {
    std::cout << "error saving character animations" << std::endl;
  }
  // 7. Create a new texture and load the modified image into it

  if (!texture.loadFromImage(combinedImage)) {
    std::cerr << "error creating mirrored walking animation" << std::endl;
  }

  //this->sprite.setTexture(finalTexture);
  this->addAnimationComponent(texture);
}
void Player::updateAnimation(const float& dt)
{

    if (this->physicsComponents->getStatus(MOVING_RIGHT)) {
        this->animationcomponet->play("WALK_RIGHT", dt);

    }

    else if (this->physicsComponents->getStatus(MOVING_LEFT)) {
        this->animationcomponet->play("WALK_LEFT", dt);


    }





}

void Player::update(const float& dt, sf::Vector2f& MousePosView)
{
    this->attributes->update();
    this->physicsComponents->update(dt);
    this->hitbox->update();
    this->updateAnimation(dt);


}

void Player::updateLighting(const float& dt)
{
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f& light, const bool render_hitbox)
{



    if (shader) {

        shader->setUniform("lightPos", light);
        shader->setUniform("hasTexture", true);

        target.draw(this->sprite, shader);

    }

    else if (render_hitbox) {
        this->hitbox->render(target);
    }
    else
        target.draw(this->sprite);
}

StatusComponet* Player::getStatusComponent()
{
    return this->attributes.get();
}

const std::string& Player::toString() const
{
    std::stringstream ss;


    return ss.str();
}

void Player::saveToFile(const std::string& filename)
{

}

void Player::loadFromFile(const std::string& filename)
{

}
