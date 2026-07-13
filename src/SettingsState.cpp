//
//  SettingsState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include <SFML/Window/WindowEnums.hpp>
#
#include "include/SettingsState.hpp"

// Private Functions

void SettingsState::initvariables()
{
    // sthis->current_item = NULL;
    this->selection_temp = "";

    std::vector video_modes = sf::VideoMode::getFullscreenModes();
    for (auto& i : video_modes) {
        // std::cout << std::to_string(i.width) + 'x' + std::to_string(i.height) << std::endl;
        this->modes[std::to_string(i.size.x) + 'x' + std::to_string(i.size.y)] = i;
    }


    this->tutorial_text = new sf::Text(this->font);
    this->tutorial_text->setCharacterSize(GUI::calcCharSize(this->state_data->gfxsettings->resolution,200));
    this->tutorial_text->setFillColor(sf::Color::White);
   // this->tutorial_text->setPosition({100.f, 100.f});
   this->tutorial_text->setPosition({GUI::pixelpercentX(1.f,this->state_data->gfxsettings->resolution) ,0.f});
    this->tutorial_text->setString("Go to https://www.pony.town");
}

void SettingsState::initview()
{

    this->view.setSize(sf::Vector2f(this->state_data->gfxsettings->resolution.size.x, this->state_data->gfxsettings->resolution.size.x));
}

void SettingsState::initkeybinds()
{

    std::ifstream ifs("SettingsState_Keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void SettingsState::initGUI()
{

    sf::VideoMode& vm = this->state_data->gfxsettings->resolution;

    this->buttons["RESOLUTION"] = new GUI::Button(GUI::pixelpercentX(20.f, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(5.f, vm), GUI::pixelpercentY(50.f, vm), &this->font, "Import Character", GUI::calcCharSize(vm));

    this->buttons["EXIT"] = new GUI::Button(GUI::pixelpercentX(20.f, vm), GUI::pixelpercentY(10.f, vm), GUI::pixelpercentX(5.f, vm), GUI::pixelpercentY(75.f, vm),&this->font, "Exit", GUI::calcCharSize(vm));

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.size.x), static_cast<float>(vm.size.y)));

    this->background.setTexture(&this->backgroundTexture);

    std::vector<std::string> modes_str;

    for (auto& i : this->modes) {
        std::cout << i.second.size.x << "x" << i.second.size.y << std::endl;
        modes_str.push_back(static_cast<std::string>(std::to_string(i.second.size.x) + 'x' + std::to_string(i.second.size.y)));
    }
}

void SettingsState::resetGUI()
{
}

void SettingsState::initFonts()
{

    if (!this->font.openFromFile("Resources/Assets/Fonts/OpenSans-Variable.ttf")) {
        // LOG(WARNING) << "unable to load default font";
        // LOG(FATAL) << "throwing runtime exception on line 104";
        throw std::runtime_error("ERROR CODE 05: SettingsState::initFonts COULD NOT LOAD FONT FROM FILE");
    }
}

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
{
    try {
        this->initFonts();
         this->initvariables();
        this->initkeybinds();
        this->initGUI();

    }

    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

SettingsState::~SettingsState()
{
    auto it2 = dropdownlists.begin();
    for (it2 = dropdownlists.begin(); it2 != this->dropdownlists.end(); ++it2)

    {
        delete it2->second;
    }
}

// Functions
void SettingsState::update(const float& dt)
{
    this->updateKeyTime(dt);
    this->updateView();
    this->updateMousePosition();
    this->updateInput(dt);

    this->updateGUI(dt);
}

void SettingsState::updateInput(const float& dt)
{
  if(this->buttons["EXIT"]->isPressed() && this->getKeyTime())
  {
    this->endState();
  }
}



void SettingsState::render(sf::RenderTarget* target)
{

    if (!target)
        target = this->window;

    target->setView(this->view);
    // target->draw(this->background);

    this->renderGUI(*target);
}

void SettingsState::renderGUI(sf::RenderTarget& target)
{

    for (auto& it : this->buttons) {
        it.second->render(target);
    }

    target.draw(*this->tutorial_text);
}

void SettingsState::updateevents()
{
}

void SettingsState::updateGUI(const float& dt)
{

    for (auto& it : this->buttons) {
        it.second->update(this->MousePosWindow);
    }
}

void SettingsState::updateView()
{
   // this->view.setSize(sf::Vector2f(GUI::calcCharSize(this->state_data->gfxsettings->resolution, 2), GUI::calcCharSize(this->state_data->gfxsettings->resolution, 2)));
}
