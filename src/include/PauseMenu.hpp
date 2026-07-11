//
//  PauseMenu.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef PauseMenu_hpp
#define PauseMenu_hpp

#include "GUI.hpp"

/////////////////////////////////////////////////
/// \brief pause menu
/////////////////////////////////////////////////
class PauseMenu {

private:
    sf::RectangleShape background;
    sf::RectangleShape container;
    float adjusted_volume;

    sf::Font& font;
    sf::Text* menutext;

    std::map<std::string, GUI::Button*> buttons;

public:

    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param vm sf::VideoMode&
    /// \param font sf::Font&
    ///
    /////////////////////////////////////////////////
    PauseMenu(sf::VideoMode& vm, sf::Font& font);
    virtual ~PauseMenu();

    /// Fetch the address to the container holding all of the PauseMenu Buttons
    std::map<std::string, GUI::Button*>& getButtons();


    /////////////////////////////////////////////////
    /// \brief true if button at [key] has been pressed
    /// \see GUI::Button
    /// \param key const std::string&
    /// \return const bool
    ///
    /////////////////////////////////////////////////
    const bool isButtonPressed(const std::string& key);


    /////////////////////////////////////////////////
    /// \brief append a button to the pause menu
    ///
    /// \param key const std::string
    /// \param charSize const unsigned
    /// \param text const std::string
    /// \param width const float
    /// \param height const float
    /// \param y const float
    /// \return void
    ///
    /////////////////////////////////////////////////
    void addbutton(const std::string key, const unsigned charSize, const std::string text, const float width, const float height, const float y);

    void update(const sf::Vector2i& MousePos);
    void render(sf::RenderTarget& target);
};

#endif /* PauseMenu_hpp */
