
#pragma once

#include "Tab.hpp"
class CharacterTab:public Tab
{
public: 
	CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player); 
	virtual ~CharacterTab(); 

	void update(); 
	void render(sf::RenderTarget& target); 
private: 
	sf::RectangleShape characterTabBack; 
	sf::Text CharacterInfo; 


};

 