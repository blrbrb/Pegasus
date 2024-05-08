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
        explicit EditorState(StateData* state_data);
    
        ~EditorState() override;

    
        //Update Functions
        void updateInput(const float& dt) override;
        void updateEditorInput(const float& dt);
        void update(const float& dt) override;
        void updateButtons();
        void updateGUI(const float& dt);
        void updateModes(const float& dt);
        void updatePauseMenuButtons();
       // void updateshaders(const float& dt);


        //Render Functions
        void renderButtons(sf::RenderTarget& target);
        void renderGUI(sf::RenderTarget& target);
        void renderModes(sf::RenderTarget& target);
        void render(sf::RenderTarget* target);   
        
       

   
private:
    
        //Initializer Functions
        void initkeybinds() override;
        void initView();
        void initFonts();
        void initButtons();
        void initbackground();
        void initVariables();
        void initPauseMenu();
        void initEditorStateData();
        void initTileMap();
        void initSidebar();
        void initGUI();
        void initbg(); 
        void initModes();
        void initLevels();
        bool initShader();
        void initRenderSprite();

        //Exception Handler Functions
        void handleFonts();

        //GUI
       std::map<std::string, GUI::Button*> buttons; //could be causing error 
       float cameraSpeed;

        //Text
        sf::Font font;
        sf::Text cursorText;

        //Modes
        std::vector<EditorModes*> modes;
        unsigned activeMode;
        //Active Level Manager
       


        //PauseMenu
        PauseMenu* pMenu;
    
        //TileMap
        TileMap* Tilemap;
        //GUI::EditorStateGUI* EditorStateGUI; 
        std::string curr_level;
    
        //Data
        EditorStateData editorStateData;
        Levels* levels;
       
        //Sounds
        sf::SoundBuffer buffer;
        sf::Sound UI_invalid;
    
        //Camera
        sf::View mainView;

        std::string customFile;

        int str_size;
       sf::RectangleShape bg; 
       //sf::ConvexShape bg;
       sf::RectangleShape bg_interior; 
       sf::FloatRect view_default_reset;
       sf::Sprite renderSprite;
       sf::RenderTexture renderTexture;
       sf::Shader core_shader;
       AnimationComponent* animations; 
       sf::Sprite loading_sprite; 
       sf::Texture loading_texture; 
       bool buffering;
};
    

#endif /* EditorState_hpp */
