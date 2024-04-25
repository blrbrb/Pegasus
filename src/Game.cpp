//
//  Game.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#include "include/game.hpp"


//INITIALIZE_EASYLOGGINGPP

Game::Game() {
     
    std::cout << std::filesystem::current_path().string() << std::endl;
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initJoySticks();
    this->initStateData();
    this->initStates();
    
    }


Game::~Game() {
    
    delete this -> window;
    
    
    while (!this->states.empty()) 
    {
       delete this->states.top();
        this->states.pop(); 
         //LOG(INFO) << "deleting..." << " " << states.size() << " " << "in Game.cpp";
    } 
    

}

//initalizer functions

void Game::initKeys() {
    
/*!
 @brief  Load the supported input methods (keys,buttons, controllers etc) from the ini file and store them as shared class variables

 @param  void

 @return void


 
 
 
 
 
  */
   // LOG(INFO) << "creating keyBinds ";
    
   std::ifstream ifs("Init/Supported_Keys.ini");

   if (ifs.is_open())
   {
       std::string key = "";
       int key_value = 0;
       
       while (ifs >> key >> key_value)
       {
           this->supported_keys[key] = key_value;
           //std::cout << "Game.cpp supported Keys are As Follows:" << " " << this->supported_keys.at(key) << std::endl;
           
       }
      
   }
  
   ifs.close(); 
 

    
    
}

bool Game::initJoySticks()
{

    if (this->joystick.isConnected(0)) 
    {
    
        return true;
    }
    else
    return false;
}

void Game::initStates() {
    

    this->states.push(new MainMenuState(&this->state_data)); 
    
}



void Game::initGraphicsSettings() {
    
    this->gfxsettings = new GraphicsSettings();

    this->gfxsettings->loadFromFile("Config/Window.cfg");
    
  
}

void Game::initWindow() {

    /*!
     @brief  Initalizes the media layer the application runs on

     @param   void

     @return  void

    */

    ImGui::CreateContext();
   

    if (this->gfxsettings->fullscreen) {
        //it might be a good idea to assign the hanging window1 pointer a value, and then use the newer .create method
       // this->window1 = new sf::RenderWindow();
        this->window = new sf::RenderWindow(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Fullscreen, this->gfxsettings->windowSettings);
    }


    else
        this->window = new sf::RenderWindow(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Titlebar, this->gfxsettings->windowSettings);
     //   assert(this->gfxsettings->resolution.isValid());
  
       // this->window1->create(this->gfxsettings->resolution, this->gfxsettings->title, sf::Style::Titlebar, this->gfxsettings->windowSettings);


   this->window->setFramerateLimit(this->gfxsettings->framerate_limit);
   // this->window1->setVerticalSyncEnabled(this->gfxsettings.vsync);

 

    sf::RenderWindow& window1 = *this->window;
    assert(window1.isOpen());
    window1.setActive(true);
    
    //ImGui::CreateContext();
    //ImGui::ShowDemoWindow();
    if (ImGui::SFML::Init(window1))
    {
      // this->states.top()->log("ImGui has properly been initalized", "Main");
      //LOG(INFO)<< "initalized imgui";
    } 

    ///ImGui::StyleColorsDark();
   // ImGui::SetCurrentContext()
    //ImGui_ImplGlfw_InitForOpenGL(this->window1, true);
    this->initWindowIcon(); 
}

void Game::initStateData()
{
    this->state_data.window = this->window;
    this->state_data.gfxsettings = this->gfxsettings; 
    this->state_data.supportedKeys = &this->supported_keys;
    this->state_data.states = &this->states;
    this->state_data.gridSize = &this->gridSize;
    
    if (this->state_data.window == nullptr)
    {
       // LOG(INFO) << "Unable to initalize Window info into State data";
    }

    if (this->state_data.gfxsettings == NULL) 
    {
        //LOG(INFO) << "Unable to initalize Graphics Settings into State Data" << std::endl;

    }
    if (this->state_data.supportedKeys == nullptr)
    {
      // LOG(INFO) << "Unable to initalize Keys into State Data";

    }
    if (this->state_data.states == nullptr)
    {
        //LOG(INFO) << "Unable to initalize States into State Data";
    }
    if (this->state_data.gridSize == nullptr)
    {
      //  LOG(INFO) << "Unable to initalize gridSize into Statedata";
    }

    
}

void Game::initWindowIcon()
{
   
    this->window->setIcon(icon.width, icon.height, icon.data);
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
    
    
    if (!this->states.empty())
        {
            if (this->window->hasFocus())
            {
                this->states.top()->update(this->dt);

                if (this->states.top()->getQuit())
                {
                   // LOG(INFO) << "Size of deque: " << this->states.size(); 
                   
                    //LOG(INFO) << "destroying state ";     

                    this->states.top()->endState();
                   
                   // delete this->states.top();
                    delete this->states.top();
                     this->states.pop();
                    // LOG(INFO) << "top of deque: " << this->states.size();
               
                }
            }
        }
        //Application end
        else
        {
            this->endApplication();
            this->window->close();
        }
    }




void Game::UpdateEvents() {
    
    while (this->window->pollEvent(this->event))
    {
        
        if (this->event.type == sf::Event::Closed) {
            if (!this->states.empty()) 
            {
                //LOG(INFO) << "destroying window...";
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

void Game::endApplication()
{
    if(!this->states.empty());
    std::cout << "no running states remaining, destroying window context..." << std::endl;
    //LOG(INFO) << "Ending the application..."; 
}

void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.f;
    this->gridSize = sf::Vector2f(32.f, 24.f);


}
