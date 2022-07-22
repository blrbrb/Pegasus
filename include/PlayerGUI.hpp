//
//  PlayerGUI.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/24/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//




#pragma once
#include "PlayerGUITabs.hpp"

class PlayerGUI
{
private:
    
    Player* player;
    sf::VideoMode& vm;
    
    //Level Tag
    std::string LevelTagstring;
    sf::Text LevelTagText;
    sf::RectangleShape LevelTagExterior;
        
    //Exp bar
    GUI::ProgressBar* ExpBar;
    
    //Health bar
    sf::Font font;
    GUI::ProgressBar* HPbar;

    //Character Information tag 
    PlayerGUITabs* playerTabs; 
    //PlayerGUITabs playerGuiTabs; 
    
    //Inventory
    
    std::vector<sf::RectangleShape> Itemboxes;
    
    
    
    //COINS
    GUI::Icon* Coins; 
    std::string coins_string;
    sf::Text CurrentCoins;
    int max = 99;
    int maxItems;
    int currentSize; 
    bool hidden;

   
    void initfont();
    void initLevelTag();
    void initHPbar();
    void initEXPbar();
    void initMONEY();
    void initinventory();
    void initvariables(); 
    void initcharacterinfo();  
    void initTabs(sf::VideoMode& vm, sf::Font& font, Player& player); 
  
    
public:
    
    PlayerGUI(Player* player, sf::VideoMode& vm);
    virtual ~PlayerGUI();
    
    //Accessors
    ///get wether or not the user has opted to hide the Inventory
    const bool getInventoryHidden();
    const bool getTabsOpen() const; 
    void toggleCharacterTab(); 

    
    //Modifiers
    ///Hide the Inventory upon request from the user
    void HideInventory(); 
    
  
    
    void updateLevelTag();
    void updateHPbar();
    void updateEXPbar();
    void updateMoney();
    void updateInventory();
    void updateCharacterTabs(); 
    /// update
    /// @brief Update all of the PlayerGUI elements
    /// @param dt Delta-Time
    void update(const float& dt);
    
    //Render functions
    void renderLevelTag(sf::RenderTarget& target);
    void renderHPbar(sf::RenderTarget& target);
    void renderMoney(sf::RenderTarget& target);
    void renderEXPbar(sf::RenderTarget& target);
    void renderInventory(sf::RenderTarget& target); 
    void renderPlayerTabs(sf::RenderTarget& target); 
 
    
    /// render
    /// @brief Render all of the PlayerGUI elements to a sf::RenderTarget
    /// @param target RenderTarget
    void render(sf::RenderTarget& target);
    
    
};


//end namespace PlayerGUI


 /* PlayerGUI_hpp */
