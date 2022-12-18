#ifndef CharacterEdtiorState_h
#define CharacterEditorState_h
#include "Entity.hpp"
#include "Player.hpp"
#include "State.hpp"

class Entity; 
class Player; 

class CharacterEditorState : public State
{


public: 
	CharacterEditorState(Entity* entity, Player* player); 
	virtual ~CharacterEditorState(); 


	// Inherited via State
	virtual void updateInput(const float& dt) override;

	virtual void update(const float& dt) override;

	virtual void render(sf::RenderTarget* target); 

	virtual void initkeybinds() override;


private: 

	Player& player; 
	Entity& entity; 

	sf::Texture demotexture;
	sf::Sprite characterDemo;            


};

#endif // !CharacterEdtior_h