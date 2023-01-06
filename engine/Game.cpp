//
//  Game.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 
#include "stdafx.h"
#include "Game.hpp"


INITIALIZE_EASYLOGGINGPP

Game::Game() {
    this->initlog(); 
    std::cout << std::filesystem::current_path().string() << std::endl;
    this->initVariables();
    this->initGraphicsSettings();
    this->initwindow();
    this->initkeys();
    this->initJoySticks();
    this->initstatedata();
    this->initstates(); 
    
  
    }


Game::~Game() {
    
    delete this -> window;
    
    
    while (!this->states.empty()) 
    {
       delete this->states.top();
        this->states.pop(); 
         LOG(INFO) << "deleting..." << " " << states.size() << " " << "in Game.cpp";
    } 
    

}

//initalizer functions

void Game::initkeys() {
    
/*!
 @brief  Load the supported input methods (keys,buttons, controllers etc) from the ini file and store them as shared class variables

 @param  void

 @return void


 
 
 
 
 
  */
    LOG(INFO) << "creating keybinds "; 
    
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

bool Game::initJoySticks()
{
   
    if (this->joystick.isConnected(0)) 
    {
        LOG(INFO) << "a joystick has been connected"; 
        return true;
    }
    else
    return false;
}

void Game::initstates() { 
    

    this->states.push(new MainMenuState(&this->state_data)); 
    
}

void Game::initlog()
{
    el::Configurations defaultConf;
    //defaultConf.setToDefault(); 
   // el::ConfigurationType::
   // defaultConf.parseFromText("*GLOBAL:\n FORMAT =  \n FILENAME = Pegasus.log\n ENABLED = true\nTO_FILE = true\nTO_STANDARD_OUTPUT = true\nSUBSECOND_PRECISION = 6\nPERFORMANCE_TRACKING = true\nMAX_LOG_FILE_SIZE = 16777216\nLOG_FLUSH_THRESHOLD = 300");
     //el::Loggers::reconfigureLogger("Pegasus", defaultConf);
    // el::Configureation
    defaultConf.setGlobally(el::ConfigurationType::Filename, "Pegasus.log");
   // defualtConf.set
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime %thread_name %msg");
   
   // defaultConf.set(el::ConfigurationType::)
    //defaultConf.set(el::Level::Info,
     //   el::ConfigurationType::Format, "%datetime %level %msg");

    //defaultConf.setGlobally(el::ConfigurationType::Filename, "Pegasus.log"); 
    el::Loggers::reconfigureLogger("Pegasus", defaultConf);
    el::Loggers::reconfigureAllLoggers(defaultConf);
    el::Helpers::setThreadName("main"); 
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
       // this->window = new sf::RenderWindow(); 
        this->window = new sf::RenderWindow(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Fullscreen, this->gfxsettings->windowSettings);
    }


    else
        this->window = new sf::RenderWindow(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Titlebar, this->gfxsettings->windowSettings);
     //   assert(this->gfxsettings->resolution.isValid());
  
       // this->window->create(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Titlebar, this->gfxsettings->windowSettings);
 
        
   this->window->setFramerateLimit(this->gfxsettings->framerate_limit);
   // this->window->setVerticalSyncEnabled(this->gfxsettings.vsync);       

 

    sf::RenderWindow& window = *this->window;   
    assert(window.isOpen()); 
    window.setActive(true);
    
    //ImGui::CreateContext();
    //ImGui::ShowDemoWindow();
    if (ImGui::SFML::Init(window)) 
    {
      // this->states.top()->log("ImGui has properly been initalized", "Main");
       LOG(INFO)<< "initalized imgui";
    } 

    ///ImGui::StyleColorsDark();
   // ImGui::SetCurrentContext()
    //ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    this->initWindowIcon(); 
}

void Game::initstatedata()
{
   
   
    this->state_data.window = this->window;
    this->state_data.gfxsettings = this->gfxsettings; 
    this->state_data.supportedkeys = &this->supportedkeys;
    this->state_data.states = &this->states;
    this->state_data.gridsize = &this->gridsize; 
    this->state_data.music = new Sound::MusicPlayer(); 
 
    if (this->state_data.window == NULL) 
    {
        LOG(INFO) << "Unable to initalize Window info into State data";
    }

    if (this->state_data.gfxsettings == NULL) 
    {
        LOG(INFO) << "Unable to initalize Graphics Settings into State Data" << std::endl;

    }
    if (this->state_data.supportedkeys == NULL)
    {
       LOG(INFO) << "Unable to initalize Keys into State Data";

    }
    if (this->state_data.states == NULL)
    {
        LOG(INFO) << "Unable to initalize States into State Data";
    }
    if (this->state_data.gridsize == NULL)
    {
        LOG(INFO) << "Unable to initalize gridsize into Statedata";
    }

    
}

void Game::initWindowIcon()
{
   
    this->window->setIcon(icon.width, icon.height, icon.data);
}






void Game::resizewindow()
{


    
}

void Game::setfullscreen()
{





}

void Game::log(std::string stat)
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
                    LOG(INFO) << "Size of deque: " << this->states.size(); 
                   
                    LOG(INFO) << "destroying state ";     
                    
                    this->states.top()->endstate();
                   
                   // delete this->states.top();
                    delete this->states.top();
                     this->states.pop();
                     LOG(INFO) << "top of deque: " << this->states.size();
               
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
                LOG(INFO) << "destroying window...";
                this->window->close();
            }
        }      

        ImGui::SFML::ProcessEvent(this->event); 
        
       
    }
}

void Game::render() {
 
    this->window->clear(sf::Color::Black); 
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
    LOG(INFO) << "Ending the application..."; 
}

void Game::initVariables()
{
    this->window = NULL;
    this->dt = 0.f;

    this->gridsize = sf::Vector2f(32.f, 24.f);


}
