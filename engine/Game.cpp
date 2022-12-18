//
//  Game.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 
#include "stdafx.h"
#include "Game.hpp"
#include "../stdafx.h"

Game::Game() {
    
    std::cout << "init game" << std::endl; 
    this->initVariables();
    this->initGraphicsSettings();
    this->initwindow();
    this->initkeys();
    this->initstatedata();
    this->initstates(); 
    
  
    }


Game::~Game() {
    
    delete this -> window;
    
    
    while (!this->states.empty()) 
    {
       delete this->states.top();
        this->states.pop(); 
        std::cout << "deleting..." << " " << states.size() << " " << "in Game.cpp" << std::endl;
    } 
    

}

//initalizer functions

void Game::initkeys() {
    
/*!
 @brief  Load the supported input methods (keys,buttons, controllers etc) from the ini file and store them as shared class variables

 @param  void

 @return void


 
 
 
 
 
  */
   std::ifstream ifs("Init/Supported_Keys.ini");

   if (ifs.is_open())
   {
       std::string key = "";
       int key_value = 0;
       
       while (ifs >> key >> key_value)
       {
           this->supportedkeys[key] = key_value;
           //std::cout << "Game.cpp supported Keys are As Follows:" << " " << this->supportedkeys.at(key) << std::endl;
           
       }
      
   }
  
   ifs.close(); 
 

    
    
}

void Game::initstates() { 
    

    this->states.push(new MainMenuState(&this->state_data)); 
    
}


void Game::initGraphicsSettings() {
    
    this->gfxsettings = new GraphicsSettings(); 
    this->gfxsettings->loadfromfile("Config/Window.cfg");
    
  
}

void Game::initwindow() {

    /*!
     @brief  Initalizes the media layer the application runs on

     @param   void

     @return  void

    */

    ImGui::CreateContext();
   

    if (this->gfxsettings->fullscreen) {
        //it might be a good idea to assign the hanging window pointer a value, and then use the newer .create method
        this->window = new sf::RenderWindow(); 
        this->window = new sf::RenderWindow(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Fullscreen, this->gfxsettings->windowSettings);
    }


    else
        this->window = new sf::RenderWindow(); 
        assert(this->gfxsettings->resolution.isValid());
  
        this->window->create(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Titlebar, this->gfxsettings->windowSettings);
 
        
   this->window->setFramerateLimit(this->gfxsettings->framerate_limit);
   // this->window->setVerticalSyncEnabled(this->gfxsettings.vsync);       

 

    sf::RenderWindow& window = *this->window;   
  
 
    //ImGui::CreateContext();
    //ImGui::ShowDemoWindow();
    if (ImGui::SFML::Init(window)) 
    {
      // this->states.top()->log("ImGui has properly been initalized", "Main");
        std::cout << "initalized imgui" << std::endl;
    }

    ///ImGui::StyleColorsDark();
   // ImGui::SetCurrentContext()
    //ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    
}

void Game::initstatedata()
{
    this->state_data.window = this->window;
    this->state_data.gfxsettings = this->gfxsettings; 
    this->state_data.supportedkeys = &this->supportedkeys;
    this->state_data.states = &this->states;
    this->state_data.gridsize = &this->gridsize; 
   


    if (this->state_data.window == NULL) 
    {
        std::cout << "Unable to initalize Window info into State data" << std::endl; 
    }

    if (this->state_data.gfxsettings == NULL) 
    {
        std::cout << "Unable to initalize Graphics Settings into State Data" << std::endl; 

    }
    if (this->state_data.supportedkeys == NULL)
    {
        std::cout << "Unable to initalize Keys into State Data" << std::endl; 

    }
    if (this->state_data.states == NULL)
    {
        std::cout << "Unable to initalize States into State Data" << std::endl;
    }
    if (this->state_data.gridsize == NULL)
    {
        std::cout << "Unable to initalize gridsize into Statedata" << std::endl;
    }

    
}





void Game::resizewindow()
{

    
}



void Game::load()
{
    
       
}



void Game::Update()
{
    this->UpdateEvents();
    
    
    if (!this->states.empty())
        {
            if (this->window->hasFocus())
            {
                this->states.top()->update(this->dt);

                if (this->states.top()->getquit())
                {
                    this->states.top()->endstate();
                   
                    delete this->states.top();
                    
                    this->states.pop();
               
                }
            }
        }
        //Application end
        else
        {
            this->endapplication();
            this->window->close();
        }
    }




void Game::UpdateEvents() {
    
    while (this->window->pollEvent(this->event))
    {
        
        if (this->event.type == sf::Event::Closed) {
            if (!this->states.empty()) 
            {
                this->states.top()->log("destroying window...", "Main");
                this->window->close();
            }
        }      

        ImGui::SFML::ProcessEvent(this->event); 
        
       
    }
}

void Game::render() {
 
    this->window->clear(sf::Color::Black); 
   
    if (!this->states.empty())
     
       


         this->states.top()->render(); 
        
    ImGui::SFML::Render(*this->window);
  
   this->window->display();  
                                                       
    
  }
        
void Game::UpdateDT()
{
    
   // Updates the time variable with the time taken for each frame to render
  


    
    this-> dt = this -> dtClock.restart().asSeconds();
    //std::cout << this->dt  << std::endl;
   
   
}


void Game::running() {
    
    while (this->window->isOpen()) {
      
        ImGui::SFML::Update(*this->window, this->ImGuiClock.restart());
       // ImGui::End(); 
        this->UpdateDT();
        this->Update();
         this->render();
    }
    ImGui::SFML::Shutdown();
    
} //main loop

void Game::endapplication()
{
    if(this->states.size() > 0)
    this->states.top()->log("Ending the application...", "Main"); 
}


void Game::initVariables()
{
    this->window = NULL;
    this-> dt = 0.f;

    this->gridsize = sf::Vector2f(32.f, 24.f);
    //This is the size of the stolen ponytown assets 
    //I am a shameless pirate.qweqweqweqeqweqweqweqweqeqweqwe
    //this->GridSizeIrr = asdasdasdasdasdasdasdsad

    
}







