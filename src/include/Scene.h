
#ifndef Scene_hpp
#define Scene_hpp
#include "State.hpp"
#include "PauseMenu.hpp"
#include "TileMap.hpp"
#include "PlayerGUI.hpp"
#include "EnemySystem.hpp"
#include "DialougeSystem.hpp"
#include "BattleState.hpp"
#include "AudioComponent.h"

/// The Main Scene, containing the main gameplay elements
class Scene : public State {


public:

    Scene(StateData* state_data);
    virtual ~Scene();

    /// Control the area the Player is able to see on screen.
    /// @param dt Delta-Time
    ///@discussion This function works by setting the center of the sf::View to the center of the Player's sprite, and then constantly checking to see if the view's bounding rectangle around the player has exceeded the maximum size of the tilemap and correcting by reseting the center of the view.
    void updateView(const float& dt);


    void updateShaders(const float& dt);


    /// Update the basic controls for the Player
    /// @param dt Detla-Time
    void updatePlayerInput(const float& dt);

    /// Update the User's GUI, HP, coin counter etc
    /// @param dt Delta-Time
    void updatePlayerGUI(const float& dt);

    /// Update components associated with the Player. e.g, updating the Animations, and hitbox.
    /// @param dt Delta-Time
    void updatePlayer(const float& dt);

    /// Check for an encounter between the player, and an enemy
    /// @param dt Delta-Time
    void updateEncounter(Enemy* enemy, const int index, const float& dt);


    ///Update the State
    void update(const float& dt);
    ///Check for a user-requested quit from the state
    void checkforendstate();
    ///Update user input, e.g close the window
    void updateInput(const float& dt);
    ///Update the Buttons
    void updatebuttons();
    ///Update the Tile Map, shaders, etc
    void updatetilemap(const float& dt);
    ///Render all of the Scene elements
    void render(sf::RenderTarget* target);


    void updateDialouge(const float& dt);


    void updateEnemies(const float& dt);


    //Modifiers 
    const bool savegame() const;

private:

    //View and Camera
    sf::View view;
    float cameraspeed;
    class BattleState* battleState;
    //sf::Color debug; 
    float debug1;
    sf::Color debug;
    ImVec4 selection_color_Imgui;

    Player* player;
    PlayerGUI* playerGUI;
    PauseMenu* pMenu;
    TileMap* Tilemap;


    EnemySystem* enemysystem;
    DialougeSystem* dialougeSystem;


    sf::Font font;
    sf::RenderTexture rendertexture;
    sf::Sprite rendersprite;
    sf::Color selection_color;
    ImVec4 Selection_colorImGui;
    //Shaders
    sf::Shader core_shader;
    sf::Shader lantern_shader;
    float shadertime;


    //Sounds
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::Vector2i ViewGridPosition;


    //Enemies
    std::vector<Enemy*> activEnemies;


    StateData statedata;

    //Init Functions
    void initdeferedrender();
    void initview();
    void initkeybinds();
    void inittextures();
    void initplayers();
    void initplayerGUI();
    void initfonts();
    void initpausemenu();
    void inittilemap();
    void initshaders();
    void initenemysystem();
    void initScenedata();
    void initvariables();
    void initdialougesystem();
    void initworldbounds();




    //Exception handler Functions 
    void handletilemap();
    void handleshader();
    void handlekeybinds();
    void handlefonts();

};
#endif /* Scene_hpp */
