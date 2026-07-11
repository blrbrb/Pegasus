//
//  GraphicsSettings.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 2/7/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "include/GraphicsSettings.hpp"

// Constructors/ Destructors

GraphicsSettings::GraphicsSettings()
{
    // std::cout << sf::VideoMode::getDesktopMode().height << " " << sf::VideoMode::getDesktopMode().width << " " << sf::VideoMode::getDesktopMode().bitsPerPixel << std::endl;
    sf::VideoMode test(sf::Vector2u(1920,1080),32);
    this->title = "Debug";
    this->resolution = test;
    this->fullscreen = false;
    this->vsync = false;
    this->windowSettings.antiAliasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
    this->antialias_level = 0;
    this->framerate_limit = 0;
    std::cout << this->windowSettings.depthBits << std::endl;
    this->windowSettings.majorVersion = 4;
    this->windowSettings.minorVersion = 6;
    this->windowSettings.attributeFlags = sf::ContextSettings::Core;

    // Make sure to only push valid video modes.
    for (auto& videomode : sf::VideoMode::getFullscreenModes()) {
        if (videomode.isValid()) {
            this->videoModes.push_back(videomode);
        }
    }

    this->videoModes = sf::VideoMode::getFullscreenModes();
}

// Functions

void GraphicsSettings::saveToFile(const std::string& path)
{

}

void GraphicsSettings::loadFromFile(const std::string& path)
{

}
