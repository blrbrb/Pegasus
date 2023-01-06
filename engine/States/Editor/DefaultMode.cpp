//
//  DefaultMode.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "stdafx.h"
#include "DefaultMode.hpp"



DefaultMode::DefaultMode(StateData *statedata, TileMap* tilemap, EditorStateData* editorstatedata, Levels* levels) : EditorModes(statedata, tilemap, editorstatedata, levels)
{
    this->initvariables();
    this->inittext();
    this->initgrid();
    this->initGUI();


}

DefaultMode::~DefaultMode()
{ 

}

void DefaultMode::updateInput(const float& dt)
{

   

  

    
    
        //this->TextureRect = this->texture_selector->getTextureRect();
    
    
  


   if((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("PLACE"))) && this->getkeytime() ))
       {
           
       //if the user's mouse is not on the sidebar
           
      
           //if the texure selector is not active
            if(!this->texture_selector->getActive())
            {
                if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) > -1)
                {
                        //if adding tiles is locked to one layer
                  
                          if (this->tilemap->lock_layer)
                          {
                               if (this->tilemap->TileEmpty(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, 0))
                                { 
                                   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) 
                                   {
                                       this->levels->addTile(this->editorstatedata->mousePosView->x, this->editorstatedata->mousePosView->y, 0, this->TextureRect, collision, this->type); 
                                       //this->levels[curr_level]->addTile(this->editorstatedata->mousePosView->x, this->editorstatedata->mousePosView->y, 0, this->TextureRect, collision, this->type);
                                   }
                                   this->levels->addTile(this->editorstatedata->mousePosView->x, this->editorstatedata->mousePosView->y, this->layer, this->TextureRect, collision, this->type);
                                   // this->tilemap->addTile(this->editorstatedata->mousePosView->x, this->editorstatedata->mousePosView->y, this->layer, this->TextureRect, collision, this->type);
                                    
                                       std::cout << "LOCKED: Tile Added" << std::endl;
                                }
                                else
                                {
                                   LOG(INFO) << "editor tried to place more than one tile on a locked layer";
                                }
                              
                          }
                        //else if adding tiles is not locked to one layer
                          else if (!this->tilemap->lock_layer)
                           {
                             
                              if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {



                                  for (int x = 0; x < this->tilemap->getMaxSizeGrid().x; x++)
                                  {
                                      for (int y = 0; y < this->tilemap->getMaxSizeGrid().y; y++)
                                      {
                                          this->levels->addTile(x, y, this->layer, this->TextureRect, collision, this->type);
                                          //this->tilemap->addTile(x, y, this->layer, this->TextureRect, collision, this->type);
                                      }

                                  }




                                  //this->tilemap->addTile(this->editorstatedata->mouseposGrid->x + (t * this->statedata->gridsize->x) ,this->editorstatedata->mouseposGrid->y + (i * this->statedata->gridsize->y), this->layer, this->TextureRect, collision, type);

                             // this->tilemap->addTile(this->editorstatedata->mouseposGrid->x + i, this->editorstatedata->mouseposGrid->y, this->layer, this->TextureRect, collision, type);

                              }
                              else
                                  this->levels->addTile(this->editorstatedata->mouseposGridI->x++, this->editorstatedata->mouseposGridI->y++, this->layer, this->TextureRect, collision, this->type); 
                                 // this->tilemap->addTile(this->editorstatedata->mouseposGridI->x++, this->editorstatedata->mouseposGridI->y++, this->layer, this->TextureRect, collision, this->type);
                               std::cout << "Tile Added" << std::endl;
                              
                           }

                    }
                
                   //else play UI invalid sound for invalid tile placement
                
                else if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) == -1)
                    {
                        LOG(INFO) << "editor tried to place tile on invalid tile Space";
                    }  
            }
            //else set the selection rect to the texture the user's mouse is on in the texture selector
           else 
           {

                this->TextureRect = this->texture_selector->getTextureRect();
                if (this->type == TileTypes::OBJECT)
                {
                    this->TextureRect = sf::IntRect(0, 0, 11, 16);

                }     
             

               
                        
           }  
        


      
           
        
     }
   
       //Remove a tile
   else if ((sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("REMOVE"))) && this->getkeytime()))
    {
       
        
             //if the user's mouse is not inside the texture selector
            if(!this->texture_selector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorstatedata->mousePosWindow)))
             {
                 //if the cursor is over a valid tile, ok to place
                 if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) != -1)
                 {
                     
                     if (this->tilemap->lock_layer)
                        {
                             if (!this->tilemap->TileEmpty(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer))
                              {
                                  this->tilemap->RemoveTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, TileTypes::DEFAULT);
                                  std::cout << "LOCKED: Tile Removed" << std::endl;
                              }
                              else
                              {
                                 LOG(INFO) << "editor tried to place more than one tile on a locked layer";
                              }
                            
                        }

                     else
                     {
                         this->TextureRect = this->texture_selector->getTextureRect();
                     }
                       //else if adding tiles is not locked to one layer
                         if (!this->tilemap->lock_layer)
                         {
                     
                             this->tilemap->RemoveTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, TileTypes::DEFAULT);
                             
                             std::cout << "Tile Removed" << std::endl;
                             
                         }
                     
                 }
                 
                 //else play UI invalid sound
               // TO DO: Create soundbuffer to load GUI sounds
                 else if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) == -1)
                 {
                     
                 }
             }
           
              
         
           
    }
       
     
       
       //Toggle Collision on Tiles
       if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("TOGGLE_COLLISION"))) && this->getkeytime())
       {
           if(this->collision)
               this->collision = false;
           else
               this->collision = true;
           
           std::cout << "Collision Tog" << std::endl;
       }
       
       
       //Toggle Type of Tile to increase or decrease
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("TYPE_INCREASE"))) && this->getkeytime())
       {
           ++this->type;
           std::cout << "Type up" << std::endl;
       }
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("TYPE_DECREASE"))) && this->getkeytime())
       {
           if(this->type > 0)
           --this->type;
           std::cout << "Type down" << std::endl;
       }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && this->getkeytime())
       {
          // this->select_Rect.rotate(90);  

           //this Is how you rotate things to the left, dear god, thank christ
           this->TextureRect.width = -this->TextureRect.top * this->TextureRect.left; 
            
          std::cout << this->select_Rect.getTextureRect().top << " After Transformation" << std::endl;
          
          // this->TextureRect.height = reverse.height; 
          
       }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && this->getkeytime()) 
       {
           this->TextureRect.height = -this->TextureRect.height; 
       
       } 
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && this->getkeytime())
       {
           std::cout << "object added" << std::endl;
           this->tilemap->addTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, this->editorstatedata->mouseposGridF->x, this->editorstatedata->mouseposGridF->y, ObjectTypes::LANTERN);
           //this->tilemap->addObject(this->editorstatedata->mousePosWindow->x, this->editorstatedata->mousePosWindow->y);
       }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4) && this->getkeytime())
       {
           if (this->TextureRect.left >= static_cast<int>(this->texture_selector->getMaxSize().x))
               return;
           else 
            this->TextureRect.left += 32;
       
       }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6) && this->getkeytime()) 
       {
           if (this->TextureRect.left <= 0)
               return;
           else
           this->TextureRect.left -= 32;
       }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8) && this->getkeytime()) 
       {
           if (this->TextureRect.top >= static_cast<int>(this->texture_selector->getMaxSize().y))
               return; 
           else 
           this->TextureRect.top += 24; 
       }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2) && this->getkeytime()) 
       {
           if (this->TextureRect.top <= 0)
               return;
           else 
           this->TextureRect.top -= 24; 
       }
      
        
    
}
    


void DefaultMode::update(const float &dt)
{
    this->updateGUI(dt);

    if (ImGui::GetIO().WantCaptureMouse == false)
    {
        this->updateInput(dt);
    }

    // this->updateInput(dt);
}

void DefaultMode::updateGUI(const float& dt)
{
    //this->select_Rect.setTextureRect(this->texture_selector->getTextureRect());

    ImGui::Begin("Map Editor", NULL, ImGuiWindowFlags_NoMove);
    this->texture_selector->update(*this->editorstatedata->mousePosWindow, dt);
    this->texturesample.setTextureRect(sf::IntRect(static_cast<int>(this->statedata->gridsize->x), static_cast<int>(this->statedata->gridsize->y), 0, 0));

    if (!this->texture_selector->getActive())
    {
        

        this->select_Rect.setTextureRect(this->TextureRect);
        this->texturesample.setTextureRect(this->TextureRect); 
        this->select_Rect.setPosition(this->editorstatedata->mouseposGridI->x * this->statedata->gridsize->x, this->editorstatedata->mouseposGridI->y * this->statedata->gridsize->y);

    }
   // this->texturesample.setTexture(*this->select_Rect.getTexture());
  


    this->select_Rect.setOrigin(sf::Vector2f(this->select_Rect.getLocalBounds().width, this->select_Rect.getLocalBounds().height) / 2.f);
   
    //this->select_Rect.setTextureRect(this->texture_selector->getTextureRect());
   // this->texturesample.setTextureRect(this->TextureRect);
    std::stringstream cursor_text;
    cursor_text << "MouseX: " << this->editorstatedata->mousePosView->x << "\n"
    << "MouseY:" << this->editorstatedata->mousePosView->y
    << "\n" << "GridX: " << this->editorstatedata->mouseposGridI->x
    << "\n" << "GridY: " << this->editorstatedata->mouseposGridI->y
    << "\n" << "TextureRectX: " << this->TextureRect.left
    << "\n" << "TextureRectY: " << this->TextureRect.top
    << "\n" << "Collision: " << this->collision
    << "\n" << "Type: " << EnumStrings[this->type]
    << "\n" << "Tiles:" << this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer);
    //this->statedata->gridsize.
    std::string text = cursor_text.str(); 

   
    ImGui::Text(text.c_str()); 
    ImGui::SameLine(); 
 
    ImGui::Image(this->texturesample); 

  
    ImGui::Separator(); 

    ImGui::Checkbox("Lock Tile Placement to this layer", &this->tilemap->lock_layer);
    ImGui::Checkbox("Hide Texture Selector", &this->texture_selector->hidden);  
    ImGui::SameLine(0.f, 8.f); 
    ImGui::Checkbox("Show Grid", &this->showgrid); 
   // ImGui::LableText("Texture Rectangle Controls"); 
    
    if (ImGui::ArrowButton("##up", ImGuiDir_Up)) { this->TextureRect.top += 24; }
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { this->TextureRect.left += 32; };
    ImGui::SameLine(0.0f, 0.5f);
    if(ImGui::ArrowButton("##right", ImGuiDir_Right)) {
         this->TextureRect.left -= 32; }
    if (ImGui::ArrowButton("##down", ImGuiDir_Down)) { this->TextureRect.top -= 24; }
    ImGui::SameLine(); 
   

    
    if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) < -1)
    {
        ImGui::TextColored(sf::Color::Red, "Invalid Tile Space");  
    
    }
    
    
  
    
  
    ImGui::End(); 
    


   // this->tilemap->updateTiles(dt);

   }

    


void DefaultMode::renderGUI(sf::RenderTarget &target)
{
    if (!this->texture_selector->getActive())
       {
           target.setView(*this->editorstatedata->view);
           target.draw(this->select_Rect);
           
           
           
           
       }


    if (this->showgrid) 
    {
        for (auto& it : this->grid) 
        {
            target.draw(it); 
        }
    
    }
       
       target.setView(this->statedata->window->getDefaultView());
       this->texture_selector->render(target); 
    
     
      
       
       
     
     
    
       
       target.setView(*this->editorstatedata->view);
}

void DefaultMode::render(sf::RenderTarget& target)
{

    this->renderGUI(target);
    
}

void DefaultMode::initvariables()
{
    this->TextureRect = sf::IntRect(0, 0, 32, 24);
    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->layer = 0;
    
}

void DefaultMode::inittext()
{
    
    sf::VideoMode vm = statedata->gfxsettings->resolution;
        
           
          
           
            
                    
}
    
    

    
void DefaultMode::initGUI()
{
    sf::VideoMode vm = statedata->gfxsettings->resolution;
    
 
   // this->select_Rect.setOrigin(sf::Vector2f(this->select_Rect.getGlobalBounds().width / 2.f / this->statedata->gridsize - static_cast<float>(this->editorstatedata->mouseposGrid->x), this->select_Rect.getGlobalBounds().height / 2.f / this->statedata->gridsize - static_cast<float>(this->editorstatedata->mouseposGrid->y)));
    
  //  sf::IntRect fart = this->texture_selector->getTextureRect(); 
    this->select_Rect.setSize(sf::Vector2f(statedata->gridsize->x, statedata->gridsize->y));
    this->select_Rect.setTexture(tilemap->getTileSheet());
 
    //this->texturesample.setSize(sf::Vector2f(64, 64));
    this->texturesample.setScale(sf::Vector2f(3, 3)); 
    this->texturesample.setTexture(*this->select_Rect.getTexture());
    this->texturesample.setTextureRect(this->select_Rect.getTextureRect()); 
    
    //this->texturesample.setPosition(GUI::pixelpercentX(100, vm), GUI::pixelpercentY(20, vm));
   
   //this->texture_selector = new GUI::TextureSelector(); 
   this->texture_selector = new GUI::TextureSelector(100.f, 20.f, 798.f, 798.f, *this->statedata->gridsize, this->tilemap->getTileSheet(), *this->editorstatedata->font, "X");
     
}


void DefaultMode::initgrid()
{
    this->grid.resize(100);


    this->showgrid = false;
    
    sf::VideoMode &vm = this->statedata->gfxsettings->resolution;
    
         float X= GUI::pixelpercentX(0, vm);
         float Y = GUI::pixelpercentY(0, vm);
         
           for (int x =0; x <= 1000; x++)
             {
                 X += GUI::pixelpercentX(3.2,vm);
                 
                 
                 if(X >= GUI::pixelpercentX(100, vm) || Y >= GUI::pixelpercentY(1000, vm))
                 {
                     Y += GUI::pixelpercentY(2.4, vm);
                     X = GUI::pixelpercentX(0, vm);

                 }
       
                    this->grid.push_back(sf::RectangleShape());
                    this->grid.at(x).setSize(sf::Vector2f(this->statedata->gridsize->x, this->statedata->gridsize->y));
                    this->grid.at(x).setFillColor(sf::Color::Transparent);
                    this->grid.at(x).setOutlineColor(sf::Color::White);
                    this->grid.at(x).setOutlineThickness(0.1f);
                    this->grid.at(x).setPosition(X, Y);
                           
                 
             }
      
}
