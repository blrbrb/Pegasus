



#pragma once
#include "CharacterTab.hpp"


enum TABS { CHARACTER_TAB = 0, INVENTORY};


class PlayerGUITabs

{
public: 
	PlayerGUITabs(sf::VideoMode& vm,sf::Font& font, Player& player); 
	virtual ~PlayerGUITabs(); 

	void update(); 
	void render(sf::RenderTarget& target);   

	const bool getkeytime(); 
	const bool istabopen();   
	
	void toggletabs(const int tabID); 

private: 
	CharacterTab chab;  
	sf::VideoMode& vm; 
	sf::Font& font; 
	Player& player; 

	std::vector<Tab*> tabs;  

	//initalizer functions 
	void initTabs(); 
	void initKeyTime(); 


	//Minium amount of time in between allowed key presses 
	float keytimeMax; 
	sf::Clock keytimer; 

};

