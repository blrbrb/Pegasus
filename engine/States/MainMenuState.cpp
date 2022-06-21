//
//  MainMenuState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/25/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "stdafx.h"
#include "MainMenuState.hpp"



//Constructors and Destructors

MainMenuState::MainMenuState(StateData* state_data)
: State(state_data) {
    
    std::cout << this->state_data; 
        this->state_data = state_data;  
        this->initvariables();
        this->initFonts();
        this->initkeybinds();
        this->initGUI();
        //this->resetGUI();  
        
     
}

MainMenuState::~MainMenuState() {
    
    auto it = buttons.begin();
     for (it = buttons.begin(); it != this->buttons.end(); ++it)
    
     {
         delete it->second; 
         std::cout << " MainMenu State Buttons Deleted" << std::endl; 
         
     }
    
}




//initalization functions

void MainMenuState::initvariables()
{
  
}


void MainMenuState::initkeybinds() {
  
   std::ifstream ifs("Init/MenuState_Keys.ini"); 

   

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = ""; 
        std::cout << "Attempting to Read MenuState Keybinds" << std::endl; 

        while (ifs >> key >> key2)
        {
          // this->keybinds[key] = this->supportedkeys->at(key2);
          // std::cout << key << " " << key2 << std::endl; 
        }
        
    } 
    ifs.close(); 
    



 }

void MainMenuState::initGUI() {
    
  const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
  //const sf::VideoMode& vm = sf::VideoMode::getDesktopMode(); 


  try {

      this->buttons["NEW GAME"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(7.14, vm), GUI::pixelpercentY(44, vm), &this->font, "New Game", GUI::calcCharSize(vm), "Resources/GUI/Buttons/red_button01.png", "Resources/GUI/Buttons/red_button02.png", "Resources/GUI/Buttons/red_button00.png");

      this->buttons["EXIT"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(35.7, vm), GUI::pixelpercentY(44, vm), &this->font, "Exit", GUI::calcCharSize(vm), "Resources/GUI/Buttons/red_button01.png", "Resources/GUI/Buttons/red_button02.png", "Resources/GUI/Buttons/red_button00.png");

      this->buttons["EDITOR"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(35.7, vm), GUI::pixelpercentY(60, vm), &this->font, "Editor", GUI::calcCharSize(vm), "Resources/GUI/Buttons/red_button01.png", "Resources/GUI/Buttons/red_button02.png", "Resources/GUI/Buttons/red_button00.png");
      this->buttons["SETTINGS"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(7.14, vm), GUI::pixelpercentY(60, vm), &this->font, "Settings", GUI::calcCharSize(vm), "Resources/GUI/Buttons/red_button01.png", "Resources/GUI/Buttons/red_button02.png", "Resources/GUI/Buttons/red_button00.png");

      this->buttons["Info"] = new GUI::Button(GUI::pixelpercentX(3.5, vm), GUI::pixelpercentY(3.5, vm), GUI::pixelpercentX(64.2, vm), GUI::pixelpercentY(20, vm), &this->font, "Info", GUI::calcCharSize(vm), "Resources/GUI/Buttons/red_button06.png", "Resources/GUI/Buttons/red_button07.png", "Resources/GUI/Buttons/red_button06.png");
  } 

  catch (std::invalid_argument& e) 
  {
      std::cout << e.what() << std::endl; 

  
  }
   
    
  std::cout << this->buttons.size() << std::endl; 
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
            std::cout << "Buttons Deleted " << std::endl; 
            
        }
    this->buttons.clear();
    
    this->initGUI(); 
}


void MainMenuState::initFonts() {



  

    try
    {

        if (!this->font.loadFromFile("Resources/Fonts/PressStart2P.ttf"))
        {
            std::cout << "Font Not loading" << std::endl;

            std::cout << "ERROR CODE 07: MainMenuState::initFonts COULD NOT LOAD FONT FROM FILE" << std::endl;
            throw std::runtime_error("ERROR CODE 07: MainMenuState::initFonts COULD NOT LOAD FONT FROM FILE");
        }
    }
        catch (std::runtime_error& e) {
            
            std::cout << std::filesystem::current_path() << std::endl;
            // this->font.loadFromFile("Resources/PressStart2p.ttf")''
        }
    
    
    

        
    }

   



void MainMenuState::initbackground()
{

    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
  
  
    
    
   // this->background.setTexture(&this->backgroundTexture);
    this->background.setFillColor(sf::Color::Black);

}

//Update Functions

void MainMenuState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateInput(dt);
   
    this->updatebuttons();
}

void MainMenuState::updateInput(const float& dt)
{

    
    
}

//Render Functions 

void MainMenuState::render(sf::RenderTarget* target)
{
    
    if (!target)
        target = this->window;
    
    

    
   target->draw(this->background);
   
    
    //sf::Text mouseText;
    //mouseText.setPosition(this->MousePosView.x, this->MousePosView.y - 50);
    //mouseText.setFont(this->font);
    //mouseText.setCharacterSize(12);
 
    //std::stringstream Position;
    //Position << this->MousePosView.x << " " << this->MousePosView.y;
    //mouseText.setString(Position.str());
    
  //  target->draw(mouseText);
   this->renderbuttons(*target);
    
}


void MainMenuState::renderbuttons(sf::RenderTarget& target)
{
    for (auto &it : this->buttons)
       {  
           it.second->render(target);
          
       }
}

void MainMenuState::updatebuttons() {
    
    std::cout << "updating buttons" << std::endl; 
    for (auto &it : this->buttons)
   
    {
        it.second->update(this->MousePosWindow);
        std::cout << it.second << std::endl; 
        
    }



    if (this->buttons["NEW GAME"]->isPressed())
    {
        this->states->push(new GameState(this->state_data));
    }


    //Exit the game
    if(this->buttons["EXIT"]->isPressed())
    {
        this->endstate();
        
    }
    
    
    if (this->buttons["EDITOR"]->isPressed())
    {
        this->states->push(new EditorState(this->state_data)); 
        std::cout << "Creating EditorState... from Mainmenustate.cpp" << std::endl; 
        
    }
    if (this->buttons["SETTINGS"]->isPressed())
    {
        this->states->push(new SettingsState(this->state_data));
      
    }
   
    
}



