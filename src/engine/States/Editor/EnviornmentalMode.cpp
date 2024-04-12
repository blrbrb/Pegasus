//
//  EnviornmentalMode.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/10/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//#

#
#include "EnviornmentalMode.hpp"


void EnviornmentalMode::initvariables()
{
    this->TextureRect = sf::IntRect(0, 0, 32, 24);
    this->collision = false;
    this->type = TileTypes::OBJECT;
    this->layer = 0;
    
}

void EnviornmentalMode::inittext()
{
    sf::VideoMode vm = statedata->gfxsettings->resolution;
        
            //init the cursor text
           this->cursortext.setFont(*this->editorstatedata->font);
           this->cursortext.setFillColor(sf::Color::White);
           this->cursortext.setCharacterSize(GUI::calcCharSize(vm, 100));
           this->cursortext.setOutlineThickness(1.f);
           this->cursortext.setPosition(GUI::pixelpercentX(73.4, vm), GUI::pixelpercentX(3, vm));

            //init the cursor text container
           this->text_container.setSize(sf::Vector2f(400.f, 300.f));
           this->text_container.setFillColor(sf::Color(50,50,50,100));
           this->text_container.setPosition(GUI::pixelpercentX(71.4, vm), GUI::pixelpercentY(0, vm));
           this->text_container.setOutlineThickness(1.f);
           this->text_container.setOutlineColor(sf::Color(200, 200, 200, 150));
    

}

void EnviornmentalMode::initGUI()
{
   //
    this->guitexture.loadFromFile("Resources/GUI/Icons/Lantern.png");
    this->guisprite.setTexture(this->guitexture);
    this->guisprite.setScale(4.f, 4.f); 
    this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->statedata->gfxsettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50,50,50, 100));
    this->sidebar.setOutlineColor(sf::Color(200,200,200,150));
    this->sidebar.setOutlineThickness(1.f);
    
     //config the selection rectangle. Twice the size of the regular selection rectangle. Enviornmental objects like trees, rocks mountains etc.
    this->select_Rect.setSize(sf::Vector2f(statedata->gridsize->x, statedata->gridsize->y));
    this->select_Rect.setTexture(tilemap->getTileSheet());
     
     
     //this->select_Rect.setFillColor(sf::Color::Transparent);
     //this->select_Rect.setOutlineColor(sf::Color::Green);
     //this->select_Rect.setOutlineThickness(2);
     
     //Config the TextureSelector from GUI.hpp
     this->texture_selector = new GUI::TextureSelector(20.f, 20.f, 543.f, 560.f, *this->statedata->gridsize, this->tilemap->getTileSheet(), *this->editorstatedata->font, "X");
     
    
     
     //this->buffer.loadFromFile(resourcePath() + "Beep.wav");
     //this->UI_invalid.setBuffer(buffer
}


EnviornmentalMode::EnviornmentalMode(StateData *statedata, TileMap *tilemap, EditorStateData *editorstatedata, Levels* levels) : EditorModes(statedata, tilemap, editorstatedata, levels)
{
    this->initvariables();
    this->inittext();
    this->initGUI();
    this->type = TileTypes::OBJECT; 
}

EnviornmentalMode::~EnviornmentalMode()
{
    
}

void EnviornmentalMode::updateInput(const float &dt)
{
    if((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("PLACE")))))
        {
            
        //if the user's mouse is not on the sidebar
            
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorstatedata->mousePosWindow)))
        {
            //if the texure selector is not active
             if(!this->texture_selector->getActive())
             {
                 if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) != -1)
                     {
                         //if adding tiles is locked to one layer
                           if (this->tilemap->lock_layer)
                           {
                                if (this->tilemap->TileEmpty(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer))
                                 {
                                    this->tilemap->addTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, this->editorstatedata->mouseposGridF->x, this->editorstatedata->mouseposGridF->y, this->object_type);
                                     
                                        std::cout << "LOCKED: Tile Added" << std::endl;
                                 }
                                 else
                                 {
                                     std::cout << "Tile is already assigned to space, disable layer locking to place more than one tile on a spot" << std::endl;
                                 }
                               
                           }
                         //else if adding tiles is not locked to one layer
                           else if (!this->tilemap->lock_layer)
                            {
                                
                                this->tilemap->addTile(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer, this->TextureRect, collision, type);
                                
                                std::cout << "Tile Added" << std::endl;
                               
                            }

                     }
                 
                    //else play UI invalid sound for invalid tile placement
                 
                 else if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGridI->x, this->editorstatedata->mouseposGridI->y, this->layer) == -1)
                     {
                         std::cout << "Invalid Tile Space" << std::endl;
                     }
             }
             //else set the selection rect to the texture the user's mouse is on in the texture selector
            else
            {
                this->TextureRect = this->texture_selector->getTextureRect();
                         
            }
         }
        
            
         
      }
    
        //Remove a tile
    else if ((sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("REMOVE"))) && this->getkeytime()))
     {
         //if the user's mouse is not on the sidebar
         if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorstatedata->mousePosWindow)))
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
                                   std::cout << "Tile is already assigned to space, disable layer locking to place more than one tile on a spot" << std::endl;
                               }
                             
                         }
                        //else if adding tiles is not locked to one layer
                         else if (!this->tilemap->lock_layer)
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
            
                else
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
        
        
        
        
}

void EnviornmentalMode::update(const float &dt)
{
    this->updateGUI(dt);
    this->updateInput(dt);
    
}

void EnviornmentalMode::updateGUI(const float &dt)
{
   
    ImGui::Begin("Map Editor"); 

    ImGui::Text("Place misc objects onto the tilemap"); 
    
    if (ImGui::ImageButton(this->guisprite)) 
    {
      //  this->curr_type = TileTypes::OBJECT; 
        this->object_type = ObjectTypes::LANTERN; 
    }

   // ImGui::Button///
    ImGui::End(); 
  
}

void EnviornmentalMode::renderGUI(sf::RenderTarget &target)
{
   

}

void EnviornmentalMode::render(sf::RenderTarget &target)
{
     this->renderGUI(target);
}
