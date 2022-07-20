#include "stdafx.h"
#include "PlayerGUITabs.hpp"



PlayerGUITabs::PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player) :vm(vm), font(font), player(player),
chab(vm, font, player)
{

  
}

PlayerGUITabs::~PlayerGUITabs()
{
}

void PlayerGUITabs::update()
{
}

void PlayerGUITabs::render(sf::RenderTarget* target)
{
	this->chab.render(target);
}