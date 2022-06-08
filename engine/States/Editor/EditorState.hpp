//
//  EditorState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/1/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#ifndef EditorState_hpp
#define EditorState_hpp
#include "engineFramework/States/State.hpp"
#include "Componets/GUI/GUI.hpp"
#include  "engineFramework/States/PauseMenu.hpp"
#include "engineFramework/Map/TileMap.hpp"
#include "engineFramework/States/Editor/EditorModes.hpp" 




class State;
class StateData; 

class PauseMenu;
class TileMap;
class EditorModes; 
class DefaultMode;
class EnemyEditorMode;
class EnviornmentalMode; 
class EditorStateData; 



enum EDITOR_MODES {DEFAULT_MODE = 0, ENEMY, ENV};


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
        void updateGUI(const float& dt);
        void updateModes(const float& dt);
        void updatepausemenubuttons();
        
        //Render Funcions
        void renderbuttons(sf::RenderTarget& target);
        void renderGUI(sf::RenderTarget& target);
        void renderModes(sf::RenderTarget& target);
        void render(sf::RenderTarget* target = nullptr);
            
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
        void initmodes(); 
      
     
    

        //GUI
       std::map<std::string, GUI::Button*> buttons;
       float cameraspeed;
      
    
        //Modes
        std::vector<EditorModes*> modes;
        unsigned activeMode;
                       
    
        //Text
        sf::Font font;
        sf::Text cursortext;
    
        //PauseMenu
        PauseMenu* pMenu;
    
        //TileMap
        TileMap* Tilemap;
    
        //Data
        EditorStateData editorstatedata; 
       
        //Sounds
        sf::SoundBuffer buffer;
        sf::Sound UI_invalid;
    
        //Camera
        sf::View mainview;

    
   
};
    

#endif /* EditorState_hpp */
