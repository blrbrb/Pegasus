#
#include "LevelManagerMode.hpp"

LevelManagerMode::LevelManagerMode(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata, Levels* levels) : EditorModes(statedata, tilemap, editorstatedata, levels)
{
	this->initvariables(); 
}

LevelManagerMode::~LevelManagerMode()
{
}

void LevelManagerMode::updateInput(const float& dt)
{
}

void LevelManagerMode::initvariables()
{



}

void LevelManagerMode::update(const float& dt)
{
    this->updateGUI(dt); 


}

void LevelManagerMode::updateGUI(const float& dt)
{
    static char str0[128] = "Map.dat";
    static char str1[128] = "New Area";
    static char str3[128] = "   "; 
    static bool p_open = true; 
    int levels_count = 0; 

    ImGui::Begin("New Area", &p_open);

    ImGui::InputText("New Area", str1, IM_ARRAYSIZE(str1));  
    ImGui::SameLine();
    if (ImGui::Button("Append"))
    {
        this->levels->add_level(str1);
        this->levels->set_current_level(str1);
     
        this->curr_level = std::string(str1); 
    }

    levels_count = this->levels->size_total(); 
    ImGui::BeginTable("Levels", 4, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders); 

    ImGui::TableSetupColumn("Level: ");
    ImGui::TableSetupColumn("Size: ");
    ImGui::TableSetupColumn("Type: "); 
    ImGui::TableHeadersRow(); 
    ///How many header rows do we need to display all of the relevant information? 
    //1 size 
    //2 file 
    //3 type 
    
    static bool selected[10] = { false, false, false, false, false, false, false, false, false, false};
    //Display The Title of the Level
    for (int x = 0; x < levels_count; x++) 
    {
      
      
        ImGui::TableNextRow();    
        ImGui::TableNextColumn();

      


        ImGui::Selectable(this->levels->get_name(x).c_str(), &selected[x], ImGuiSelectableFlags_SpanAllColumns + ImGuiSelectableFlags_AllowDoubleClick);
        if (ImGui::IsMouseDoubleClicked && selected[x])
        {
            this->curr_level = this->levels->get_name(x).c_str();
            this->levels->set_current_level(this->levels->get_name(x)); 
            std::cout << this->curr_level << std::endl;
        }
          
        
        //ImGui::Text(this->levels->get_name(x).c_str()); 

        ImGui::TableNextColumn();
          ImGui::Text(this->levels->get_size(this->levels->get_name(x)).c_str());

        ImGui::TableNextColumn(); 
        ImGui::Text(this->levels->get_type(this->levels->get_name(x)).c_str());

    }
     
       


    ImGui::EndTable(); 
     

    if (ImGui::Button("Save")) 
    {
        this->levels->saveLevelsBatch("levels.dat"); 
    }

    ImGui::Separator(); 


   
    ImGui::Text("Current Level"); 
    for (int x = 0; x < levels_count; x++)
    {

      


       // ImGui::ListBox("listbox", x, this->levels->get_name(x), IM_ARRAYSIZE(levels_count), 4);


    } 
    ImGui::End();
	

    //Switch back to the inital GUI window 



    ImGui::Begin("Map Editor", NULL, ImGuiWindowFlags_NoMove);

    ImGui::Text("New Level"); 
    
    ImGui::End();



}

void LevelManagerMode::renderGUI(sf::RenderTarget& target)
{



}

void LevelManagerMode::render(sf::RenderTarget& target)
{
	//this function will not be called, as this entire class will work as 
	//an overload template. Essentially just to display a few organized ImGui elements. 
	//Only the update function, and the gui variables are really nessecary. 


}
