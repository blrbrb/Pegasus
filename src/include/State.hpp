//
//  State.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef State_hpp
#define State_hpp

#include "GraphicsSettings.hpp"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <stack>

class Player;
class GraphicsSettings;
class State;

/// Class that passes important global data between states while the application is running.
class StateData {

public:
    StateData() { };

    /// The size of each individual tile in a grid. If The Tiles are square and have a uniform size
    // float gridSize;
    //
    sf::Vector2f gridSize;
    /// Pointer to the RenderWindow
    //sf::RenderWindow* window;
    std::shared_ptr<std::_NonArray<sf::RenderWindow>> window;

    std::map<std::string, int>* supportedKeys;

    std::stack<State*>* states;
    /// graphics and window settings
    GraphicsSettings* gfxsettings;

    // the sounds and music
};

class State : public std::enable_shared_from_this<State> {

public:
    State(StateData* state_data);

    virtual ~State();


    /// Has the State been quit?
    bool quit;

    bool paused;
    // char shadow = *((&quit >> 3) + _asan_runtime_assigned_offset


    /////////////////////////////////////////////////
    /// \brief return true if state stack is empty, or if quit is pressed from the main menu
    ///
    /// \return  const bool&
    ///
    /////////////////////////////////////////////////
    [[nodiscard]] const bool& getQuit() const;

    /////////////////////////////////////////////////
    /// \brief calculates the number of frames that have passed between inputs and checks to see if a minimum time value has been met
    /// before allowing another input
    ///
    /// \return bool
    ///
    /////////////////////////////////////////////////
    bool getKeyTime();

    virtual void log(std::string stat, std::string log_instance);

    /////////////////////////////////////////////////
    /// \brief end the state and pop from the application stack
    ///
    /// \return void
    ///
    /////////////////////////////////////////////////
    void endState();

    /////////////////////////////////////////////////
    /// \brief stop updating
    ///
    /// \return void
    ///
    /////////////////////////////////////////////////
    void pause();

    /////////////////////////////////////////////////
    /// \brief resume updating
    ///
    /// \return void
    ///
    /////////////////////////////////////////////////
    void unpause();
    // Write to the Log file


    /////////////////////////////////////////////////
    /// \brief keep track of the mouse's position
    ///
    /// \param nullptr sf::View* view=
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void updateMousePosition(sf::View* view = nullptr);
    /////////////////////////////////////////////////
    /// \brief handle user inputs
    ///
    /// \param dt const float&
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void updateInput(const float& dt) = 0;
    /////////////////////////////////////////////////
    /// \brief final update
    ///
    /// \param dt const float&
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void update(const float& dt) = 0;
    /////////////////////////////////////////////////
    /// \brief render to a sf::RenderTarget*
    ///
    /// \param nullptr sf::RenderTarget* target=
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    virtual void updateKeyTime(const float& dt);

protected:

    std::string name;

    unsigned state_ID;

    sf::RenderWindow* window;

    sf::Vector2f gridSize;

    StateData* state_data;

    /// The cursor's position relative to the screen
    sf::Vector2i MousePosScreen;
    /// The cursor's position relative to the window
    sf::Vector2i MousePosWindow;
    /// The cursor's position relative to the view
    sf::Vector2f MousePosView;
    /// The cursor's position relative to the tile grid,
    //@brief  The cursor's position relative to the tile grid. Stored in a Vector of Two Integers (x, y)
    sf::Vector2i MousePosGrid;
    //@brief The cursor's position relative to the tile grid. Stored in a Vector of Two Floats (x, y)

    std::map<std::string, int>* supportedKeys;
    /// Keys with a user-supplied map
    std::map<std::string, int> keyBinds;

    /////////////////////////////////////////////////
    /// \brief load keybinds and application control keys from disk
    ///
    /// \return virtual void
    ///
    /////////////////////////////////////////////////
    virtual void initkeybinds() = 0;

    float keyTime;
    float keyTimeMax;

    virtual void initFiles();

    // State mechanism
    std::stack<State*>* states;

    /// Texture Asset storage. Saved as a Map container and can be retrieved with a string
    std::map<std::string, sf::Texture> textures;
};

#endif /* State_hpp */
