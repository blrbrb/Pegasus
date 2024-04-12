#
#include "CharacterEditorState.h"

CharacterEditorState::CharacterEditorState(Entity* entity, Player* player) : State(state_data), player(*player), entity(*entity)
{ 

}

CharacterEditorState::~CharacterEditorState()
{
}

void CharacterEditorState::updateInput(const float& dt)
{
}

void CharacterEditorState::update(const float& dt)
{
	static bool p_open = true; 
	ImGui::Begin("Character Editor",&p_open, ImGuiWindowFlags_NoMove);


}

void CharacterEditorState::render(sf::RenderTarget* target)
{
}

void CharacterEditorState::initkeybinds()
{
}
