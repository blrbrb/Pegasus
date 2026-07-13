//
//  MainMenuState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/25/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "include/MainMenuState.hpp"

// Constructors and Destructors

MainMenuState::MainMenuState(StateData* state_data)
    : State(state_data)
{

    this->state_data = state_data;
    this->initvariables();
    this->initFonts();
    this->initkeybinds();
    this->resetGUI();


    // this->resetGUI();
}

MainMenuState::~MainMenuState()
{

    auto it = buttons.begin();
    for (it = buttons.begin(); it != this->buttons.end(); ++it)

    {
        delete it->second;

    }


}

// initalization functions

void MainMenuState::initvariables()
{
    this->name = "Menu";
    this->state_ID = this->states->size();
}


void MainMenuState::initkeybinds()
{

    std::ifstream ifs("Init/MenuState_Keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        // this->log<< "Attempting to Read MenuState Keybinds" << std::endl;

        while (ifs >> key >> key2) {
            // this->keyBinds[key] = this->supported_keys->at(key2);
            // this->log<< key << " " << key2 << std::endl;
        }
    }
    ifs.close();
}

void MainMenuState::initGUI()
{

    // const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    std::cout << "current window resolution " << this->state_data->gfxsettings->resolution.size.x << "x" << this->state_data->gfxsettings->resolution.size.x << std::endl;
    const sf::VideoMode& vm = sf::VideoMode::getDesktopMode();

    try {

        this->buttons["NEW GAME"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(7.14, vm), GUI::pixelpercentY(44, vm), &this->font, "New Map", GUI::calcCharSize(vm));
        this->buttons["EXIT"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(35.7, vm), GUI::pixelpercentY(44, vm), &this->font, "Exit", GUI::calcCharSize(vm));
        this->buttons["EDITOR"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(35.7, vm), GUI::pixelpercentY(60, vm), &this->font, "Editor", GUI::calcCharSize(vm));
        this->buttons["SETTINGS"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(7.14, vm), GUI::pixelpercentY(60, vm), &this->font, "Export Map", GUI::calcCharSize(vm));

    }

    catch (std::invalid_argument& e) {
        std::cout << e.what() << "/";

    }


}

void MainMenuState::resetGUI()
{
    /*!
           @brief clear all GUI elements

     */

    auto it = buttons.begin();
    for (it = buttons.begin(); it != this->buttons.end(); ++it)

    {
        delete it->second;
        // this->log<< "Buttons Deleted " << std::endl;
    }
    this->buttons.clear();

    this->initGUI();
}

void MainMenuState::initFonts()
{

    try {

        if (!this->font.openFromFile("Resources/Assets/Fonts/OpenSans-Variable.ttf")) {

            // LOG(WARNING) << "Unable to load font from Resources/Assets/Fonts/*";
            // LOG(FATAL) << "Throwing runtime exception on line 164...", "State::Menu";
            throw std::runtime_error("ERROR unable to load font file MainMenuState lin 144");
        }
    } catch (std::runtime_error& e) {

        // this->log("looking for fonts in " + std::filesystem::current_path(), "State::Menu");
        // this->font.loadFromFile("Resources/OpenSans-Variable.ttf")''
    }
}

void MainMenuState::initbackground()
{

    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

    this->background.setFillColor(sf::Color(31, 31, 31, 255));
}

// Update Functions

void MainMenuState::update(const float& dt)
{

    this->updateMousePosition();
    this->updateKeyTime(dt);


    this->updateInput(dt);

    this->updatebuttons(dt);
}

void MainMenuState::updateInput(const float& dt)
{
}



void MainMenuState::render(sf::RenderTarget* target)
{

    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderbuttons(*target);
}

void MainMenuState::renderbuttons(sf::RenderTarget& target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::updatebuttons(const float& dt)
{

    // this->log<< "updating buttons" << std::endl;
    for (auto& it : this->buttons)
    {

        it.second->update(this->MousePosWindow);
        // this->log<< it.second << std::endl;
    }

    if (this->buttons["NEW GAME"]->isPressed()) {

        this->states->push(new GameState(this->state_data));
    }


    //TD: Find workaround for https://www.reddit.com/r/sfml/comments/1poyl3p/sfml_button_clicks_trigger_automatically_on/
    // so that the window doesn't instantly close if the "exit" button was clicked on the main menu the last time the application was run
    // SFML for some reason continues to spam the sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) event even after a complete state reset with a fresh window
    if (this->buttons["EXIT"]->isPressed()) {
        // this->endState();
    }

    if (this->buttons["EDITOR"]->isPressed()) {
        this->states->push(new EditorState(this->state_data));
    }
    if (this->buttons["SETTINGS"]->isPressed() && this->getKeyTime()) {
        this->states->push(new SettingsState(this->state_data));
    }

}

void MainMenuState::reconfigure_log()
{
}
