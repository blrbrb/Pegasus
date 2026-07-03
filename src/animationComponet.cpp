//
//  AnimationComponet.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 1/30/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#
#include "include/AnimationComponet.hpp"

AnimationComponet::AnimationComponet(sf::Sprite& sprite, sf::Texture& texturesheet)
    : sprite(sprite)
    , texturesheet(texturesheet)
    , lastAnimation(NULL)
    , priorityAnimation(NULL)
{
}

AnimationComponet::~AnimationComponet()
{

    for (auto& i : this->animations) {
        delete i.second;
    }
}

//*Functions*
void AnimationComponet::add_animation(const std::string& key, float animationtimer, int start_x, int start_y, int end_x, int end_y, int width, int height)
{
    this->animations[key] = new Animation(this->texturesheet, this->sprite, animationtimer, start_x, start_y, end_x, end_y, width, height);
    // this->Animations.insert(animation(key, new Animation(this->texturesheet, this->sprite, animationtimer, start_x, start_y, end_x, end_y, width, height)));
    // this->names.push_back(this->Animations.right.at(this->animations[key]));
}

const bool& AnimationComponet::play(const std::string& key, const float& dt, const bool priority)
{

    if (this->priorityAnimation) //*if a priority animation exists, play it first
    {

        if (this->priorityAnimation == this->animations[key]) {

            if (this->lastAnimation != this->animations[key]) {

                if (this->lastAnimation == nullptr)
                    this->lastAnimation = this->animations[key];

                else {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }
            }
            // if the priority animation is finished
            if (this->animations[key]->play(dt)) {
                this->priorityAnimation = nullptr;
            }
        }

    }

    else // Play an animation if no other priority animations exist
    {
        if (priority) {
            this->priorityAnimation = this->animations[key];
        }

        if (this->lastAnimation != this->animations[key]) {

            if (this->lastAnimation == nullptr)
                this->lastAnimation = this->animations[key];

            else {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }
        }

        this->animations[key]->play(dt);
    }
    return this->animations[key]->getDone();
}

const bool& AnimationComponet::play(const std::string& key, const float& dt, const float& speed, const float& speed_max, const bool priority)
{
    if (this->priorityAnimation) //*if a priority animation exists, play it first
    {

        if (this->priorityAnimation == this->animations[key]) {

            if (this->lastAnimation != this->animations[key]) {

                if (this->lastAnimation == nullptr) {
                    this->lastAnimation = this->animations[key];
                } else {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }
            }

            if (this->animations[key]->play(dt, std::abs(speed / speed_max))) {
                this->priorityAnimation = nullptr;
            }
        }
    }

    else {
        // if there is a priority animation, set true
        if (priority) {
            this->priorityAnimation = this->animations[key];
        }

        if (this->lastAnimation != this->animations[key]) {
            if (this->lastAnimation == nullptr)
                this->lastAnimation = this->animations[key];

            else {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }
        }

        this->animations[key]->play(dt, std::abs(speed / speed_max));
    }
    return this->animations[key]->getDone();
}

//*End Functions*

//*Accessors*
const bool& AnimationComponet::getDone(const std::string& key)
{
    return this->animations[key]->getDone();
}

const std::string& AnimationComponet::getName(int index)
{
    if (this->names.empty())
        return "empty";
    else
        return names.at(index);
}

// const int& AnimationComponet::getWidth(const std::string& key)
//{
// return this->animations[key]->getAnimationWidth();
//}

// const int& AnimationComponet::getHeight(const std::string& key)
//{
//   return this->animations[key]->getAnimationHeight();
//}

// const int& AnimationComponet::getStartRectLeft(const std::string& key)
//{
//   return this->animations[key]->getStartRectLeft();
//}

// const int& AnimationComponet::getStartRectTop(const std::string& key)
//{
//   return this->animations[key]->getStartRectTop();
//}
// const int& AnimationComponet::getStartRectWidth(const std::string& key)
//{
//  return this->animations[key]->getStartRectWidth();
//}

// const int& AnimationComponet::getStartRectHeight(const std::string& key)
//{
//   return this->animations[key]->getStartRectHeight();
//}

// const float& AnimationComponet::getTimer(const std::string& key)
//{
//   return this->animations[key]->getTimer();/
//}

// const int& AnimationComponet::getEndRectLeft(const std::string& key)
//{
//   return this->animations[key]->getEndRectLeft();
//}

// const int& AnimationComponet::getEndRectTop(const std::string& key)
//{
//    return this->animations[key]->getEndRectTop();
//}

// const int& AnimationComponet::getEndRectWidth(const std::string& key)
//{
//    return this->animations[key]->getEndRectWidth();
//}

// const int& AnimationComponet::getEndRectHeight(const std::string& key)
//{
//    return this->animations[key]->getEndRectHeight();
//}

// const int& AnimationComponet::getSize() const
//{
// return static_cast<int>(this->Animations.left.size());
//}

// const int& AnimationComponet::getStartX(const std::string& key) const
//{
//  return this->animations[key]->getStartX();
//}

// const int& AnimationComponet::getStartY(const std::string& key) const
//{
//  return this->animations[key]->getStartY();
//}

// const int& AnimationComponet::getEndX(const std::string& key) const
//{
// return this->animations[key]->getEndX();
//}

// const int& AnimationComponet::getEndY(const std::string& key) const
//{
// return this->animations[key]->getEndY();
//}
