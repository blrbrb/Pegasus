#include "stdafx.h"
#include "PlayerGUITabs.h"



PlayerGUITabs::PlayerGUITabs(sf::VideoMode& vm, sf::Font& font) :vm(vm), font(font)
{

    this->initcharacterinfo(); 
}

PlayerGUITabs::~PlayerGUITabs()
{
}

void PlayerGUITabs::initcharacterinfo()
{
    this->info_tag_interior.setFillColor(sf::Color(50, 50, 50, 180));
    this->info_tag_interior.setSize(sf::Vector2f(GUI::pixelpercentX(30.f, this->vm), static_cast<float>(this->vm.height)));

    this->character_info.setFont(this->font);
    this->character_info.setCharacterSize(GUI::calcCharSize(this->vm, 20.f));
    this->character_info.setFillColor(sf::Color::White);
    this->character_info.setPosition(this->info_tag_interior.getPosition().x + GUI::pixelpercentX(1, this->vm), this->info_tag_interior.getPosition().y + 20.f);

}