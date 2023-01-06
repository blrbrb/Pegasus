#pragma once
#ifndef Utilities_h 
#define Utilities_h 

#ifndef DEFAULT_RESOURCE
/// <summary>
/// Auxillary constant expressions to help with resource path management. Default paths to be placed \n 
/// as fallbacks, missing textures, too lazy to create new textures resources etc
/// </summary>
/// 
namespace Resources {
    /// <summary>
    /// path to the font
    /// </summary>
    const std::string font = "Resources/Assets/Fonts/PressStart2P.ttf";
    /// <summary>
    /// GUI Red Button Idle Texture
    /// </summary>
    const std::string red_button_idle = "Resources/GUI/Buttons/red_button01.png";
    /// <summary>
    /// GUI Red Button Active (pressed) texture
    /// </summary>
    const std::string red_button_active = "Resources/GUI/Buttons/red_button00.png";
    /// <summary>
    /// GUI Red Button hover texture
    /// </summary>
    const std::string red_button_hoover = "Resources/GUI/Buttons/red_button02.png";


    const std::string grey_button_idle = "Resources/GUI/Buttons/grey_button03.png";
    /// <summary>
    /// GUI Red Button Active (pressed) texture
    /// </summary>
    const std::string grey_button_active = "Resources/GUI/Buttons/grey_button05.png";
    /// <summary>
    /// GUI Red Button hover texture
    /// </summary>
    const std::string grey_button_hoover = "Resources/GUI/Buttons/grey_button04.png";
    /// <summary>
    /// Default player sprite sheet
    /// </summary>
    const std::string player_texture = "Resources/Assets/Entity/PlayerSheets/character_sheet4.png";
    ///<summary>
    /// Default Tilemap sprite sheet
    ///</summary>
    const std::string tilemap_texture = "Resources/Assets/Tiles/sheet.png";



};

#endif   
//DEFAULT_RESOURCE
// 









#ifndef LIGHTING
#define LIGHTING

static int node_count = 0;

typedef struct spotlight
{
   
    spotlight(sf::Vector2f position, sf::Color color, sf::Vector2f radius) 
    {
        //Add one to the total number of light nodes 
        node_count = node_count + 1;
        this->light_system.push_back(this);
        LOG(INFO) << "total number of lights on screen " << node_count;
        LOG(INFO) << "Size of lighting system vector " << light_system.size();
    }
    sf::Vector2f position; 
    sf::Color color; 
    sf::Vector2f radius;
    std::vector<spotlight*> light_system;

};



#endif 
//LIGHTING


#endif
//Utility_h 
//


