



#ifndef PLAYERGUITABS_HPP_
#define PLAYERGUITABS_HPP_




#include "CharacterTab.hpp"


enum TABS { CHARACTER_TAB = 0, INVENTORY};


class PlayerGUITabs

{
public: 
	PlayerGUITabs(sf::VideoMode& vm,sf::Font& font, Player& player); 
	virtual ~PlayerGUITabs(); 

	void update(); 
	void render(sf::RenderTarget& target);   

	bool getkeytime();
	bool istabopen();
	
	void toggletabs(int tabID);

private: 
	CharacterTab chab;  
	sf::VideoMode& vm; 
	sf::Font& font; 
	Player& player; 

	std::vector<Tab*> tabs;  

	//initializer functions
	void initTabs(); 
	void initKeyTime(); 


	//Minium amount of time in between allowed key presses 
	float keytimeMax;
	sf::Clock keytimer; 

};

#endif // PLAYERGUITABS_HPP_