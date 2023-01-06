//
//  Game.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#ifndef Game_hpp
#define Game_hpp

#include "MainMenuState.hpp"
#include "icon.h"

class Game {
public:
    
    
     Game();
    ~Game();
    
    //Misc
    void endapplication();
    void resizewindow(); 
    void setfullscreen(); 
    void log(std::string stat);
    
    //Final Render
    void render();
    
    //To Main loop
    void running();
    
    //Update Functions 
    void UpdateEvents();
    void UpdateDT();
    void Update();
    
    std::ofstream* outfile; 
    
private:
  
    ///All of the mappable keyboard keys for user input.
    std::map<std::string, int> supportedkeys;
    sf::Joystick joystick; 
    
     sf::RenderWindow* window;
    Sound::MusicPlayer* music_player; 
    sf::Event event;
    //float gridsize; 
    sf::Vector2f gridsize; 
    bool fullscreen;
    
    sf::Clock dtClock;
    sf::Clock ImGuiClock; 
    ///Delta Time
    float dt;
    ///Elapsed Time 
    float elapsedTime;
    
    ///The State Mechanism, stored in a stack of "State" objects
    ///The State Mechanism, stored in a stack of "State" objects
    std::stack<State*> states;
    StateData state_data;
    GraphicsSettings* gfxsettings; 
    //std::ostream* ostream;
    //init functions
    void load();
    void initwindow();
    void initstates();
    void initlog(); 
    void initkeys();
    bool initJoySticks();
    void initVariables();
    void initGraphicsSettings();
    void initstatedata();
    void initWindowIcon(); 
  
    
};


#endif /* Game_hpp */
