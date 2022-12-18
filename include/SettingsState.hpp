//
//  SettingsState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef SettingsState_hpp
#define SettingsState_hpp
#include "State.hpp"
#include "GUI.hpp"

/// Class with methods that allow the user to change basic settings 
class SettingsState : public State
{
private:
    
        //Functions
         void initkeybinds();
         void initFonts();
         void initGUI();
         void resetGUI();
         void initvariables();
         void initview(); 
    
       //Variables
    sf::Font font;
    sf::RectangleShape background;
    sf::View view; 
    sf::Texture backgroundTexture;
    sf::Text option_text;
    std::map<std::string, GUI::Button*> buttons;
    std::map<std::string, GUI::DropDownList*> dropdownlists;
    std::map<std::string, sf::VideoMode> modes;
    
    //Gui variables 
    const char* items[120];
    const char* current_item; 
    std::string selection_temp; 
    //const char* current_item;
    

    
public:
    
    SettingsState(StateData* state_data);
    virtual ~SettingsState();
    
    //Accessors
    
    
    //Functions
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void updateView(); 
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void updateevents();
    void render(sf::RenderTarget* target = nullptr);
    
};

#endif /* SettingsState_hpp */
