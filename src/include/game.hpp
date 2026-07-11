
#include "MainMenuState.hpp"
#include "easylogging++.h"
#include "icon.h"
#include "imgui-SFML.h"
#include "imgui.h"

#include <cmath>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

#ifndef Game_hpp
#define Game_hpp

class Game {
public:
    Game();
    ~Game();

    // Misc
    void endApplication();
    void resizeWindow();
    void setFullScreen();
    void log(const std::string& stat);

    // Final Render
    void render();

    // To Main loop
    void running();

    // Update Functions
    void UpdateEvents();
    void UpdateDT();
    void Update();

    std::ofstream* outfile;

private:
    /// All of the mappable keyboard keys for user input.
    std::map<std::string, int> supported_keys;
    // sf::Joystick joystick;

    //sf::RenderWindow* window;
    std::shared_ptr<std::_NonArray<sf::RenderWindow>> window;
    sf::Event event;
    sf::Vector2f gridSize;
    bool fullscreen;

    sf::Clock dtClock;
    sf::Clock ImGuiClock;
    /// Delta Time
    float dt;
    /// Elapsed Time
    float elapsedTime;

    /// The State Mechanism, stored in a stack of "State" objects
    std::stack<State*> states;

    const float virtualWidth = 1920.0f;
    const float virtualHeight = 1080.0f;
    StateData state_data;

    std::shared_ptr<std::_NonArray<GraphicsSettings>> gfxsettings;


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
