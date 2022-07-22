//
//  GraphicsSettings.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/7/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "stdafx.h"
#include "GraphicsSettings.hpp"

//Constructors/ Destructors

GraphicsSettings::GraphicsSettings()
{
    this->title = "Debug"; 
    this->resolution = sf::VideoMode::getDesktopMode(); 
    this->fullscreen = false;
    this->vsync = false;
    this->windowSettings.antialiasingLevel = 0;
    this->Videomodes = sf::VideoMode::getFullscreenModes();  
    std::cout << "video resolution depth is " << this->Videomodes.at(2).bitsPerPixel << " bits per pixel" << std::endl;
    //this->Videomodes = sf::VideoMode::
           
}

//Functions

void GraphicsSettings::savetofile(const std::string path)
         {
            std::ofstream out(path);
              
             if (out.is_open())
             {
                 out << this->title;
                 out << this->resolution.width << "" << this->resolution.height;
                 out << fullscreen;
                 out << framerate_limit;
                 out << vsync;
                 out << this->windowSettings.antialiasingLevel;
             }
           
           out.close();
             
         }

void GraphicsSettings::loadfromfile(const std::string path)
       {
           std::fstream in(path);
           
           if (in.is_open())
           {
               
               std::getline(in, this->title);
               in >> this->resolution.width >> this->resolution.height;
               in >> fullscreen;
               in >> framerate_limit;
               std::cout << framerate_limit << std::endl; 
               in >> vsync;
               in >> this->windowSettings.antialiasingLevel;
           }
           
           in.close();
           
           std::cout << "the window init file is being read properly" << std::endl; 

          
       }
