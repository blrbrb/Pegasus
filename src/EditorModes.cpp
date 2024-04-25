//
//  EditorModes.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#
#include "include/EditorModes.hpp"

EditorModes::EditorModes(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata, Levels* levels) : statedata(statedata), tilemap(tilemap), editorstatedata(editorstatedata), levels(levels)
{
    
    

}


EditorModes::~EditorModes()
{
    
    
    
    
    
    
    
    
}


void EditorModes::updateInput(const float& dt)
{
   
  

   
  
}

void EditorModes::update(const float &dt)
{
    
}

void EditorModes::updateGUI(const float &dt)
{
    
}

void EditorModes::renderGUI(sf::RenderTarget &target)
{

}

void EditorModes::render(sf::RenderTarget & target)
{
    
}

const bool EditorModes::getkeytime()
{
    /**
    @class EditorModes
    @brief Acess the keyTime
        @see updateKeyTime()
     @sa updateKeyTime()
    @discussion You can use this function to create a minimum amount of time that must pass before the user can acess a button, or key again.
    @return const bool
     */
    
    if (*this->editorstatedata->keytime >= *this->editorstatedata->ketyimeMax)
    {
        *this->editorstatedata->keytime = 0.f;
        return true;
    }
    
    return false;
}
