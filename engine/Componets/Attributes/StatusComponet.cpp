//
//  AttributeComponet.cppe
//  Project Pegasus
//
//  Created by Eli Reynolds on 2/21/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "stdafx.h"
#include "StatusComponet.hpp"


///me secret leveling formular
//
//(50/3) x (y+1^3) - 6 x (y^2) + (y+1) x 17 - 12;
//
//
//
StatusComponet::StatusComponet(int level)
{
    //init leveling variables
    this->level = level;
    this->exp = 0;                                      
    this->expNextlvl =static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) -12));
    
    this->attributepts = 2;
    this->MagicMax = 100; 
    //init stats
  
    //Init Positive Multipliers
    this->friendship = 1; 
    this->honesty = 1; 
    this->Heart = 1; 
    this->generosity = 1;
    this->laughter = 1; 
    this->kindness = 1; 
    this->strength = 1; 

    //Init Negative Multipliers 
    this->animosity = 0; 
    this->deceit = 0; 
    this->indifference = 0; 
    this->greed = 0; 
    this->despair = 0; 
    this->malice = 0; 
    this->treachery = 0; 
   
   
    this->initsounds();
    this->UpdateStats(true);
    
    
    this->UpdateLevel();
    this->UpdateStats(true);
    
    //init money
    this->coins = 0; 
    
}

StatusComponet::~StatusComponet()
{
   
}

void StatusComponet::initsounds()
{
   //this->buffer.loadFromFile("LevelUp.wav");
    this->Levelsound.setBuffer(buffer);
}


void StatusComponet::UpdateStats(const bool reset)
{
    //Calc to determine the Player's health points
    ////Form: x = y*9 + y + z/2 + xn / 5;
    
    //Calc to determien the Player's min damage
    ///Form: x = y2 + y/4 + xn / 5;
    
    //Calc to determine the Player;s Maximum damage
    ///Form: x = y2 + y/2 + xn / 5;
    
    //Calc to determine the Player's defense
    
    ///x = y2 + y/4 + xn/5;
    
    this->hpMax = this->Heart * 9 + this->friendship + (this->strength / 5 + this->treachery);
    this->damageMin = this->strength * 2 + this->animosity + this->strength / 4 - this->Heart / 10;
    this->damMax = this->strength * 2 + (this->indifference * 10 + this->animosity) + this->strength / 2 + (this->friendship / 5 - this->Heart / 10); 
    this->MagicMax = this->Magic * 10 + this->friendship / 2 + this->honesty / 2 - (this->despair * 2 + this->malice + this->treachery / 2);
    this->defense = this->loyalty * 2 + this->Heart / 4 + this->friendship / 10 - (this->animosity * 2 + this->despair / 4);
    this->Magic_Charge = this->friendship * 2 + this->Heart / 4 + this->honesty + this->kindness / 10 - (this->animosity * 5);
    //this->MagicMax = this->friendship * 10 + this->Heart * 10 + this->kindness * 10 + this->honesty - (this->animosity * 6 + this->indifference + this->malice);
    this->luck = this->generosity * 2 + this->honesty / 5 + this->laughter - (this->deceit + this->despair * 2); 
    
    if(reset)
    {
        this->hp = this->hpMax;
    }
    
}



void StatusComponet::update()
{
    this->UpdateLevel();
}

void StatusComponet::updateMagic(const float& dt)
{
    if (static_cast<int>(this->Magic_Charge) > this->MagicMax) 
    {
        this->Magic_Charge += this->Magic_Charge + dt / dt * 3.14; 
    }

}



void StatusComponet::createstats()
{
    
}



void StatusComponet::UpdateLevel()
{
    
    if (this->exp >= this->expNextlvl)
    {
        this->Levelsound.play();
        
        ++this->level;
        this->exp -= this->expNextlvl;
        this->expNextlvl = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) -12));
        //Formula Proof
        // x  = (50/30) * (y^3) - 6 * (y-^2)  +  (y * 17) - 12
        ++this->attributepts;
        
    }
    
}

std::string StatusComponet::debugPrint() const
{
    std::stringstream st;
    
    st << "Level:" << this->level << "\n"
    << "Exp:" << this->exp << "\n"
    << "Exp Next:" << this->expNextlvl << "\n"
    << "Attribute Pts:" << this->attributepts << "\n";
    
    
    return st.str();
    
}

const bool StatusComponet::isdead() const
{
    return this->hp <= 0;
    
}

//Modifiers
//Begin

void StatusComponet::loseHP(const int hp)
{
    this->hp -= hp;

    if (this->hp < 0)
        this->hp = 0;
}

void StatusComponet::gainHP(const int hp)
{
    this->hp += hp;

    if (this->hp > this->hpMax)
        this->hp = this->hpMax;
}

void StatusComponet::loseEXP(const int exp)
{
    this->exp -= exp;

    if (this->exp < 0)
        this->exp = 0;
}

void StatusComponet::gainEXP(const int exp)
{
    this->exp += exp;

    this->UpdateLevel();
}
