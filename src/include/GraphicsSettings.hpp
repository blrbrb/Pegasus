//
//  GraphicsSettings.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/7/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef GraphicsSettings_hpp
#define GraphicsSettings_hpp

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include<SFML/Graphics.hpp> 
#include <iostream> 
#include "easylogging++.h"

class GraphicsSettings
      {
      private:
          
          
      public:
          //Variables
          std::string title;
          sf::VideoMode resolution;
          std::vector<sf::VideoMode> Videomodes;
          sf::ContextSettings windowSettings;
          boost::property_tree::ptree pt;
          

          bool fullscreen;
          bool vsync;
          unsigned framerate_limit;
          unsigned depth; 
          unsigned antialias_level; 
          unsigned stencil_depth; 
          unsigned major_OpenGL_version; 
          unsigned minor_OpenGL_version;
          unsigned ppi; 


    
        
          //Constructors/Destructors
          GraphicsSettings();
          
          
          
          /// savetofile
          /// @brief Save the current graphics settings to a file to acess later.
          /// @param path to the file to write on
          void savetofile(const std::string path);
          
          /// loadfromfile
          /// @brief Load saved graphics settings from a file.
          /// @param path to the file to read from
          void loadfromfile(const std::string path);


          //Modifiers 

          //windowtitle
          //@breif Set the Title of the current Window \n
          //(window must be re-created with sfml window.create() for changes to apply) 
          //@param title 
         
          
      };

#endif /* GraphicsSettings_hpp */
