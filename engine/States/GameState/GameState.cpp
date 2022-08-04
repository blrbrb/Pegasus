//
//  GameState.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .

#include "stdafx.h"
#include "GameState.hpp"


GameState::GameState(StateData* state_data)
: State(state_data)
{
    try
    {
        this->initvariables();
        this->initdeferedrender();
        this->initview();
        this->initkeybinds();
        this->initfonts();
        this->inittextures();
        this->initpausemenu();
        this->initshaders();
        this->initplayers();
        this->initplayerGUI();
        this->initenemysystem();
        this->inittilemap();
        this->initdialougesystem();
        
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl; 
        std::cerr << e.what() << std::endl;  


        //this->handlefonts(); 
       // this->handletilemap(); 
    
  
    }
    
     //this->activEnemies.push_back(new Blrb(500.f, 800.f,this->textures["ENEMY_SHEET"]));
     //this->activEnemies.push_back(new Blrb(100.f, 300.f, this->textures["ENEMY_SHEET"]));
 
}

GameState::~GameState()
{
    
    delete this->player;
    delete this->pMenu;
    delete this->playerGUI;
    delete this->Tilemap;
    delete this->enemysystem;
   // delete this->dialougeSystem;
    
    for (size_t i = 0; i < this->activEnemies.size(); i++ )
    {
        delete this->activEnemies[i];
        
    }
    

}


void GameState::initvariables()
{ 
    
    this->shadertime = 0.f; 
    
}


void GameState::initdialougesystem()
{
    this->dialougeSystem = new DialougeSystem("Resources/Assets/Fonts/PressStart2P.ttf");
}

void GameState::initdeferedrender() {
     
    std::cout << "creating a new render texture with the size" << " " << this->state_data->gfxsettings->resolution.width << std::endl; 
    if(!this->rendertexture.create(this->state_data->gfxsettings->resolution.width,this->state_data->gfxsettings->resolution.height))
    {
        throw std::exception("unable to create rendertextrue GameState Line 78"); 
        
    }

    this->rendersprite.setTexture(this->rendertexture.getTexture());
   
    this->rendersprite.setTextureRect(
        sf::IntRect(
            0,
            0,
                    this->state_data->gfxsettings->resolution.width,
                    this->state_data->gfxsettings->resolution.height
        )
  
                                                                        );
    
  
}


void GameState::initworldbounds()
{
 
}




void GameState::initshaders()
{
    if(!this->core_shader.loadFromFile("Data/Shader/vertex_shader.vert", "Data/Shader/fragment_shader.frag"))
    { 
        std::cout << "unable to load core shaders in gamestate. Line 116" << std::endl; 
        throw std::exception("ERROR Unable to load shaders Gamestate line 71");
        
    }
    
 
    
}


void GameState::initview()
{
    
    this->view.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.F, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));

    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 2.f,static_cast<float>(this->state_data->gfxsettings->resolution.height) / 2.f));

    
    
}


void GameState::initkeybinds() {
  
    std::ifstream ifs("Init/GameState_Keys.ini", std::ifstream::in);

   
    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";
        //std::cout << "GAmestate Keybinds exist";
        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedkeys->at(key2);
           //std::cout << key << " " << key2;
        }
    }
    else {
        throw std::exception("ERROR unable to load GameState Keybinds GameState lin 145");
    }
            


      
      ifs.close();
  }

void GameState::initplayerGUI()
{
    this->playerGUI = new PlayerGUI(this->player, this->state_data->gfxsettings->resolution);
    
    
}


void GameState::inittextures()
{
    
    if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Assets/Entity/PlayerSheets/character_sheet3.png"))
    {
        std::cout << "ERROR Could not load Player Sheet texture GameState lin 168" << std::endl;
       
        throw std::exception("ERROR Could not load Player Sheet texture GameState lin 168");
    }
    
    if (!this->textures["ENEMY_SHEET"].loadFromFile("Resources/Assets/Entity/EnemySheets/Blrb.png"))
    {
        std::cout << "ERROR Could Not load Enemy Sheet textures GameState lin 171" << std::endl;
        
        throw std::exception("ERROR Could Not load Enemy Sheet textures GameState lin 175");
    } 


}

void GameState::initfonts()
{
    if (!this->font.loadFromFile("Resources/Assets/Fonts/PressStart2P.ttf"))
       {
           std::cout << "ERROR Could not load font from font file" << std::endl;
           throw std::exception("ERROR Could not load font from font file GameState lin 185");                           
       }
}



void GameState::initplayers()
{ 
    
    this->player = new Player(0,0, this->textures["PLAYER_SHEET"]);
    
}


void GameState::initgamestatedata()
{
    this->gamestatedata.keybinds = &this->keybinds;
    this->gamestatedata.font = &this->font;
    
}

void GameState::initpausemenu()
{
    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    
    this->pMenu = new PauseMenu(this->state_data->gfxsettings->resolution, this->font);
    
    this->pMenu->addbutton("Pause_Quit_Button",GUI::calcCharSize(vm),"Quit",GUI::pixelpercentX(13.f, vm), GUI::pixelpercentY(6.f, vm), 200.f);
    
    
}

void GameState::inittilemap()
{
    this->Tilemap = new TileMap(*this->state_data->gridsize, 100, 100, "Resources/Assets/Tiles/sheet.png");
  
    this->Tilemap->loadfromfile("Data/TileMap/text.slmp"); 

   
}




void GameState::update(const float& dt)
{
    this->updateShaders(dt); 
   
    srand(static_cast<unsigned>(time(NULL)));
    
    this->updateMousePosition(&this->view);
    this->updatekeytime(dt);
    this->updateInput(dt);
   
    if(!this->paused) //Update while unpaused 
     {
       
            this->updateView(dt);
            this->updatePlayerInput(dt);
            this->updatetilemap(dt);
            this->updatePlayer(dt); 
            
            this->updatePlayerGUI(dt);
            this->updateEnemies(dt);
            this->dialougeSystem->update(dt);
     }
    else // Update while Paused
     {
         this->pMenu->update(this->MousePosWindow);
         this->updatebuttons();  
         
         //ImGui::Text("Hello, world %d", 123);
         
          
         //ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
        // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
     }
         
     
    
}

void GameState::updateInput(const float& dt)
{
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getkeytime())
     {
         if (!this->paused)
             this->Pause_State();
         else
             this->Unpause_State();
     }
}

void GameState::updatetilemap(const float& dt)
{
    this->Tilemap->update(this->player, dt); 
    this->Tilemap->updateWorldBoundsCollision(this->player, dt);
    this->Tilemap->updateTileCollision(this->player, dt);
    this->Tilemap->updateTiles(this->player, dt, *this->enemysystem);
    
}




void GameState::updatebuttons()
{
    if(this->pMenu->isButtonPressed("Pause_Quit_Button"))
    {
        this->endstate();        
        this->endstate();        
    }
    

}

void GameState::updateView(const float &dt)
{
  
    
    
    this->view.setCenter(std::floor(this->player->getPosition().x + static_cast<float>(this->state_data->gfxsettings->resolution.width / 20)), std::floor(this->player->getPosition().y +                                                                        static_cast<float>(this->state_data->gfxsettings->resolution.height / 20)));
    
    
    
    if(this->Tilemap->getMaxSize().x >= this->view.getSize().x)
    {
        
        if(this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
        {
            this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
        
        else if(this->view.getCenter().x + this->view.getSize().x / 2.f > 10000.f)
        {
            this->view.setCenter(3000.f - this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
        
    }
    
    
    if(this->Tilemap->getMaxSize().y >= this->view.getSize().y)
    {
    
        if (this->view.getCenter().y - this->view.getSize().y / 2.f  < 0.f)
        {
            this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
        }
        
        else if (this->view.getCenter().y + this->view.getSize().y / 2.f > 10000.f)
        {
            this->view.setCenter(this->view.getCenter().x, 10000.f - this->view.getSize().y / 2.f);
        }
        
    }
    

    //Update the GridPosition view
    this->ViewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->state_data->gridsize->x);
    
    this->ViewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->state_data->gridsize->y);
}

void GameState::updateShaders(const float& dt)
{
  
    this->shadertime += dt /100;
    if (this->shadertime > 1) 
    {
        this->initvariables(); 
    }
   // std::cout << shadertime << std::endl; 
    this->core_shader.setUniform("time", shadertime);
   
}

void GameState::updatePlayerGUI(const float &dt)
{
    this->playerGUI->update(dt);   

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && this->getkeytime()) 
    {
       this->playerGUI->toggleCharacterTab(); 
    }
}

void GameState::updatePlayerInput(const float& dt)
{
   //check for a quit

    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(dt, 1.f, 0.f);
       // std::cout << "RIGHT" << std::endl;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) )
    {
        
        this->player->move(dt, -1.f, 0.f);
        //std::cout << "LEFT" << std::endl;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player->move(dt, 0.f, -1.f);
        //std::cout << "UP" << std::endl;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    {
        
        this->player->move(dt, 0.f, 1.f);
        //std::cout << "DOWN" << std::endl;
        this->dialougeSystem->addTextbox(DEFAULT_TAG); 

    }
    
    //hide the player's inventory 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && this->getkeytime())
    {
        this->playerGUI->HideInventory();
    }
    
   
}

void GameState::render(sf::RenderTarget* target) {
  

    //There is clearly a render layering issue here, the tilemap refuses to render at all. Possible causes: 
    //There's something fucky with the defered render 
    //there's something fucky with the actual renderSprite. 
    //There's something fucky with the order that the renders are being called, and assigned to the rendersprite. 
    //The rendertexture is broken. 
    if(!target)
        target = this->window;
    
    this->rendertexture.clear();

    
    
    this->rendertexture.setView(this->view); 
   
   // target->mapPixelToCoords(this->Tilemap->getMaxSizeGrid()); 
    this->Tilemap->render(this->rendertexture,this->view, this->ViewGridPosition, false, &this->core_shader);
    //this->Tilemap->render()
    //this->Tilemap->renderlighttile(this->rendertexture, &this->core_shader);
   
  
    //target->mapPixelToCoords(static_cast<sf::Vector2i>(this->player->getCenter())); 
    this->player->render(this->rendertexture, &this->core_shader, this->player->getCenter(), false);
    //this->Tilemap->renderObjects(this->rendertexture, this->view, this->ViewGridPosition, false, &this->core_shader);

    for (auto *i : this->activEnemies)
       {
           i->render(this->rendertexture, &this->core_shader, i->getCenter(), false);
           
       }
    
   this->Tilemap->DefferedRender(this->rendertexture, &this->core_shader,this->player->getCenter());
    
    //this->dialougeSystem->render(this->rendertexture);
    
    this->rendertexture.setView(this->rendertexture.getDefaultView());
    
    this->playerGUI->render(this->rendertexture);
    
    if(this->paused)
    {
        this->rendertexture.setView(this->rendertexture.getDefaultView());
        this->pMenu->render(this->rendertexture);
    }
    
   
    
    this->rendertexture.display();
    //this->rendersprite.setTexture(this->rendertexture.getTexture());
    target->draw(this->rendersprite);
}

void GameState::updateevents()
{




}






void GameState::checkforendstate() {
    
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
          
          //return this->quit = true;
        
      }
  //else return this->quit = false;
    
}

void GameState::updatePlayer(const float &dt)
{
    this->player->update(dt, this->MousePosView);
   
}





void GameState::updateEnemies(const float &dt)
{
    
    unsigned index = 0;
    for (auto *enemy : this->activEnemies)
    {
        enemy->update(dt, this->MousePosView);
        
        enemy->move_rand(dt, rand() % 3);
    

        this->Tilemap->updateWorldBoundsCollision(enemy, dt);
        this->Tilemap->updateTileCollision(enemy, dt);
        
        this->updateEncounter(enemy, index, dt);
        
        
                if(enemy->isDead())
                 {
                     
                     this->player->attributes->gainHP(enemy->getGainExp());
                     this->enemysystem->RemoveEnemy(index);
                     this->battleState = nullptr; 
                     
                     --index;
                    
                 }
   
        
        }
     ++index;
   
}

void GameState::updateEncounter(Enemy* enemy, const int index, const float & dt)
{
    
    if (enemy->getGlobalBounds().contains(this->player->getPosition().x, this->player->getPosition().y))
    {
        this->battleState = new BattleState(this->state_data, &this->gamestatedata, this->player, this->playerGUI, enemy);
        this->state_data->states->push(battleState);
                   
    }
    
    
    
        
}


void GameState::initenemysystem()
{
    this->enemysystem = new EnemySystem(this->activEnemies, this->textures);
   // this->objecthandler = new ObjectHandler(this->Objects, this->textures); 

}

void GameState::handletilemap()
{
    std::cout << "Searching for useable custom TileMap data..." << std::endl;
    std::string custom_tilemap_path = "";

    for (auto& p : std::filesystem::recursive_directory_iterator("Data/TileMap/"))
    {
        if (p.path().extension() == ".slmp") {
            std::cout << p.path().stem().string() << std::endl;
            std::cout << "custom TileMap data found!" << std::endl;
            custom_tilemap_path = p.path().string();
            break;
        }
    }
    std::cout << custom_tilemap_path << std::endl;
    try {
        this->Tilemap->loadfromfile(custom_tilemap_path);
    } 

    catch (std::runtime_error& e) 
    {
        std::cout << e.what() << std::endl; 
        std::cerr << e.what() << std::endl; 
    
    
    }
    std::cout << "Custom TileMap data found!" << std::endl;

}

void GameState::handleshader()
{


}

void GameState::handlekeybinds()
{



}

void GameState::handlefonts() 
{

        std::cout << "Searching for useable custom font files..." << std::endl;   
        std::string custom_font_path = "";

        for (auto & p : std::filesystem::recursive_directory_iterator("Resources/Assets/Fonts"))
        {
            if (p.path().extension() == ".ttf") {
                std::cout << p.path().stem().string() << std::endl;
                std::cout << "custom font files found!" << std::endl;
                custom_font_path = p.path().string();
                break;
            }
        }
        std::cout << custom_font_path << std::endl;
        this->font.loadFromFile(custom_font_path); 
        std::cout << "Custom Font Files Loaded!" << std::endl; 
       
}

    




