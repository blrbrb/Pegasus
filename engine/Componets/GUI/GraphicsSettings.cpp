//
//  GraphicsSettings.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 2/7/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "stdafx.h"
#include "GraphicsSettings.hpp"

//Constructors/ Destructors



GraphicsSettings::GraphicsSettings()
{
    //std::cout << sf::VideoMode::getDesktopMode().height << " " << sf::VideoMode::getDesktopMode().width << " " << sf::VideoMode::getDesktopMode().bitsPerPixel << std::endl; 
    this->title = "Debug";
    
  


    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->vsync = false;
    this->windowSettings.antialiasingLevel = 0;
    this->Videomodes = sf::VideoMode::getFullscreenModes();
    this->antialias_level = 0;
    this->framerate_limit = 0; 
    std::cout << this->windowSettings.depthBits << std::endl;
    this->windowSettings.majorVersion = 4;
    this->windowSettings.minorVersion = 6; 

    //Make sure to only push valid video modes. 
    for (auto& videomode : sf::VideoMode::getFullscreenModes())
    {
        if (videomode.isValid())
        {
            this->Videomodes.push_back(videomode); 
        }
    }
    LOG(INFO) << "creating graphics settings properties";
    LOG(INFO) << "Current Window Resolution is " << this->resolution.width << 'x' << this->resolution.height;
    LOG(INFO) << "video resolution depth is " << this->Videomodes.at(2).bitsPerPixel << " bits per pixel";
    pt.put("window.title", this->title);
    pt.put("window.resolution.width", this->resolution.width);
    pt.put("window.resolution.height", this->resolution.height);
    pt.put("window.fullscreen", this->fullscreen);
    pt.put("window.vsync", this->vsync);
    pt.put("contextSettings.bitdepth", this->windowSettings.depthBits);
    pt.put("contextSettings.debug", this->windowSettings.Debug);
    pt.put("contextSettings.framerate_limit", this->framerate_limit);
    pt.put("contextSettings.stencil_depth", this->windowSettings.stencilBits);
    pt.put("contextSettings.version_maj", this->windowSettings.majorVersion);
    pt.put("contextSettings.version_min", this->windowSettings.minorVersion);
    pt.put("contextSettings.device_accept_sRgb", this->windowSettings.sRgbCapable);
    pt.put("contextSettings.antialias_level", this->antialias_level);
    pt.put("contextSettings.stencildepth", this->windowSettings.stencilBits);
    pt.put("contextSettings.windowFlags", this->windowSettings.attributeFlags);
  


    //boost::property_tree::json_parser::write_json("Config/Window.cfg", pt);

    LOG(INFO) << "done creating graphics settings info"; 
    //this->Videomodes = sf::VideoMode::
           
}

//Functions

void GraphicsSettings::savetofile(const std::string path)
         {
           

           //There needs to be a thread resource use manager embedded somewhere here.
           //Assume we don't understand what the user's hardware is yet. Call this->graphicssettings->CUDA_Flush();
           /// 0 no cuda onboard. Switch to openGL. Fuck vulkan
           // Glut.h? fuck it

            
               boost::property_tree::json_parser::write_json(path, pt);
         }



void GraphicsSettings::loadfromfile(const std::string path)
{
             LOG(INFO) << "reading graphics configuration file " << path; 
           //Make sure to actually initalize the property tree so It's not a nullptr when you try and save dumdum
           boost::property_tree::json_parser::read_json(path, this->pt);



           this->resolution.width = this->pt.get<unsigned>("window.resolution.width");
           this->resolution.height = this->pt.get<unsigned>("window.resolution.height");
           this->fullscreen = this->pt.get<bool>("window.fullscreen");
           this->windowSettings.depthBits = this->pt.get<unsigned>("contextSettings.bitdepth");
           this->vsync = this->pt.get<bool>("window.vsync"); 
           this->title = this->pt.get<std::string>("window.title"); 
          
           this->framerate_limit = this->pt.get<unsigned>("contextSettings.framerate_limit");
           
           this->antialias_level = this->pt.get<unsigned>("contextSettings.antialias_level"); 
           this->windowSettings.majorVersion = this->pt.get<unsigned>("contextSettings.version_maj");
           this->windowSettings.sRgbCapable = this->pt.get<bool>("contextSettings.device_accept_sRgb");
           this->windowSettings.stencilBits = this->pt.get<unsigned>("contextSettings.stencildepth");
           this->windowSettings.attributeFlags = this->pt.get<sf::Uint32>("contextSettings.windowFlags"); 
           
           std::cout << "the window init file is being read properly" << std::endl; 

          
       }

