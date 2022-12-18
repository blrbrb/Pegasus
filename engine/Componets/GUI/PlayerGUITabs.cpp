#include "stdafx.h"
#include "PlayerGUITabs.hpp"

PlayerGUITabs::PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player) :vm(vm), font(font), player(player),
chab(vm, font, player)
{
	this->initTabs(); 
	this->initKeyTime(); 
  
}

PlayerGUITabs::~PlayerGUITabs()
{


} 




void PlayerGUITabs::initTabs()
{
	this->tabs.push_back(new CharacterTab(vm, font, player));
}

void PlayerGUITabs::initKeyTime()
{ 
	this->keytimeMax = 0.3f; 
	this->keytimer.restart(); 

}

void PlayerGUITabs::update()
{ 
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->getOpen())
			this->tabs[i]->update();
	}

}

void PlayerGUITabs::render(sf::RenderTarget& target)
{
	//this->chab.render(target);   

	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->getOpen())
			this->tabs[i]->render(target);
	}
}

const bool PlayerGUITabs::getkeytime()
{ 

	if (this->keytimer.getElapsedTime().asSeconds() >= this->keytimeMax)
	{
		this->keytimer.restart(); 
		return true; 
	
	}


	return false;
}

void PlayerGUITabs::toggletabs(const int tabID)
{
	if (tabID >= 0 || tabID < this->tabs.size()) 
		this->tabs[tabID]->toggle();
	
		
}

const bool PlayerGUITabs::istabopen()
{ 
	bool open = false; 
	for (size_t i = 0; i < this->tabs.size() && !open; i++)
	{
		if (this->tabs[i]->getOpen())
			open = true; 

	}
	return open; 
}
