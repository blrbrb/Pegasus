//
//  MainMenuState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/25/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "GameState.hpp"

#include "EditorState.hpp"
#include "GUI.hpp"
#include "GraphicsSettings.hpp"
#include "SettingsState.hpp"

class MainMenuState : public State {
public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    // Functions
    /// Update User Input
    /// @param dt Delta Time
    void updateInput(const float& dt);
    void update(const float& dt);
    void updatebuttons(const float& dt);
    void reconfigure_log();
    // Render Functions
    void renderbuttons(sf::RenderTarget& target);


    void render(sf::RenderTarget* target = nullptr);

private:

    void initkeybinds();
    void initFonts();
    void initGUI();
    void resetGUI();
    void initbackground();
    void initvariables();
    void setmusic();

    // Private &variables
    sf::Font font;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::SoundBuffer click;

    std::map<std::string, GUI::Button*> buttons;
};

#endif /* MainMenuState_hpp */
