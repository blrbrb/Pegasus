



#pragma once
#include "CharacterTab.hpp"

class PlayerGUITabs

{
public: 
	PlayerGUITabs(sf::VideoMode& vm,sf::Font& font, Player& player); 
	virtual ~PlayerGUITabs(); 

	void update(); 
	void render(sf::RenderTarget* target); 

private: 
	CharacterTab chab; 
	sf::VideoMode& vm; 
	sf::Font& font; 
	Player& player; 
	
};

