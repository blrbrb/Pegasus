//
//  State.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef State_hpp
#define State_hpp

#include <stack> 
#include <map>
#include "easylogging++.h"
#include <vector> 
#include <exception>
#include <SFML/System.hpp> 
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GraphicsSettings.hpp" 
#include "AudioComponent.h"
#include <iostream> 
#include "imgui.h"
#include "imgui-SFML.h" 

class Player;
class GraphicsSettings;
class State;



/// Class that passes important global data between states while the application is running.
class StateData
{
    
public:
    
    StateData() 
    {
        
    };
    
   ///The size of each individual tile in a grid. If The Tiles are square and have a uniform size 
    //float gridSize;
    // 
    sf::Vector2f* gridsize; 
    ///Pointer to the RenderWindow
    sf::RenderWindow* window;
    ///Acessable keys
    std::map<std::string, int>* supportedkeys;
    ///States
    std::stack<State*>* states;
    ///User-defined graphics settings
    GraphicsSettings* gfxsettings;

    Sound::MusicPlayer* music;
    //the sounds and music 
  
    
};



class State {

    public:
  
    State(StateData* state_data);
    
    virtual ~State();




    //public variables
    ///Has the State been quit?
    bool quit;
    ///Has the State been Paused?
    bool paused;
    //char shadow = *((&quit >> 3) + _asan_runtime_assigned_offset
    
    //Acessors
    /// Retrieve wether or not the user has requested to end the Application
    const bool& getquit() const;
    /// Retrieve wether or not the minimum allowed time between individual keystrokes has passed
    const bool getkeytime();
    
    //this has gotta be a virtual method for some reason, or the compiler will shit itself very hard.
     virtual void log(std::string stat, std::string log_instance);
    
    
    //Modifiers
    ///End the State, and return to either the main menu; or a previous state.
    /// @discussion NOTE: if there is no previou state, or if this function is accessed from the main menu you will get a  bad acess error
    void endstate();
    ///Pause the State
    void Pause_State();
    /// Un-Pause the state
    void Unpause_State();
    //Write to the Log file




    //Pure Virtual/Template Update functions
    virtual void updateMousePosition(sf::View* view = NULL); 
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = NULL) = 0;
    virtual void updatekeytime(const float& dt);  
    
    

protected:
   

    ///string ID of the state, e.g. "MainMenu", "Game" 
    std::string name;
    //unsigned int ID of the state
    unsigned state_ID; 
    sf::RenderWindow* window;
    //float gridSize;
    sf::Vector2f gridsize; 
    //std::ostream outfile; 
    StateData* state_data; 
   
    ///The cursor's position relative to the screen
    sf::Vector2i MousePosScreen;
    /// The cursor's position relative to the window
    sf::Vector2i MousePosWindow;
    /// The cursor's position relative to the view
    sf::Vector2f MousePosView;
    /// The cursor's position relative to the tile grid, 
    //@brief  The cursor's position relative to the tile grid. Stored in a Vector of Two Integers (x, y)
    sf::Vector2i MousePosGridI;
    //@brief The cursor's position relative to the tile grid. Stored in a Vector of Two Floats (x, y)
    sf::Vector2f MousePosGridF; 
     /// All useable keyboard keys
    std::map<std::string, int>* supportedkeys;
    /// Keys with a user-supplied map
    std::map<std::string, int> keybinds;

   
  
   


    virtual void initkeybinds() = 0; 
  
    float keytime;
    float keytime_MAX;
    
    virtual void initfiles();

    
   
    //State mechanism
    std::stack<State*>* states; 
    
    ///Texture Asset storage. Saved as a Map container and can be retrieved with a string
    std::map<std::string,sf::Texture> textures;
   
  
  
    
  
};

#endif /* State_hpp */
