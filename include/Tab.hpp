#pragma once

#include "Player.hpp"
#include "GUI.hpp" 

class Tab
{
public: 
	Tab(sf::VideoMode& vm, sf::Font& font, Player& player, bool hidden); 
	virtual ~Tab(); 

	virtual void update() = 0; 
	virtual void render(sf::RenderTarget* target) = 0; 

//functions
	void hide(); 
	void show(); 

protected: 

	Player& player;
	sf::VideoMode& vm;
	sf::Font& font;
	bool hidden; 
};

