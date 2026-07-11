
//  PauseMenu.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#
#include "include/PauseMenu.hpp"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
    : font(font)
{
    this->adjusted_volume = 100.f;
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.size.x), static_cast<float>(vm.size.y)));
    this->background.setFillColor(sf::Color(20, 20, 20, 100));
    this->container.setSize(sf::Vector2f(static_cast<float>(vm.size.x) / 0.5f, static_cast<float>(vm.size.y) - GUI::pixelpercentY(9.3, vm)));
    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(sf::Vector2f(static_cast<float>(vm.size.x / 2.f) - this->container.getSize().x / 2.f, 0.f));

    // init MenuText
    // TO DO: Add pointer memory de-allocation to the class deconstructor. Since SFML 3.0 breaking changes all sf::Text instances need to be initalized as pointers
    this->menutext = new sf::Text(font, "PAUSED");
    this->menutext->setFillColor(sf::Color(255, 255, 255, 200));
    this->menutext->setCharacterSize(GUI::calcCharSize(vm));
    this->menutext->setPosition(sf::Vector2f(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menutext->getGlobalBounds().size.x / 2.f,
        this->container.getPosition().y + GUI::pixelpercentY(4, vm)));

    // test

    //this->pillbutt = new GUI::RoundedRectangleShape(sf::Vector2f(200.f, 200.f), 45.f, 20);
    //this->pillbutt->setPosition(sf::Vector2f(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menutext->getGlobalBounds().size.x / 2.f,
       // this->container.getPosition().y + GUI::pixelpercentY(4, vm);
}

PauseMenu::~PauseMenu()
{
    auto it = buttons.begin();
    for (it = buttons.begin(); it != this->buttons.end(); ++it)

    {
        delete it->second;
    }
}

void PauseMenu::update(const sf::Vector2i& MousePos)
{
    for (auto& i : this->buttons) {
        i.second->update(MousePos);
    }
}

void PauseMenu::render(sf::RenderTarget& target)
{

    target.draw(background);
    target.draw(container);

    for (auto& i : this->buttons) {
        i.second->render(target);
    }

    target.draw(*this->menutext);

    // GUI Pill Button render test

}

std::map<std::string, GUI::Button*>& PauseMenu::getButtons()
{

    return this->buttons;
}

void PauseMenu::addbutton(const std::string key, const unsigned charSize, const std::string text, const float width, const float height, const float y)
{
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new GUI::Button(width, height, x, y, &this->font, text, charSize);
}
const bool PauseMenu::isButtonPressed(const std::string& key)
{
    return this->buttons[key]->isPressed();
}
