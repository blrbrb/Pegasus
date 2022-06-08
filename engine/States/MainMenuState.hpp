//
//  MainMenuState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/25/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//





#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "engineFramework/States/GameState/GameState.hpp" 
#include "engineFramework/States/Editor/EditorState.hpp"
#include "Componets/GUI/GUI.hpp"
#include "engineFramework/States/SettingsState.hpp" 
#include "Componets/GUI/GraphicsSettings.hpp" 



class MainMenuState : public State
{
    public:
        MainMenuState(StateData* state_data);
        virtual ~MainMenuState();
        
    //Functions
    /// Update User Input
    /// @param dt Delta Time 
        void updateInput(const float& dt);
        void update(const float& dt);
        void updatebuttons();
           
        //Render Functions
        void renderbuttons(sf::RenderTarget& target);
    
    /// Render the Main Menu, and all associated elements
        void render(sf::RenderTarget* target = nullptr);
            
private:
        //Private initalizer Functions
        void initkeybinds();
        void initFonts();
        void initGUI();
        void resetGUI(); 
        void initbackground();
        void initvariables();
         
        //Private &variables
        sf::Font font;
        sf::RectangleShape background;
        sf::Texture backgroundTexture;
 
      
       
   
    
        std::map<std::string, GUI::Button*> buttons;
    
};

#endif /* MainMenuState_hpp */