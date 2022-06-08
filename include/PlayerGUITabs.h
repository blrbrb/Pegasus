#include "GUI.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Inventory.hpp"


class PlayerGUITabs
{
public: 
	PlayerGUITabs(sf::VideoMode& vm,sf::Font& font); 
	virtual ~PlayerGUITabs(); 

private: 

	sf::RectangleShape info_tag_interior;
	sf::Text character_info;
	sf::VideoMode& vm;
	sf::Font& font;

	void initcharacterinfo(); 
};

