//
//  EditorState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/1/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#ifndef EditorState_hpp
#define EditorState_hpp
#include <filesystem>
#include "State.hpp"
#include "GUI.hpp"
#include "PauseMenu.hpp"
#include "TileMap.hpp"
#include "EditorModes.hpp"
#include "DefaultMode.hpp" 
#include "EnemyEditorMode.hpp" 
#include "EnviornmentalMode.hpp" 
#include "ShaderEditorMode.h"

#include "imgui.h"
#include "imgui-SFML.h"

class State;
class EditorModes;
class PauseMenu;
class TileMap;
class EnemyEditorMode;
class DefaultMode;
class PauseMenu;
class EditorStateData; 
class ShaderEditorMode; 


enum EDITOR_MODES {DEFAULT_MODE = 0, ENEMY, ENV, LEVEL, SHADER};


class EditorState : public State
{
    public:
        
        //Constructor and Destructor
        EditorState(StateData* state_data);
    
        virtual ~EditorState();

    
        //Update Functions
        void updateInput(const float& dt);
        void updateEditorinput(const float& dt);
        void update(const float& dt);
        void updatebuttons();
        void updateevents();
        void updateGUI(const float& dt);
        void updateModes(const float& dt);
        void updatepausemenubuttons(); 
        void updateshaders(const float& dt);
        void updateImGui(); 
        void TextInput();  
        
        //Render Funcions
        void renderbuttons(sf::RenderTarget& target);
        void renderGUI(sf::RenderTarget& target);
        void renderModes(sf::RenderTarget& target);
        void render(sf::RenderTarget* target);   
        
       

   
private:
    
        //Initalizer Functions
        void initkeybinds();
        void initview();
        void initFonts();
        void initButtons();
        void initbackground();
        void initvariables();
        void initpausemenu();
        void initeditorstatedata();
        void inittilemap();
        void initsidebar();
        void initGUI();
        void initbg(); 
        void initmodes(); 
        void initlevels(); 
        bool initshader();
        void initrendersprite();
        //Exception Handler Functions 
        void handlefonts(); 

     
    

        //GUI
       std::map<std::string, GUI::Button*> buttons;
       float cameraspeed;
      
    
        //Modes
        std::vector<EditorModes*> modes;
        unsigned activeMode;
        //Active Level Manager
       
                       
    
        //Text
        sf::Font font;
        sf::Text cursortext;
    
        //PauseMenu
        PauseMenu* pMenu;
    
        //TileMap
        TileMap* Tilemap;
        //GUI::EditorStateGUI* EditorStateGUI; 
        std::string curr_level;
    
        //Data
        EditorStateData editorstatedata;  
        Levels* levels;
       
        //Sounds
        sf::SoundBuffer buffer;
        sf::Sound UI_invalid;
    
        //Camera
        sf::View mainview;

        std::string customfile; 

        //GUI 
        int str_size; 
       sf::RectangleShape bg; 
        //sf::ConvexShape bg; 
       sf::RectangleShape bg_interior; 
       sf::FloatRect view_default_reset;
       sf::Sprite rendersprite; 
       sf::RenderTexture rendertexture;
       sf::Shader core_shader;
       AnimationComponent* animations; 
       sf::Sprite loading_sprite; 
       sf::Texture loading_texture; 
       bool buffering;
};
    

#endif /* EditorState_hpp */
