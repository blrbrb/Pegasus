/**
  GameState.hpp
engineFramework

 Created by Eli Reynolds on 1/22/20.
 @author Eli Reynolds
 @header GameState.hpp
 @brief the state containing the main gameplay elements, such as the overworld, and battlestate.
 @Copyright © 2020 Eli Reynolds. Apache License .
 @version 0.06.0.0
*/

#ifndef GameState_hpp
#define GameState_hpp


#include "PauseMenu.hpp"
#include "PlayerGUI.hpp"
#include "State.hpp"
#include "TileMap.hpp"
#include "placeholder-character.h"


class State;
class Blrb;
class PauseMenu;
class Player;
class TileMap;

class GameStateData {
public:
    GameStateData() { };

    std::map<std::string, int>* keybinds;
    sf::Font* font;
};


class GameState : public State {

public:
    GameState(StateData* state_data);
    virtual ~GameState();


    /////////////////////////////////////////////////
    /// \brief keep the view centered on the player as the player moves
    ///
    /// \param dt const float&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void updateView(const float& dt);

    void updateShaders(const float& dt);

    /////////////////////////////////////////////////
    /// \brief update player controls
    ///
    /// \param dt const float&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void updatePlayerInput(const float& dt);

    void updateMapEditor(const float& dt);


    /////////////////////////////////////////////////
    /// \brief update the player's animations, hitbox, physics
    ///
    /// \param dt const float&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void updatePlayer(const float& dt);

    void updateMapEditorInput(const float& dt);

    /////////////////////////////////////////////////
    /// \brief  final update
    ///
    /// \param dt const float&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void update(const float& dt);

    void checkforendstate();

    /////////////////////////////////////////////////
    /// \brief update SFML events (window close, resize, etc)
    ///
    /// \param dt const float&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void updateInput(const float& dt);

    void updateButtons();

    void updateTileMap(const float& dt);


    void render(sf::RenderTarget* target);



    void renderMapEditor(sf::RenderTarget* target);

    void updateDialouge(const float& dt);

    const bool savegame() const;

private:

    sf::View view;
    float cameraspeed;

    int editor_layer;
    short editor_type;
    bool editor_collision;
    Player* player;
    PauseMenu* pMenu;
    TileMap* Tilemap;
    sf::Text* cursortext;
    GUI::TextureSelector* texture_selector;

    sf::Font font;
    sf::RenderTexture* rendertexture;
    sf::Sprite* rendersprite;
    sf::Color selection_color;
    sf::RectangleShape select_Rect;
    std::map<std::string,GUI::Button*> buttons;
    sf::IntRect TextureRect;
    ImVec4 Selection_colorImGui;

    sf::Shader core_shader;
    sf::Shader lantern_shader;
    float shadertime;


    sf::Vector2i ViewGridPosition;




    GameStateData gamestatedata;


    void initdeferedrender();
    void initview();
    void initkeybinds();
    void inittextures();
    void initplayers();
    void initbuttons();
    void initshaders();
    void initfonts();
    void initpausemenu();
    void initTileMap();
    void initgamestatedata();
    void initvariables();

    void initworldbounds();
    void initmapeditor();

    void handletilemap();
    void handleshader();
    void handlekeybinds();
    void handlefonts();
};
#endif /* GameState_hpp */
