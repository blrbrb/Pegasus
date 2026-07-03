#
#include "include/PlayerGUITabs.hpp"

PlayerGUITabs::PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player) :chab(vm, font, player), vm(vm), font(font),
player(player)
{
	this->initTabs(); 
	this->initKeyTime(); 
  
}

PlayerGUITabs::~PlayerGUITabs()
= default;




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
	for (auto & tab : this->tabs)
	{
		if (tab->getOpen())
			tab->update();
	}

}

void PlayerGUITabs::render(sf::RenderTarget& target)
{
	//this->chab.render(target);

	//for (auto & tab : this->tabs)
	//{
		//if (tab->getOpen())
			//tab->render(target);
	//}
}

bool PlayerGUITabs::getkeytime()
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

bool PlayerGUITabs::istabopen()
{ 
	bool open = false; 
	for (size_t i = 0; i < this->tabs.size() && !open; i++)
	{
		if (this->tabs[i]->getOpen())
			open = true; 

	}
	return open; 
}
