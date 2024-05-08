#ifndef ShaderEditorMode_h
#define ShaderEditorMode_h
#include "EditorModes.hpp" 

class ShaderEditorMode : public EditorModes 
{
public: 

	ShaderEditorMode(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata);
	virtual ~ShaderEditorMode();







private: 


    void updateInput(const float& dt);
   void update(const float& dt);
   void updateGUI(const float& dt);
   void renderGUI(sf::RenderTarget& target);
  
     void render(sf::RenderTarget& target);
     ImVec4 selection_color_ImGUi; 
    bool write_edited_shader(); 

    sf::Color selection_color;
    sf::Color selection_normal; 
    sf::Color selection_vector;
    
    sf::Vector2f selection_vec2; 
    sf::Vector3f selection_vec3;

    sf::Shader core_shader;



};

#endif 