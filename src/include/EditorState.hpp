//
//  EditorState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/1/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef EditorState_hpp
#define EditorState_hpp
#include "DefaultMode.hpp"
#include "EditorModes.hpp"
#include "GUI.hpp"
#include "PauseMenu.hpp"
#include "State.hpp"
#include "TileMap.hpp"
#include <filesystem>
#include "imgui-SFML.h"
#include "imgui.h"

class State;
class EditorModes;
class PauseMenu;
class TileMap;
class DefaultMode;
class PauseMenu;
class EditorStateData;


enum EDITOR_MODES { DEFAULT_MODE = 0,};

class EditorState : public State {
public:
    // Constructor and Destructor
    explicit EditorState(StateData* state_data);

    ~EditorState() override;

    // Update Functions
    void updateInput(const float& dt) override;
    void updateEditorInput(const float& dt);
    void update(const float& dt) override;
    void updateButtons();
    void updateGUI(const float& dt);
    void updateModes(const float& dt);
    void updatePauseMenuButtons();
    void updateMenuButtons();


    // Render Functions
    void renderButtons(sf::RenderTarget& target);
    void renderGUI(sf::RenderTarget& target);
    void renderModes(sf::RenderTarget& target);
    void render(sf::RenderTarget* target) override;

private:
    // Initializer Functions
    void initkeybinds() override;
    void initView();
    void initFonts();
    void initButtons();
    void initVariables();
    void initPauseMenu();
    void initEditorStateData();
    void initTileMap();
    void initSidebar();
    void initGUI();
    void initModes();
    void initRenderSprite();

    // Exception Handler Functions
    void handleFonts();

    // GUI
    std::map<std::string, GUI::Button*> buttons;
    float cameraSpeed;

    // Text
    sf::Font font;
    sf::Text* cursorText;

    // Modes
    std::vector<EditorModes*> modes;
    unsigned activeMode;

    // PauseMenu
    PauseMenu* pMenu;

    // TileMap
    TileMap* Tilemap;
    std::string curr_level;

    // Data
    EditorStateData editorStateData;

    // Camera
    sf::View mainView;

    std::string customFile;

    int str_size;

    sf::RectangleShape bg_interior;
    sf::FloatRect view_default_reset;
    sf::Sprite* renderSprite;
    sf::RenderTexture* renderTexture;

    //AnimationComponent* animations;
};

#endif /* EditorState_hpp */
