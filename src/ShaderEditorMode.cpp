#
#include "include/ShaderEditorMode.h"

ShaderEditorMode::ShaderEditorMode(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata) : EditorModes(statedata, tilemap, editorstatedata)
{ 
   

}

ShaderEditorMode::~ShaderEditorMode()
{
}

void ShaderEditorMode::updateInput(const float& dt)
{
}

void ShaderEditorMode::update(const float& dt)
{
    this->updateGUI(dt); 

}

void ShaderEditorMode::updateGUI(const float& dt)
{ 
  
    static ImVec4 saved_palette[32] = {};
    

    for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
    {
        ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f,
            saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
        saved_palette[n].w = 1.0f; // Alpha
    }
   // saved_palette_init = false;



    static int r = 0;
    static int g = 0;
    static int b = 0;
    static int a = 0; 

    ImGui::Begin("Map Editor"); 


    ImGui::Text("Light Color"); 

    //ImGui::ColorPicker4("Light Color", &this->editorstatedata->selection_color.x);
   
   
  
    ImGui::End(); 
   // ImGui::SliderInt()
    //this->selection_color_ImGUi = ImVec4(this->editorstatedata->selection_color); 
   // this->selection_color = this->editorstatedata->selection_color; 
    this->editorstatedata->shader->setUniform("ambientData", sf::Glsl::Vec4(this->selection_color)); 
 //   this->core_shader.setParameter("ambientData", this->selection_color); 
}

void ShaderEditorMode::renderGUI(sf::RenderTarget& target)
{


}



void ShaderEditorMode::render(sf::RenderTarget& target)
{


}

bool ShaderEditorMode::write_edited_shader()
{
    return false;
}
