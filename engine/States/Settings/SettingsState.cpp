//
//  SettingsState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#include "stdafx.h"
#include "SettingsState.hpp"


//Private Functions


void SettingsState::initvariables()
{
    //sthis->current_item = NULL;
    this->selection_temp = "";
    this->current_item = "";
    std::vector video_modes = sf::VideoMode::getFullscreenModes(); 
    for (auto& i : video_modes) 
    {
        //std::cout << std::to_string(i.width) + 'x' + std::to_string(i.height) << std::endl;
        this->modes[std::to_string(i.width) + 'x' + std::to_string(i.height)] = i;
    
    }

    this->music_volume = 0.f;
}

void SettingsState::initview()
{

    this->view.setSize(sf::Vector2f(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.width)); 


}


void SettingsState::initkeybinds() {
  
    std::ifstream ifs("SettingsState_Keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedkeys->at(key2);
        }
    }

    ifs.close();
    
 }

void SettingsState::initGUI() {
    
    sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    
  


    
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
    

    this->background.setTexture(&this->backgroundTexture);
    
   

    std::vector<std::string> modes_str;
    
    for (auto &i : this->modes)
    {
        std::cout << i.second.width << "x" << i.second.height << std::endl; 
        modes_str.push_back(static_cast<std::string>(std::to_string(i.second.width) + 'x' + std::to_string(i.second.height)));
        
        
    }
   

    
}

void SettingsState::resetGUI()
{
 
}




void SettingsState::initFonts()
{
    
    
    if (!this->font.loadFromFile("Resources/Assets/Fonts/PressStart2P.ttf"))
    {
        LOG(WARNING) << "unable to load default font"; 
        LOG(FATAL) << "throwing runtime exception on line 104";
        throw std::runtime_error("ERROR CODE 05: SettingsState::initFonts COULD NOT LOAD FONT FROM FILE");
        
    }

    
}


SettingsState::SettingsState(StateData* state_data) :  State(state_data)
{
    try
    {
        this->initvariables();
        this->initFonts();
        this->initkeybinds();
        this->initGUI();
      
    }
    
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        
    }
}

SettingsState::~SettingsState()
{
    auto it2 = dropdownlists.begin();
       for (it2 = dropdownlists.begin(); it2 != this->dropdownlists.end(); ++it2)
      
       {
           delete it2->second;
           
       }
}



//Functions 
void SettingsState::update(const float& dt) {
    
    this->updateView();
    this->updateInput(dt);
    this->updateMousePosition();
    this->updateGUI(dt);
    
}

void SettingsState::updateInput(const float& dt)
{

    
    
}

//Render Functions

void SettingsState::render(sf::RenderTarget* target) {
    
   if (!target)
       target = this->window;

   target->setView(this->view);
  // target->draw(this->background);
   
    this->renderGUI(*target);

}




void SettingsState::renderGUI(sf::RenderTarget& target)
{
    
   
}

void SettingsState::updateevents()
{






}




void SettingsState::updateGUI(const float& dt) {
    
    //GUI element functionality
    static char str0[128] = "Map.dat";
    static char str1[128] = "New Area";
    static int switchTabs;
    static bool p_open = NULL;
    static bool style_titlebar = false;
    static bool style_fullscreen = false;
    static bool vertical_sync = false;
    this->open = true; 
   //bool is_selected = false; 
     

    ImGui::SetNextWindowPos(ImVec2(0, 0));

    ImGui::SetNextWindowSize(ImVec2(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height));
    ImGui::Begin("Settings", &this->open);
        
   
    ImGui::Text("Resolution"); 
    if (ImGui::BeginCombo("##Resolution", this->current_item))
    {
        for (auto & n: this->modes)
        {
          
              
            bool is_selected = (this->current_item == n.first.c_str());
            if (ImGui::Selectable(n.first.c_str(), is_selected))
                this->selection_temp = n.first;
                this->current_item = this->selection_temp.c_str();
            if(is_selected)
                     ImGui::SetItemDefaultFocus();
           
        }
        ImGui::EndCombo();
    
    }

    

    if (ImGui::CollapsingHeader("Window options"))
    {
        if (ImGui::BeginTable("split", 3))
        {
            ImGui::SameLine(); 
            ImGui::TableNextColumn(); ImGui::Checkbox("Bordered", &style_titlebar);
            ImGui::TableNextColumn(); ImGui::Checkbox("Fullscreen", &this->state_data->gfxsettings->fullscreen);
            ImGui::TableNextColumn(); ImGui::Checkbox("vertical sync", &vertical_sync);
            ImGui::EndTable();
        }
        
    }
    

    ImGui::Separator(); 
    ImGui::SliderFloat("Music Volume", &this->music_volume, 0.0f, 100.0f, "ratio = %.3");
    this->state_data->music->set_volume(this->music_volume); 

    

       
        //ImGui::SetItemDefaultFocus();
       
        if (ImGui::Button("Apply Changes") && this->selection_temp != "")
        {
            std::cout << this->current_item << std::endl; 
            this->state_data->gfxsettings->resolution = this->modes[this->selection_temp];
            
            ///Changes are stored as static bool within the update function. Changed values are passed on to the graphics settings object here.
            ///changes are applied. The graphics settings are saved, and then the window is recreated. 
         
            this->state_data->gfxsettings->vsync = &vertical_sync;
            this->state_data->gfxsettings->savetofile("Init/Window.cfg");
            if (vertical_sync)
            {

            }

            if (this->state_data->gfxsettings->fullscreen) 
            {
                LOG(INFO) << "creating new render window with resolution " << this->state_data->gfxsettings->resolution.width << "x" << this->state_data->gfxsettings->resolution.height; 
                this->window->create(this->state_data->gfxsettings->resolution, this->state_data->gfxsettings->title, sf::Style::Fullscreen);
                this->window->setIcon(icon.width, icon.height, icon.data); 
            }
            else 
            {
                LOG(INFO) << "creating new render window with resolution " << this->state_data->gfxsettings->resolution.width << "x" << this->state_data->gfxsettings->resolution.height;
                this->window->create(this->state_data->gfxsettings->resolution, this->state_data->gfxsettings->title);
                this->window->setIcon(icon.width, icon.height, icon.data);
            }

        }


        if(ImGui::Button("Exit"))
        {
           
            this->endstate();
            //LOG(INFO) << "Main"
        
        }
    

    ImGui::End();

    
}

void SettingsState::updateView()
{
   // this->view.setSize(sf::Vector2f(GUI::calcCharSize(this->state_data->gfxsettings->resolution, 2), GUI::calcCharSize(this->state_data->gfxsettings->resolution, 2)));
}


