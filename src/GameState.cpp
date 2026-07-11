//
//  GameState.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .

#include "include/GameState.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

GameState::GameState(StateData* state_data)
    : State(state_data)
{
    try {  this->inittextures();
        this->initplayers();

        this->initview();
        this->initdeferedrender();
        this->initkeybinds();
        this->initfonts();
        this->initpausemenu();
        this->initTileMap();
        this->initmapeditor();
         this->initvariables();

    } catch (std::exception& e) {

        std::cerr << e.what() << std::endl;


    }

}

GameState::~GameState()
{

    delete this->player;
    delete this->pMenu;
    delete this->Tilemap;

}

void GameState::initvariables()
{
    this->name = "Game";
    this->state_ID = this->states->size();
    this->shadertime = 0.f;
    this->select_Rect.setSize(sf::Vector2f(this->state_data->gridSize.x, this->state_data->gridSize.y));
    this->select_Rect.setTexture(this->Tilemap->getTileSheet());
    this->TextureRect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 24));
    this->editor_layer = 0;
    this->editor_collision = 0;
    this->cursortext = new sf::Text(this->font);

    this->cursortext->setCharacterSize(12);
   this->cursortext->setFillColor(sf::Color::White);
   this->cursortext->setOutlineThickness(2.f);
   this->cursortext->setOutlineColor(sf::Color::Black);
}



void GameState::initbuttons()
{
    this->buttons["MAP_EDITOR_CLOSE"] = new GUI::Button(GUI::pixelpercentX(23.f,this->state_data->gfxsettings->resolution),GUI::pixelpercentY(20.f,this->state_data->gfxsettings->resolution),GUI::pixelpercentX(20.f,this->state_data->gfxsettings->resolution),GUI::pixelpercentY(2.f, this->state_data->gfxsettings->resolution),&this->font,"Close Editor",0,1);
}

void GameState::initdeferedrender()
{

    this->rendertexture = new sf::RenderTexture(sf::Vector2u(this->state_data->gfxsettings->resolution.size.x, this->state_data->gfxsettings->resolution.size.y));
    // this->log("creating a new render texture with the size " + this->state_data->gfxsettings->resolution.width + 'x' + this->state_data->gfxsettings->resolution.height, "State::Game");
    if (!this->rendertexture) {
        // LOG(FATAL) << "failed to create renderTexture at " << this->state_data->gfxsettings->resolution.width << "x" << this->state_data->gfxsettings->resolution.height;
        throw std::runtime_error("unable to create rendertextrue GameState Line 78");
    }
    this->rendersprite = new sf::Sprite(this->rendertexture->getTexture());
    // this->rendersprite.setTexture(this->rendertexture->getTexture());

    this->rendersprite->setTextureRect(
        sf::IntRect(sf::Vector2i(
                        0,
                        0),
            sf::Vector2i(
                this->state_data->gfxsettings->resolution.size.x,
                this->state_data->gfxsettings->resolution.size.y))

    );
}
//
void GameState::initworldbounds()
{
}

void GameState::initshaders()
{
    const sf::Color testcolor = sf::Color(250, 250, 250, 100);

    if (!this->core_shader.loadFromFile("Data/Shader/vertex_shader.vert", "Data/Shader/fragment_shader.frag")) {
        // LOG(WARNING) << "unable to load core shaders";
        throw std::runtime_error("ERROR Unable to load shaders Gamestate line 71");

    } else {
        // sf::Vector2f resolution = sf::Vector2f(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height);

        // this->core_shader.setUniform("resolution", sf::Glsl::Vec2(resolution));
    }
    // this->core_shader.setUniform("ambientData", sf::Glsl::Vec4(testcolor));
}

void GameState::initview()
{

    this->view.setSize(sf::Vector2f(this->state_data->gfxsettings->resolution.size.x / 4, this->state_data->gfxsettings->resolution.size.y / 4));

    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.size.x) / 4.f, static_cast<float>(this->state_data->gfxsettings->resolution.size.y) / 4.f));
}

void GameState::initkeybinds()
{

    std::ifstream ifs("Init/GameState_Keys.ini", std::ifstream::in);

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        std::cout << "gamestate keys exist" << std::endl;
        // this->log << "GAmestate Keybinds exist";
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
            // this->log << key << " " << key2;
        }
    } else {
        throw std::runtime_error("ERROR unable to load GameState Keybinds GameState lin 145");
    }

    ifs.close();
}



void GameState::inittextures()
{

    if (!this->textures["PLAYER_SHEET"].loadFromFile(std::filesystem::path("Resources/Assets/Entity/PlayerSheets/test.png"))) {
       // LOG(WARNING) << "std::optional<sf::Texture> could not find whatever";

        throw std::runtime_error("ERROR Could not load Player Sheet texture GameState lin 168");
    }

    if (!this->textures["ENEMY_SHEET"].loadFromFile("Resources/Assets/Entity/EnemySheets/Blrb.png")) {
        // LOG(WARNING) << "unable to load default enemy spritesheet/s Resources/Assets/Entity/EnemySheets/Blrb.png";

        throw std::runtime_error("ERROR Could Not load Enemy Sheet textures GameState lin 175");
    }
}

void GameState::initfonts()
{
    if (!this->font.openFromFile("Resources/Assets/Fonts/OpenSans-Variable.ttf")) {
        // LOG(WARNING) << "unable to load default font Resources/Assets/Fonts/OpenSans-Variable.ttf";
        /// LOG(WARNING) << "throwing runtime exception on line 209";
        throw std::runtime_error("ERROR Could not load font from font file GameState lin 185");
    }
}

void GameState::initmapeditor()
{
    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;

    this->texture_selector = new GUI::TextureSelector(GUI::pixelpercentX(30.f,vm),GUI::pixelpercentY(60.f,vm),GUI::pixelpercentY(30.f,vm),GUI::pixelpercentY(40.f,vm),this->state_data->gridSize, this->Tilemap->getTileSheet(), "X");
}
void GameState::initplayers()
{

    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
    // this->player = new Player("Data/new_pony.json", this->textures["PLAYER_SHEET"]);
}

void GameState::initgamestatedata()
{
    this->gamestatedata.keybinds = &this->keyBinds;
    this->gamestatedata.font = &this->font;
    std::cout << "init gamestate data" << std::endl;
}

void GameState::initpausemenu()
{
    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;

    this->pMenu = new PauseMenu(this->state_data->gfxsettings->resolution, this->font);

    this->pMenu->addbutton("Pause_Quit_Button", GUI::calcCharSize(vm), "Quit", GUI::pixelpercentX(33.f, vm), GUI::pixelpercentY(15.f, vm), GUI::pixelpercentX(10.f, vm));

    std::cout << "init gamestate pause menu" << std::endl;
}

void GameState::initTileMap()
{
    this->Tilemap = new TileMap(this->state_data->gridSize, 100, 100, "Resources/Assets/Tiles/sheet.png");

    this->Tilemap->importTMX("my-island.tmx");

    std::cout << "init gamestate tilemap" << std::endl;
}

void GameState::update(const float& dt)
{



    this->updateView(dt);
    this->updateMousePosition(&this->view);
    this->updateKeyTime(dt);
    this->updateInput(dt);

    if (!this->paused) // Update while unpaused
    {


        this->updatePlayerInput(dt);
        this->updateTileMap(dt);
        this->updatePlayer(dt);
        this->updateMapEditor(dt);

        ;

    } else // Update while Paused
    {
        this->pMenu->update(this->MousePosWindow);
        this->updateButtons();

        // ImGui::Text("Hello, world %d", 123);

        // ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
        // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    }
}

void GameState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime()) {
        if (!this->paused)
            this->pause();
        else
            this->unpause();
    }
    this->updateMapEditorInput(dt);
}


void GameState::updateTileMap(const float& dt)
{
    this->Tilemap->update(this->player, dt);
    this->Tilemap->updateWorldBoundsCollision(this->player, dt);
    this->Tilemap->updateTileCollision(this->player, dt);
    this->Tilemap->updateTiles(this->player, dt);
}

void GameState::updateButtons()
{

    for (auto& it : this->buttons) {
        it.second->update(this->MousePosWindow);
    }

    if (this->pMenu->isButtonPressed("Pause_Quit_Button")) {
        this->endState();
        this->endState();
    }
}

void GameState::updateView(const float& dt)
{
   // std::cout << this->state_data->gfxsettings->resolution.size.y << std::endl;
//    std::cout << "player position: " << this->player->getPosition().x << std::endl;
    this->view.setCenter(sf::Vector2f(std::floor(this->player->getPosition().x + static_cast<float>(this->state_data->gfxsettings->resolution.size.x / 20)), std::floor(this->player->getPosition().y + static_cast<float>(this->state_data->gfxsettings->resolution.size.y / 20))));

    if (this->Tilemap->getMaxSize().x >= this->view.getSize().x) {

        if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f) {
            this->view.setCenter(sf::Vector2f(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y));
        }

        else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->Tilemap->getMaxSize().x) {
            this->view.setCenter(sf::Vector2f(3000.f - this->view.getSize().x / 2.f, this->view.getCenter().y));
        }
    }

    //std::cout << "update view gamestate" << std::endl;
    if (this->Tilemap->getMaxSize().y >= this->view.getSize().y) {

        if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f) {
            this->view.setCenter(sf::Vector2f(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f));
        }

        else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->Tilemap->getMaxSize().y) {
            this->view.setCenter(sf::Vector2f(this->view.getCenter().x, this->Tilemap->getMaxSize().y - this->view.getSize().y / 2.f));
        }
    }

    // Update the GridPosition view
    this->ViewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->state_data->gridSize.x);

    this->ViewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->state_data->gridSize.y);
}

void GameState::updateShaders(const float& dt)
{

    this->shadertime += dt / 100;
    if (this->shadertime > 1) {
        this->initvariables();
    }
    // this->log << shadertime << std::endl;
    // this->core_shader.setUniform("time", sf::Vector2f(shadertime, 0.f));
}


void GameState::updateMapEditorInput(const float& dt)
{
    //sf::Vector2i test = {this->ViewGridPosition.x -this->MousePosGrid.x ,this->MousePosGrid.y};
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))) {

        // if the user's mouse is not on the sidebar
        // std::cout << this->texture_selector->getActive() << " texture selector state " << std::endl;
        // if the texure selector is not active
        if (!this->texture_selector->getActive()) {

            // if adding tiles is locked to one layer
            if (this->Tilemap->lock_layer)
            {
                if (this->Tilemap->TileEmpty(this->MousePosGrid.x, this->MousePosGrid.y, 0))
                {
                    this->Tilemap->addTile(this->MousePosGrid.x, this->MousePosGrid.y, this->editor_layer, this->TextureRect, this->editor_collision, this->editor_type);
                    // this->Tilemap->addTile(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y, this->editor_layer, this->TextureRect, this->editor_this->editor_collision, this->type);
                    // std::cout << "LOCKED: Tile Added" << std::endl;
                }


            }

            else
            {
                this->Tilemap->addTile(this->MousePosGrid.x, this->MousePosGrid.y, this->editor_layer, this->TextureRect, this->editor_collision, this->editor_type);
                //std::cout << "TILE ADDED " << std::endl;
            }
        }
        else
        {
            this->TextureRect = this->texture_selector->getTextureRect();

        }

    }


    // Remove a tile
    else if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete))) {

        // if the user's mouse is not inside the texture selector
        if (!this->texture_selector->getActive() ) {
            // if the cursor is over a valid tile, ok to place
            if (this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->editor_layer) != -1) {

                if (this->Tilemap->lock_layer) {
                    if (!this->Tilemap->TileEmpty(this->MousePosGrid.x, this->MousePosGrid.y, this->editor_layer)) {
                        this->Tilemap->removeTile(this->MousePosGrid.x, this->MousePosGrid.y, this->editor_layer, TileTypes::NORMAL);
                        //std::cout << "LOCKED: Tile Removed" << std::endl;
                    } else {
                        // LOG(INFO) << "editor tried to place more than one tile on a locked layer";
                    }

                }

                else {
                    this->TextureRect = this->texture_selector->getTextureRect();
                }
                // else if adding tiles is not locked to one layer
                if (!this->Tilemap->lock_layer) {

                    this->Tilemap->removeTile(this->MousePosGrid.x, this->MousePosGrid.y, 1, TileTypes::NORMAL);

                    //std::cout << "Tile Removed" << std::endl;
                }

            }

            else if (this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->editor_layer) == -1) {
                std::cerr << "tried to place tile on invalid layer" << '\n';
            }
        }
    }
    this->cursortext->setPosition({this->MousePosWindow.x + 100.f, this->MousePosWindow.y - 50.f});
    std::stringstream ss;
    ss << "Mouse Position View:" << this->MousePosView.x << " " << this->MousePosView.y <<
    "\n" << "Mouse Position Grid: "<< this->MousePosGrid.x<< " " << this->MousePosGrid.y <<
    "\n" << "View Position Grid: " << this->ViewGridPosition.x << " " << this->ViewGridPosition.y <<
    "\n" << this->select_Rect.getSize().x << " " << this->select_Rect.getSize().y <<
    "\n" << "Collision: " << this->editor_collision <<
    "\n" << "Type: " << this->editor_type <<
    "\n" << "Tiles: " << this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->editor_layer);


    this->cursortext->setString(ss.str());

}
void GameState::updateMapEditor(const float &dt)
{

    this->texture_selector->update(this->MousePosWindow, dt);
    //this->select_Rect.setTextureRect(this->texture_selector->getTextureRect());


   // this->texturesample->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>(this->statedata->gridSize.x), static_cast<int>(this->statedata->gridSize.y)), sf::Vector2i(0, 0)));

    if (!this->texture_selector->getActive()) {

        this->select_Rect.setTextureRect(this->TextureRect);
        //this->texturesample->setTextureRect(this->TextureRect);
        this->select_Rect.setPosition(sf::Vector2f(this->MousePosWindow.x, this->MousePosWindow.y));
    }
    //this->texturesample->setTexture(*this->select_Rect.getTexture());

   // this->select_Rect.setOrigin(sf::Vector2f(this->select_Rect.getLocalBounds().size.x, this->select_Rect.getLocalBounds().size.y) / 2.f);

    //this->select_Rect.setTextureRect(this->texture_selector->getTextureRect());
    //this->texturesample->setTextureRect(this->TextureRect);
}

void GameState::updatePlayerInput(const float& dt)
{
    // check for a quit

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {
        this->player->move(dt, 1.f, 0.f);
        // this->log << "RIGHT" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {

        this->player->move(dt, -1.f, 0.f);
        // this->log << "LEFT" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) {
        this->player->move(dt, 0.f, -1.f);
        // this->log << "UP" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {

        this->player->move(dt, 0.f, 1.f);
        // this->log << "DOWN" << std::endl;
    }

    // hide the player's inventory

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this->player->saveToFile("Data/new_pony.json");
    }
}

void GameState::render(sf::RenderTarget* target)
{


    if (!target)
        target = this->window;

    this->rendertexture->clear();

    this->rendertexture->setView(this->view);



    this->Tilemap->render(*this->rendertexture, this->view, this->ViewGridPosition, false);
    // this->Tilemap->render()
    // this->Tilemap->renderlighttile(this->renderTexture, &this->core_shader);

    // target->mapPixelToCoords(static_cast<sf::Vector2i>(this->player->getCenter()));
    this->Tilemap->defferedRender(*this->rendertexture);

    this->player->render(*this->rendertexture);
    this->rendertexture->setView(this->rendertexture->getDefaultView());

    this->renderMapEditor(this->rendertexture);
    //this->test_button->render(*this->rendertexture);
    // the dialouge system needs to be rendered with the view set to the PlayerGUI's view, that way attached dialouge will fill the screen correctly.
    // this->dialougeSystem->render(this->renderTexture);

    if (this->paused) {
        this->rendertexture->setView(this->rendertexture->getDefaultView());
        this->pMenu->render(*this->rendertexture);
    }

    this->rendertexture->display();
    this->rendersprite->setTexture(this->rendertexture->getTexture());
    target->draw(*this->rendersprite);

}

void GameState::renderMapEditor(sf::RenderTarget* target)
{

    if (!this->texture_selector->getActive()) {
        //this->view =
        //target->setView(this->rendertexture->getDefaultView());
        target->draw(this->select_Rect);
    }
    target->draw(*this->cursortext);
    //target->setView(this->window->getDefaultView());
    this->texture_selector->render(*target);
    //target->setView(this->rendertexture->getDefaultView());
}
void GameState::updateDialouge(const float& dt)
{
    if (this->getKeyTime()) {
        // this->dialougeSystem->update(dt);
    }
}

void GameState::checkforendstate()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {

        // return this->quit = true;
    }
    // else return this->quit = false;
}

void GameState::updatePlayer(const float& dt)
{
    this->player->update(dt, this->MousePosView);
}



const bool GameState::savegame() const
{
    std::ofstream out;

    out.open("Data/Saves/Save.dat", std::ios::out | std::ios::binary);

    if (out.is_open()) {

    }

    else {

        throw std::runtime_error("ERROR CODE GAMESTATE:579 || GAMESTATE::SAVE || COULD NOT SAVE");

        return false;
    }

    out.close();

    return true;
}




void GameState::handletilemap()
{
    // LOG(INFO) << "attemping to handle exception";
    std::string custom_tilemap_path = "";

    for (auto& p : std::filesystem::recursive_directory_iterator("Data/TileMap/")) {
        if (p.path().extension() == ".slmp") {
            // LOG(INFO) << "searcing for tilemap files in " << p.path().stem().string();
            // LOG(INFO) << "tilemap found";
            custom_tilemap_path = p.path().string();
            break;
        }
    }

    try {
        this->Tilemap->loadFromFile(custom_tilemap_path);
    }

    catch (std::runtime_error& e) {

        std::cerr << e.what() << std::endl;
    }

    // LOG(INFO) << "done" << std::endl;
}

void GameState::handleshader()
{
}

void GameState::handlekeybinds()
{
}

void GameState::handlefonts()
{

    // LOG(INFO) << "attemping to handle exception";
    std::string custom_font_path = "";

    for (auto& p : std::filesystem::recursive_directory_iterator("Resources/Assets/Fonts")) {
        if (p.path().extension() == ".ttf") {
            // LOG(INFO) << "searcing for font files in " << p.path().stem().string();
            // LOG(INFO) << "font found";
            custom_font_path = p.path().string();
            break;
        }
    }

    // LOG(INFO) << "loading font from " << " " << custom_font_path;
    if (!this->font.openFromFile(custom_font_path)) {
        // LOG(WARN) << "unable to load fonts" << "\n";
    };
    // LOG(INFO) << "font loaded successfuly" << std::endl;
}
