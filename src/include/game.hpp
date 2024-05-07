
#include "MainMenuState.hpp"
#include "icon.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <boost/config.hpp> 
#include <deque>
#include <map>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string_view>
#include <mutex>
#include "easylogging++.h"
#include <random>
#include <memory>
#include <GL/freeglut.h>

#ifndef Game_hpp
#define Game_hpp



class Game {
public:
    
    
     Game();
    ~Game();
    
    //Misc
    void endApplication();
    void resizeWindow();
    void setFullScreen();
    void log(const std::string& stat);
    
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
    std::map<std::string, int> supported_keys;
    sf::Joystick joystick; 


    sf::RenderWindow* window; 
    
  
    
    Sound::MusicPlayer* music_player; 
    sf::Event event;
    sf::Vector2f gridSize;
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
    void initWindow();
    void initGTK();
    void initStates();
    void initKeys();
    bool initJoySticks();
    void initVariables();
    void initGraphicsSettings();
    void initStateData();
    void initWindowIcon(); 
  
    
};


#endif /* Game_hpp */
