//
//  MainMenuState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/25/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#
#include "MainMenuState.hpp"




//Constructors and Destructors

MainMenuState::MainMenuState(StateData* state_data)
: State(state_data) {
    
   
        this->state_data = state_data;  
        this->initvariables();
        this->initFonts();
        this->initkeybinds();
        this->initGUI();
        this->setmusic();

        //this->resetGUI();  
        
     
}

MainMenuState::~MainMenuState() {
    
    auto it = buttons.begin();
     for (it = buttons.begin(); it != this->buttons.end(); ++it)
    
     {
         delete it->second; 
        // this->log<< " MainMenu State Buttons Deleted" << std::endl; 
         
     }
    
     this->state_data->music->stop();
    
}




//initalization functions

void MainMenuState::initvariables()
{
    this->name = "Menu"; 
    this->state_ID = this->states->size(); 
    
}

void MainMenuState::setmusic()
{
    //this->state_data->music->update(dt);
    this->state_data->music->play(0);
    this->state_data->music->set_volume(1.f);
}




void MainMenuState::initkeybinds() {
  
   std::ifstream ifs("Init/MenuState_Keys.ini"); 

   

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = ""; 
       // this->log<< "Attempting to Read MenuState Keybinds" << std::endl; 

        while (ifs >> key >> key2)
        {
          // this->keybinds[key] = this->supportedkeys->at(key2);
          // this->log<< key << " " << key2 << std::endl; 
        }
        
    } 
    ifs.close(); 
    



 }

void MainMenuState::initGUI() {
    
  const sf::VideoMode& vm = this->state_data->gfxsettings->resolution; 
  std::cout << "current window resolution " << this->state_data->gfxsettings->resolution.width << "x" << this->state_data->gfxsettings->resolution.width << std::endl;
  //const sf::VideoMode& vm = sf::VideoMode::getDesktopMode(); 


  try {

      this->buttons["NEW GAME"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(7.14, vm), GUI::pixelpercentY(44, vm), &this->font, "New Game", GUI::calcCharSize(vm));

      this->buttons["EXIT"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(35.7, vm), GUI::pixelpercentY(44, vm), &this->font, "Exit", GUI::calcCharSize(vm));

      this->buttons["EDITOR"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(35.7, vm), GUI::pixelpercentY(60, vm), &this->font, "Editor", GUI::calcCharSize(vm));
      this->buttons["SETTINGS"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(7.14, vm), GUI::pixelpercentY(60, vm), &this->font, "Settings", GUI::calcCharSize(vm));
      this->buttons["CHARACTER_EDITOR"] = new GUI::Button(GUI::pixelpercentX(55.1, vm), GUI::pixelpercentY(9.f, vm), GUI::pixelpercentX(24.2, vm), GUI::pixelpercentY(76, vm), &this->font, "Character Editor", GUI::calcCharSize(vm));
      this->buttons["Info"] = new GUI::Button(GUI::pixelpercentX(3.5, vm), GUI::pixelpercentY(3.5, vm), GUI::pixelpercentX(64.2, vm), GUI::pixelpercentY(20, vm), &this->font, "Info", GUI::calcCharSize(vm));
  } 

  catch (std::invalid_argument& e) 
  {
      //this->log("Unhandled exception: MainMenuState 120 " + std::string(e.what()), "State::Menu");

  
  }
   
    
  //this->log<< this->buttons.size() << std::endl; 
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
            //this->log<< "Buttons Deleted " << std::endl; 
            
        }
    this->buttons.clear();
    
    this->initGUI(); 
}



void MainMenuState::initFonts() {



  

    try
    {

        if (!this->font.loadFromFile("Resources/Assets/Fonts/PressStart2P.ttf"))
        {
          
            LOG(WARNING) << "Unable to load font from Resources/Assets/Fonts/*"; 
            LOG(FATAL) << "Throwing runtime exception on line 164...", "State::Menu"; 
            throw std::runtime_error("ERROR unable to load font file MainMenuState lin 144");
        }
    }
        catch (std::runtime_error& e) {
            
           // this->log("looking for fonts in " + std::filesystem::current_path(), "State::Menu");
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
   
    this->updatebuttons(dt);
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

void MainMenuState::updatebuttons(const float& dt) {
    
    //this->log<< "updating buttons" << std::endl; 
    for (auto &it : this->buttons)
   
    {
        it.second->update(this->MousePosWindow);
       // this->log<< it.second << std::endl; 
        
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
        this->log("Creating EditorState", "State::Menu");
        
    }
    if (this->buttons["SETTINGS"]->isPressed())
    {
        this->states->push(new SettingsState(this->state_data));
      
    } 

    if (this->buttons["SETTINGS"]->isPressed())
    {
        this->states->push(new SettingsState(this->state_data));

    }
   
    
}

void MainMenuState::reconfigure_log()
{
}




