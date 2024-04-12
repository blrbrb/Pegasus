//
//  EnemyEditorMode.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/4/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#
#include "include/EnemyEditorMode.hpp"

#include "include/imgui.h"
#include "include/imgui-SFML.h"
 
EnemyEditorMode::EnemyEditorMode(StateData *statedata, TileMap *tilemap, EditorStateData *editorstatedata, Levels* levels) : EditorModes(statedata, tilemap, editorstatedata, levels)
{
    this->initvariables();
    this->inittext();
    this->initGUI();
    
}

EnemyEditorMode::~EnemyEditorMode()
{
    
}

void EnemyEditorMode::updateInput(const float &dt)
{
    if((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getkeytime()))
        {
                       
                         //if adding tiles is locked to one layer
                           if (this->tilemap->lock_layer)
                           {
                                if (!this->tilemap->TileEmpty(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer))
                                 {
                                     this->tilemap->addTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, this->TextureRect, this->Enemytype, this->Enemyamount, this->spawn_timer, this->maxDistance);
                                     
                                        std::cout << "LOCKED: Spawner Added" << std::endl;
                                 }
                                 else
                                 {
                                     std::cout << "Grid space is already assigned to a tile, disable layer locking to place more than one tile on a Grid space" << std::endl;
                                 }
                               
                           }
                         //else if adding tiles is not locked to one layer
                           else if (!this->tilemap->lock_layer)
                            {
                        
                                this->tilemap->addTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, 0, this->TextureRect, this->Enemytype, this->Enemyamount, this->spawn_timer, this->maxDistance);
                                
                               std::cout << "Spawner Tile Added" << std::endl;
                              
                               
                            }
                              
                           else 
                           {
                               this->tilemap->addTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, 0, this->TextureRect, this->Enemytype, this->Enemyamount, this->spawn_timer, this->maxDistance);
                           }

                     
                 
         
           
        }
    
        
        //Remove a tile
    else if ((sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getkeytime()) ||  (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("REMOVE"))) && this->getkeytime()))
     {
         
            if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) != -1)
                  {
                      
                      if (this->tilemap->lock_layer)
                         {
                              if (!this->tilemap->TileEmpty(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer))
                               {
                                   if(this->tilemap->checktype(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, TileTypes::SPAWNER))
                                   {
                                         this->tilemap->RemoveTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, TileTypes::SPAWNER );
                                       
                                   }
                                   std::cout << "LOCKED: Tile Removed" << std::endl;
                               }
                               else
                               {
                                   std::cout << "Grid space has already been assigned a tile , disable layer locking to place more than one tile on a Grid space" << std::endl;
                               }
                             
                         }
                        //else if adding tiles is not locked to one layer
                         else if (!this->tilemap->lock_layer)
                          {
                      
                              this->tilemap->RemoveTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, TileTypes::SPAWNER);
                              
                              std::cout << "Tile Removed" << std::endl;
                              
                          }
                      
                    
                  }
                  
                  //else play UI invalid sound
                  else if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) == -1)
                  {
                      
                  }
              
            
                else
                 {
                 
                 }
          }
            
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && this->getkeytime())
    {
        if (this->Enemyamount > 0)
            this->Enemyamount--;
              
    }
        
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->getkeytime())
    {
        
        if (this->Enemyamount < 100)
            this->Enemyamount++;
        else
            this->Enemyamount = 0;
    }
    
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) && this->getkeytime())
    {
        
        if (this->spawn_timer > 0)
                this->spawn_timer--;
    }
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && this->getkeytime())
    {
        
        if (this->spawn_timer < 1000)
            this->spawn_timer++;
        
        else
            this->spawn_timer = 0;
    }
    
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && this->getkeytime())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->type > 0)
                this->type--;
        }
    
         if (this->Enemytype < 10000)
             this->Enemyamount++;
        else
            this->Enemyamount=0;
    }
}


    


void EnemyEditorMode::update(const float &dt)
{
    this->updateGUI(dt);
    this->updateInput(dt);
}

void EnemyEditorMode::updateGUI(const float& dt)
{


    //ImGui::ShowDemoWindow(); 

    ImGui::Begin("Map Editor");
    //set the selection rectangle position

    this->select_Rect.setPosition(this->editorstatedata->mouseposGridI->x * this->statedata->gridsize->x, this->editorstatedata->mouseposGridI->y * this->statedata->gridsize->y);


    this->enemy_texture.loadFromFile("Resources/GUI/Icons/Blrb_Icon.png"); 

    std::stringstream cursor_text;
    cursor_text << "MouseX: " << this->editorstatedata->mousePosView->x << "\n"
        << "MouseY:" << this->editorstatedata->mousePosView->y
        << "\n" << "GridX: " << this->editorstatedata->mouseposGridI->x
        << "\n" << "GridY: " << this->editorstatedata->mouseposGridI->y
        << "\n" << "TextureRectX: " << this->TextureRect.left
        << "\n" << "TextureRectY: " << this->TextureRect.top
        << "\n" << "Type: " << EnumStrings[this->type]
        << "\n" << "Tiles:" << this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer);

    std::string text = cursor_text.str();


    ImGui::Text(text.c_str());
   
    //set the cursor text
    std::stringstream amount_text;
    amount_text << this->Enemyamount;
    std::string amount = amount_text.str();
    std::stringstream type_text;
    type_text << this->Enemytype;
    std::string type = type_text.str();
    std::stringstream timer_text;
    timer_text << this->spawn_timer;
    std::string timer = timer_text.str();
    std::stringstream distance_text;
    distance_text << this->maxDistance << ".f";
    std::string distance = distance_text.str();
    ImGui::Text("Spawn Controls"); 
    ImGui::SliderInt("Enemy Amount: ", &this->Enemyamount, 1, 100);
    if (ImGui::IsItemHovered())
    {
        ImGui::Text("Increase or decrease the amount of enemies that will spawn on this tile"); 

    }
    ImGui::SliderInt("Tile Spawn Timer (seconds): ", &this->spawn_timer, 1, 100);
    if (ImGui::IsItemHovered())
    {
        ImGui::Text("Increase or decrease the seconds inbetween each invidiual spawn event");

    }
    ImGui::SliderFloat("Maximum Wandering Distance", &this->maxDistance, 1.f, 10000.f, "%.4f", ImGuiSliderFlags_Logarithmic);
    if (ImGui::IsItemHovered())
    {
        ImGui::Text("Increase or decrease the maximum distance, (in floating point sfml cordinates) that an enemy can travel from it's parent tile");

    }
    ImGui::Separator();
    ImGui::Text("Enemy Type");
    ImGui::RadioButton("Blrb", &this->Enemytype, EnemyTypes::BLRB); 

    if (this->Enemytype == EnemyTypes::BLRB) 
    {
        this->enemy_GUI_sprite.setTexture(this->enemy_texture);
        ImGui::Image(this->enemy_GUI_sprite); 

    }
 
   

  
     
     //If the cursor is on a valid tile, the text color is white
     if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) != -1)
     {
        ImGui::TextColored(sf::Color::Red, "Cannot Place Tiles Over the Maximum Map boundaries!!!");
     }
     
     //if the cursor is not on a valid tile, the text color is red
     else if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) < 0)
     {
        // ImGui::TextColored(sf::Color::Red, "Cannot Place Tiles Over the Maximum Map boundaries!!!");
     }

     ImGui::End();
    }
    

void EnemyEditorMode::renderGUI(sf::RenderTarget &target)
{
    
     target.setView(*this->editorstatedata->view);
     target.draw(this->select_Rect);
   
   
    
    target.setView(this->statedata->window->getDefaultView());
 
}

void EnemyEditorMode::render(sf::RenderTarget &target)
{
      this->renderGUI(target);
}

void EnemyEditorMode::initGUI()
{
     sf::VideoMode vm = statedata->gfxsettings->resolution;
    
       
        //config the selection rectangle
        this->select_Rect.setSize(sf::Vector2f(statedata->gridsize->x, statedata->gridsize->y));
        this->select_Rect.setFillColor(sf::Color::White);
    
    
         
        //init the box for the cursor text to be displayed in
       
        
    
}

void EnemyEditorMode::initvariables()
{
    this->Enemytype = 1;
    this->Enemyamount = 1;
    this->spawn_timer = 60;
    this-> maxDistance = 1000.f;
    this->type = 1;
    this->layer = 0; 
      
}

void EnemyEditorMode::inittext()
{
    sf::VideoMode vm = statedata->gfxsettings->resolution;
        
          //init the cursor text
           this->cursortext.setFont(*this->editorstatedata->font);
           this->cursortext.setFillColor(sf::Color::White);
           this->cursortext.setCharacterSize(GUI::calcCharSize(vm, 140));
           this->cursortext.setOutlineThickness(1.f);
           this->cursortext.setPosition(GUI::pixelpercentX(78.4, vm), GUI::pixelpercentX(3, vm));
        
    
          //init the text describing the controls to the user
          this->controls.setCharacterSize(GUI::calcCharSize(vm, 140));
          this->controls.setFillColor(sf::Color::White);
          this->controls.setFont(*this->editorstatedata->font);
          this->controls.setPosition(GUI::pixelpercentX(78.4, vm), GUI::pixelpercentY(33, vm));
          this->controls.setString("CONTROLS \n+ Enemies: Up \n - Enemies: Down \n + Spawn Time: J \n - Spawn Time: K");
     
}



