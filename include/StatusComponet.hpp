//
//  AttributeComponet.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/21/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef AttributeComponet_hpp
#define AttributeComponet_hpp

class StatusComponet
{
    
private:
    //sounds
    sf::SoundBuffer buffer;
    sf::Sound Levelsound;
    
    void initsounds(); 
 
public:
    
        //Leveling 
      int level;
      int exp;
      int expNextlvl;
      int attributepts;
      

      //Time Variables 
      int Magic_Charge; 
      int stamina; 

      //Positive Multipliers
      //Magical friendship laser rainbows and shit like that, good things 
      int strength;
      int generosity;
      int kindness; 
      int laughter; 
      int honesty; 
      int loyalty; 
      int Magic; 
      int Heart;
      int friendship; 
  
      //Negative Multipliers 
      //Are you a dishonest, disloyal, mean spirited person? Do your choices reflect an evil personailty. 
      //These will work as a heavy disadvantage ultimatley, but some come with a trade.
      int animosity; 
      int greed; 
      int malice;
      int despair;
      int indifference;
      int treachery; 
      int deceit; 

      

      
      //Status
      int hp;
      int hpMax;
      int damMax;
      int damageMin;
      int accuracy;
      int defense;
      int luck; 
      int MagicMax; 
    
    //COINS
    int coins; 
      
    
    
    /// StatusComponent
    /// @brief Construct a StatusComponent for an entity.
    /// @discussion This class contains all of the elements needed for leveling, Health points, defense, etc.  applied to enemies and the player
    /// @param level a leve to start the StatusComponent off on (the player/enemy's level)
    StatusComponet(int level);
    virtual ~StatusComponet();
      
      
    //degub
    /// Print out the values for HP, DEF, etc
    std::string debugPrint() const;
      
    //Functions
    /// UpdateStats
    /// @brief Keep track of dynamic changes to the entity's Stats, and update values accordingly
    /// @param reset the hp value to the Maximum HP value. (e.g, starting off with full health)
    void UpdateStats(const bool reset);
    void update(); 
    void updateMagic(const float& dt); 
    /// Updatelevel
    ///@brief Check for changes in the entity's level, update values accordingly
    void UpdateLevel();
    void createstats();
    
    
    
    //Modifiers
    /// loseHP
    /// @brief Subtract health points from an entity
    /// @param hp point value to subtract
    void loseHP(const int hp);
    /// gainHP
    /// @brief Add health points to an entity
    /// @param hp point value to add
    void gainHP(const int hp);
    /// loseEXP
    /// @brief Subtract expierence points from an entity
    /// @param exp point value to subtract
    void loseEXP(const int exp);
    /// gainEXP
    /// @brief Add expierence points to an entity
    /// @param exp point value to add
    void gainEXP(const int exp);
    
    
    /// isdead
    ///@brief Get wether or not an entity is out of health points
    ///@returns bool wether or not the entity has run out of health points
    const bool isdead() const;  
};




#endif /* AttributeComponet_hpp */
