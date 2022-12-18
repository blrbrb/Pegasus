#pragma once
#ifndef stdafx_h
#define stdafx_h








//Core
#include <algorithm>
#include <deque>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string_view>
#include <mutex>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>



//SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp> 


//Windows Debug Tools 
#include "imgui.h"
#include "imgui-SFML.h"
#include "GUI.hpp"

//Boost FileSystem
#include "boost/config.hpp"
#include "boost/bimap.hpp" 
#include "boost/container/map.hpp"
#include "boost/algorithm/hex.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"


//#include "engine\Componets\GUI\
//#include "engine\Componets\GUI\
//#include "engine\Componets\GUI\
//#include "engine\Componets\GUI\


#endif  stdafx_h


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


#ifndef LOGGING_UTILS 

namespace utils {
    inline bool print(std::ostream& out) {
        return !!(out << std::endl);
    }

    template<typename T>
    bool print(std::ostream& out, T&& value)
    {
        return !!(out << std::forward<T>(value) << std::endl);
    }

    template<typename First, typename ... Rest>
    bool print(std::ostream& out, First&& first, Rest&& ... rest)
    {
        return !!(out << std::forward<First>(first)) && print(out, std::forward<Rest>(rest)...);
    }

    inline std::mutex logger_mtx;

    class log_stream {
    public:
        log_stream(std::string_view str, std::ostream& ifile)
            : name(str)
            , file(ifile)
        {
            std::string s{ "[" };
            name = s + name + "] ";
        } 
        template <typename... Args>
        bool operator() (Args&&... args) {
            bool OK = print( file, name, std::forward<Args>(args)...);
            {
                std::lock_guard<std::mutex> lck(logger_mtx);
               // print(std::cout, name, std::forward<Args>(args)...);
                if (!OK) {
                    print(std::cout, name, "-- Error writing to log file. --");
                }
            }
            return OK;
        }

    private:
        std::string name;
        std::ostream& file;


    };
}
#endif 



