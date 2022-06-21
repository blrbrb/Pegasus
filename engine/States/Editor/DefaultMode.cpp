//
//  DefaultMode.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "stdafx.h"
#include "DefaultMode.hpp"


DefaultMode::DefaultMode(StateData *statedata, TileMap* tilemap, EditorStateData* editorstatedata) : EditorModes(statedata, tilemap, editorstatedata)
{
    this->initvariables();
    this->inittext();
    this->initgrid();
    this->initGUI();


}

DefaultMode::~DefaultMode()
{ 

}

void DefaultMode::updateInput(const float &dt)
{
   if((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("PLACE")))))
       {
           
       //if the user's mouse is not on the sidebar
           
       if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorstatedata->mousePosWindow)))
       {
           //if the texure selector is not active
            if(!this->texture_selector->getActive())
            {
                if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) != -1)
                    {
                        //if adding tiles is locked to one layer
                          if (this->tilemap->lock_layer)
                          {
                               if (this->tilemap->TileEmpty(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer))
                                {
                                    this->tilemap->addTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, this->TextureRect, collision, type);
                                    
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
                               
                               this->tilemap->addTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, this->TextureRect, collision, type);
                               
                               std::cout << "Tile Added" << std::endl;
                              
                           }

                    }
                
                   //else play UI invalid sound for invalid tile placement
                
                else if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) == -1)
                    {
                        std::cout << "Invalid Tile Space" << std::endl;
                    }
            }
            //else set the selection rect to the texture the user's mouse is on in the texture selector
           else if (this->texture_selector->getActive())
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
                 if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) != -1)
                 {
                     
                     if (this->tilemap->lock_layer)
                        {
                             if (!this->tilemap->TileEmpty(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer))
                              {
                                  this->tilemap->RemoveTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, TileTypes::DEFAULT);
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
                     
                             this->tilemap->RemoveTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, TileTypes::DEFAULT);
                             
                             std::cout << "Tile Removed" << std::endl;
                             
                         }
                     
                   
                 }
                 
                 //else play UI invalid sound
               // TO DO: Create soundbuffer to load GUI sounds
                 else if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) == -1)
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
    


void DefaultMode::update(const float &dt)
{
    this->updateGUI(dt);
    this->updateInput(dt);
}

void DefaultMode::updateGUI(const float &dt)
{
   
    
    this->texture_selector->update(*this->editorstatedata->mousePosWindow, dt);
    
    if(!this->texture_selector->getActive())
    {
          //set the selection rectangle position
       
        this->select_Rect.setTextureRect(this->texture_selector->getTextureRect());
        
        this->select_Rect.setPosition(this->editorstatedata->mouseposGrid->x * this->statedata->gridsize, this->editorstatedata->mouseposGrid->y * this->statedata->gridsize);
        
    }

    this->texturesample.setTexture(this->select_Rect.getTexture());
    this->texturesample.setTextureRect(this->select_Rect.getTextureRect());
     
    

    //set the tile info text
    std::stringstream cursor_text;
    cursor_text << "MouseX: " << this->editorstatedata->mousePosView->x << "\n"
    << "MouseY:" << this->editorstatedata->mousePosView->y
    << "\n" << "GridX: " << this->editorstatedata->mouseposGrid->x
    << "\n" << "GridY: " << this->editorstatedata->mouseposGrid->y
    << "\n" << "TextureRectX: " << this->TextureRect.left
    << "\n" << "TextureRectY: " << this->TextureRect.top
    << "\n" << "Collision: " << this->collision
    << "\n" << "Type: " << EnumStrings[this->type]
    << "\n" << "Tiles:" << this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer);
    
    //If the cursor is on a valid tile, the above string stream color is white
    if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) != -1)
    {
        this->cursortext.setFillColor(sf::Color::White);
    }
    
    //if the cursor is not on a valid tile, the above string stream color is red
    else if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) == -1 )
    {
        this->cursortext.setFillColor(sf::Color::Red);
    }

    this->cursortext.setString(cursor_text.str());
    
    
    
    
    
    
   }

    


void DefaultMode::renderGUI(sf::RenderTarget &target)
{
    if (!this->texture_selector->getActive())
       {
           target.setView(*this->editorstatedata->view);
           target.draw(this->select_Rect);
           
           for(size_t i2 =0; i2 < grid.size(); i2++)
             {
                 target.draw(this->grid[i2]);
             }
           
           
       }
       
       target.setView(this->statedata->window->getDefaultView());
       this->texture_selector->render(target);
       target.draw(this->sidebar);
       target.draw(this->cursortext);
       target.draw(this->text_container);
       target.draw(this->texturesample);
       target.draw(this->texturesample_container);
       target.draw(this->controls);
       target.draw(this->controlsContainer);
    
       
       target.setView(*this->editorstatedata->view);
}

void DefaultMode::render(sf::RenderTarget& target)
{

    this->renderGUI(target);
    
}

void DefaultMode::initvariables()
{
    this->TextureRect = sf::IntRect(0, 0, 17, 17);
    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->layer = 0;
    
}

void DefaultMode::inittext()
{
    
    sf::VideoMode vm = statedata->gfxsettings->resolution;
        
            //init the cursor text
           this->cursortext.setFont(*this->editorstatedata->font);
           this->cursortext.setFillColor(sf::Color::White);
           this->cursortext.setCharacterSize(GUI::calcCharSize(vm, 140));
           this->cursortext.setOutlineThickness(1.f);
           this->cursortext.setPosition(GUI::pixelpercentX(78.4, vm), GUI::pixelpercentX(3, vm));

          
            //init the controls text
            this->controls.setCharacterSize(GUI::calcCharSize(vm, 140));
            this->controls.setFillColor(sf::Color::White);
            this->controls.setFont(*this->editorstatedata->font);
            this->controls.setPosition(GUI::pixelpercentX(78.4, vm), GUI::pixelpercentY(33, vm));
            this->controls.setOutlineColor(sf::Color::Black);
            this->controls.setOutlineThickness(1.f);
            this->controls.setString("Change Mode: 2 \n Zoom in: O \n Zoom Out: P \n");
                    
}
    
    



    
void DefaultMode::initGUI()
{
    sf::VideoMode vm = statedata->gfxsettings->resolution;
    
    
    //Config the sidebar
    this->sidebar.setSize(sf::Vector2f(64.f, static_cast<float>(this->statedata->gfxsettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50,50,50, 100));
    this->sidebar.setOutlineColor(sf::Color(200,200,200,150));
    this->sidebar.setOutlineThickness(1.f);
    
    //init the cursor text container
    this->text_container.setSize(sf::Vector2f(GUI::pixelpercentX(22.57, vm), (GUI::pixelpercentY(30, vm))));
    this->text_container.setFillColor(sf::Color(50,50,50,100));
    this->text_container.setPosition(GUI::pixelpercentX(77.4, vm), GUI::pixelpercentY(0, vm));
    this->text_container.setOutlineThickness(1.f);
    this->text_container.setOutlineColor(sf::Color(200, 200, 200, 150));
    
    //init the controls container
    this->controlsContainer.setSize(sf::Vector2f(GUI::pixelpercentX(22.57, vm), GUI::pixelpercentY(30, vm)));
    this->controlsContainer.setFillColor(sf::Color(50,50,50,100));
    this->controlsContainer.setPosition(GUI::pixelpercentX(77.4, vm), GUI::pixelpercentY(30, vm));
    this->controlsContainer.setOutlineThickness(1.f);
    this->controlsContainer.setOutlineColor(sf::Color(200, 200, 200, 150));
    
    //config the selection rectangle
    this->select_Rect.setSize(sf::Vector2f(statedata->gridsize , statedata->gridsize ));
    this->select_Rect.setTexture(tilemap->getTileSheet());
    
    
    
      //configure the texture sample box element
      this->texturesample.setSize(sf::Vector2f(64, 64));
      this->texturesample.setTexture(this->select_Rect.getTexture());
      this->texturesample.setTextureRect(this->select_Rect.getTextureRect());
      this->texturesample.setPosition(GUI::pixelpercentX(85.4, vm), GUI::pixelpercentY(20, vm));
      
      this->texturesample_container.setFillColor(sf::Color(50,50,50,100));
      this->texturesample_container.setSize(sf::Vector2f(this->sidebar.getSize().x , 68));
      this->texturesample_container.setOutlineColor(sf::Color(200,200,200,250));
      this->texturesample_container.setOutlineThickness(1.f);
      this->texturesample_container.setPosition(GUI::pixelpercentX(85.4, vm), GUI::pixelpercentY(20, vm));
     
    
     //Config the TextureSelector element
     this->texture_selector = new GUI::TextureSelector(100.f, 20.f, 798.f, 798.f, this->statedata->gridsize, this->tilemap->getTileSheet(), *this->editorstatedata->font, "X");
    
    
     

     //this->buffer.loadFromFile(resourcePath() + "Beep.wav");
     //this->UI_invalid.setBuffer(buffer

}


void DefaultMode::initgrid()
{
    this->grid.resize(10000);
    
    sf::VideoMode &vm = this->statedata->gfxsettings->resolution;
    
         float X= GUI::pixelpercentX(0, vm);
         float Y = GUI::pixelpercentY(0, vm);
         
           for (int x =0; x <= 10000; x++)
             {
                 X += GUI::pixelpercentX(1.4166666667,vm);
                 
                 
                 if(X >= GUI::pixelpercentX(100, vm) || Y >= GUI::pixelpercentY(100, vm))
                 {
                     Y += GUI::pixelpercentY(1.7, vm);
                     X = GUI::pixelpercentX(0, vm);

                 }
       
                    this->grid.push_back(sf::RectangleShape());
                 this->grid.at(x).setSize(sf::Vector2f(16.f, 16.f));
                    this->grid.at(x).setFillColor(sf::Color::Transparent);
                    this->grid.at(x).setOutlineColor(sf::Color::White);
                    this->grid.at(x).setOutlineThickness(1.f);
                    this->grid.at(x).setPosition(X, Y);
                           
                 
             }
      
}
