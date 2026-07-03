//
//  Game.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "include/game.hpp"

#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/WindowEnums.hpp>
// INITIALIZE_EASYLOGGING

Game::Game()
    : event(sf::Event::Closed { })
{

    std::cout << std::filesystem::current_path().string() << std::endl;
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initJoySticks();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{

    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
        // LOG(INFO) << "deleting..." << " " << states.size() << " " << "in Game.cpp";
    }
}

// initalizer functions

void Game::initKeys()
{

    /*!
     @brief  Load the supported input methods (keys,buttons, controllers etc) from the ini file and store them as shared class variables

     @param  void

     @return void







      */
    // LOG(INFO) << "creating keyBinds ";

    std::ifstream ifs("Init/Supported_Keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value) {
            this->supported_keys[key] = key_value;
            // std::cout << "Game.cpp supported Keys are As Follows:" << " " << this->supported_keys.at(key) << std::endl;
        }
    }

    ifs.close();
}

bool Game::initJoySticks()
{

    // if (this->joystick.isConnected(0)) {

    // return true;
    //  } else
    return false;
}

void Game::initStates()
{

    this->states.push(new MainMenuState(&this->state_data));
}

void Game::initGraphicsSettings()
{

    this->gfxsettings = new GraphicsSettings();

    this->gfxsettings->loadFromFile("Config/Window.cfg");
}

void Game::initWindow()
{

    /*!
     @brief  Initalizes the media layer the application runs on

     @param   void

     @return  void

    */

    ImGui::CreateContext();

    if (this->gfxsettings->fullscreen) {
        // it might be a good idea to assign the hanging window1 pointer a value, and then use the newer .create method
        // this->window1 = new sf::RenderWindow();

        this->window = new sf::RenderWindow(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Resize | sf::Style::Close, sf::State::Windowed);
    }

    else
        this->window = new sf::RenderWindow(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Resize | sf::Style::Close, sf::State::Windowed);
    //   assert(this->gfxsettings->resolution.isValid());

    // this->window1->create(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Titlebar, this->gfxsettings->windowSettings);

    this->window->setFramerateLimit(this->gfxsettings->framerate_limit);
    // this->window1->setVerticalSyncEnabled(this->gfxsettings.vsync);

    // ImGui::CreateContext();
    //  ImGui::ShowDemoWindow();
    if (ImGui::SFML::Init(*this->window)) {
        std::cout << "Imgui SFML was initalized " << std::endl;
        // this->states.top()->log("ImGui has properly been initalized", "Main");
        // LOG(INFO)<< "initalized imgui";
    }

    this->initWindowIcon();
}

void Game::initGTK()
{
}
void Game::initStateData()
{
    this->state_data.window = this->window;
    this->state_data.gfxsettings = this->gfxsettings;
    this->state_data.supportedKeys = &this->supported_keys;
    this->state_data.states = &this->states;
    this->state_data.gridSize = this->gridSize;

    if (this->state_data.window == nullptr) {
        // LOG(INFO) << "Unable to initalize Window info into State data";
    }

    if (this->state_data.gfxsettings == NULL) {
        std::cout << "unable to initalize graphics settings state data" << "/n";
        // LOG(INFO) << "Unable to initalize Graphics Settings into State Data" << std::endl;
    } else {
        std::cout << this->state_data.gfxsettings->framerate_limit;
    }
    if (this->state_data.supportedKeys == nullptr) {
        std::cout << "unable to initalize graphics settings state data" << "/n";
        // LOG(INFO) << "Unable to initalize Keys into State Data";
    }
    if (this->state_data.states == nullptr) {
        std::cout << "unable to initalize graphics settings state data" << "/n";
        // LOG(INFO) << "Unable to initalize States into State Data";
    }
}

void Game::initWindowIcon()
{
    // sf::Image windowIMage(icon.width, icon.height, icon.data)
    this->window->setIcon(sf::Vector2u(icon.width, icon.height), icon.data);
}

void Game::resizeWindow()
{
}

void Game::setFullScreen()
{
}

void Game::log(const std::string& stat)
{
}

void Game::load()
{
}

void Game::Update()
{
    this->UpdateEvents();

    if (this->states.empty()) {
        this->endApplication();
        this->window->close();
    }
    // Application end
    else {
        if (this->window->hasFocus()) {

            // update stack final
            this->states.top()->update(this->dt);

            if (this->states.top()->getQuit()) {

                // LOG(INFO) << "Size of deque: " << this->states.size();

                // LOG(INFO) << "destroying state ";

                this->states.pop();
                // DO NOT attempt to delete items from the states stack here
                // popping them already frees the memory.
                // using delete this->states.top() here will only result in an GL_free error when it attempts to free a deref. pointer to a surface

                // DO NOT use this either:
                //  delete this->states.top();
                // it's better to just let .pop() do it's job properly and not introduce any more surface area for more issues in the future

                // LOG(INFO) << "top of deque: " << this->states.size();
            }
        }
    }
}

void Game::UpdateEvents()
{

    while (const std::optional event = this->window->pollEvent()) {
        ImGui::SFML::ProcessEvent(*this->window, *event);

        if (const auto* closed = event->getIf<sf::Event::Closed>()) {
            if (!this->states.empty()) {
                // LOG(INFO) << "destroying window...";
                this->window->close();
            }
        }
    }
}

void Game::render()
{

    this->window->clear(sf::Color(31, 31, 31, 255));

    this->window->pushGLStates();

    if (!this->states.empty())
        this->states.top()->render();

    ImGui::SFML::Render(*this->window);

    this->window->popGLStates();

    this->window->display();
}

void Game::UpdateDT()
{

    // Updates the time variable with the time taken for each frame to render

    this->dt = this->dtClock.restart().asSeconds();
    // std::cout << this->dt  << std::endl;
}

void Game::running()
{

    while (this->window->isOpen()) {

        this->UpdateDT();
        ImGui::SFML::Update(*this->window, this->ImGuiClock.restart());
        this->Update();
        this->render();
    }
    ImGui::SFML::Shutdown();

} // main loop

void Game::endApplication()
{
    if (!this->states.empty())

        ;
    std::cout << "no running states remaining, destroying window context..." << std::endl;
    // LOG(INFO) << "Ending the application...";
}

void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.f;
    this->gridSize = sf::Vector2f(32.f, 24.f);
}
