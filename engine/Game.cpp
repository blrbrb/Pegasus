//
//  Game.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 
#include "stdafx.h"
#include "Game.hpp"

Game::Game() {
    
    std::cout << "init game" << std::endl; 
    this->initVariables();
    this->initwindow();
    this->initGraphicsSettings();
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
    
    this->gfxsettings.loadfromfile("Init/Window.ini"); 
    
  
}

void Game::initwindow() {

    /*!
     @brief  Initalizes the media layer the application runs on

     @param   void

     @return  void

    */


   

    if (this->gfxsettings.fullscreen) {
        this->window = new sf::RenderWindow(this->gfxsettings.resolution, this->gfxsettings.title, sf::Style::Fullscreen, this->gfxsettings.windowSettings);
    }

   
     else
        this->window = new sf::RenderWindow(this->gfxsettings.resolution, this->gfxsettings.title, sf::Style::Resize | sf::Style::Close);
        
      
        
   this->window->setFramerateLimit(this->gfxsettings.framerate_limit);
    this->window->setVerticalSyncEnabled(this->gfxsettings.vsync);    


    std::cout << "window created" << std::endl; 
    //ImGui::CreateContext();
    //ImGui::ShowDemoWindow();
  

    ///ImGui::StyleColorsDark();
   // ImGui::SetCurrentContext()
    //ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    
}

void Game::initstatedata()
{
    this->state_data.window = this->window;
    this->state_data.gfxsettings = &this->gfxsettings; 
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
                    std::cout << "Main Loop. State Deleted. Game.cpp" << std::endl; 
                   
                    
               
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
            
            this->window->close();
                   
        }      
        //if (!this->states.empty())
           // this->states.top()->updateevents(&this->event);
       
    }
}

void Game::render() {
    
    this->window->clear(sf::Color::Black); 
    //ImGui::NewFrame();
    if (!this->states.empty()) 
        //OnImGui();
   
         this->states.top()->render();
    
  
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
      
        this->UpdateDT();
        this->Update();
         this->render();
    }
    
} //main loop

void Game::endapplication()
{
    std::cout << "Ending the application..." << std::endl;
}


void Game::initVariables()
{
    this->window = NULL;
    this-> dt = 0.f;

    this->gridsize = sf::Vector2f(32.f, 24.f);
    //This is the size of the stolen ponytown assets 
    //I am a shameless pirate.
    //this->GridSizeIrr = 

    
}






