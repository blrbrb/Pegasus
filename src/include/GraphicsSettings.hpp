//
//  GraphicsSettings.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/7/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef GraphicsSettings_hpp
#define GraphicsSettings_hpp
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include "easylogging++.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class GraphicsSettings {
private:
public:
    // Variables
    std::string title;
    sf::VideoMode resolution;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;

    bool fullscreen;
    bool vsync;
    unsigned framerate_limit;
    unsigned depth;
    unsigned antialias_level;
    unsigned stencil_depth;
    unsigned major_OpenGL_version;
    unsigned minor_OpenGL_version;
    unsigned ppi;


    GraphicsSettings();


    /////////////////////////////////////////////////
    /// \brief write the current window config to disk
    ///
    /// \param path const std::string&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void saveToFile(const std::string& path);


    /////////////////////////////////////////////////
    /// \brief load window config from disk
    ///
    /// \param path const std::string&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void loadFromFile(const std::string& path);

};

#endif /* GraphicsSettings_hpp */
