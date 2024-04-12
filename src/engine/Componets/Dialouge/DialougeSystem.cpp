//
//  DialougeSystem.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 6/25/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//
#
#include "DialougeSystem.hpp"


DialougeSystem::DialougeSystem(std::string font_file, sf::VideoMode& vm) : vm(vm)
{
    this->current_box = 0;
    this->total_boxes = 0; 
         
    if (!this->font.loadFromFile(font_file))
    {
        std::cerr << "unable to open font file" << font_file << std::endl;
    }
    this->initfonts(font_file);
    this->initvariables();
    this->inittemplates();
}

DialougeSystem::~DialougeSystem()
{
    //clean memory of text tags
    
    for (auto *textbox : this->boxes)
    {
        delete textbox; 
        
    }
    
    for (auto &textbox : this->templates)
    {
          
        delete textbox.second;
    }
}

void DialougeSystem::addTextbox(unsigned type, std::string text)
{
   // int i;
    for (int x = 0; x < text.size(); x++)
    {
      
        //std::cout <<  x << std::endl; 
        //std::cout << text[x] << std::endl; 
            
        //std::cout << index << std::endl;   
        if (x < 0) {
            if (!std::isblank(text[x]))
            {

                text.insert(text[x], "\n");
            }

        }
    }
    if (text.length() > 10)
    {
        
       // std::cout << text.length() << std::endl;
        //f
     // text.insert(text[i])
        std::cout << "warning the total lenght of the dialouge string is larger than the container can safley fill..." << std::endl; 
    }
    this->boxes.push_back(new Textbox(this->templates[DIALOUGE], text));
    
}

void DialougeSystem::advance()
{
    if (!this->finished()) {
        this->boxes.erase(this->boxes.begin()); 
         
        return;
    }
    else if (this->finished()) 
    {
        return;
    }
        return; 
}



void DialougeSystem::update(const float &dt)
{
    this->total_boxes = this->boxes.size(); 
    std::cout << this->total_boxes << std::endl; 
    
    if (this->finished()) 
    {
        
        this->dialouge_container.setFillColor(sf::Color::Transparent);
    }
    
}

void DialougeSystem::render(sf::RenderTarget & target)
{
   // for (auto&textbox : this->boxes)
   // {
    //    textbox->render(target);
    //}
    // 
    if (!this->finished()) {
        this->boxes.front()->render(target);
    }
    //Draw the text over the dialouge container. This class will be used for NPC dialouge, etc, etc
    target.draw(this->dialouge_container); 
    
}

const bool DialougeSystem::finished() const
{
    if (this->boxes.empty())
    {
        return true;
    }
    return false;
}



void DialougeSystem::initvariables()
{
    //How tf do I math it so that this element is exactly distributed between both sides of the screen, at the exact same proportions? 
    ///x -y(sqr) + dx / dy? 
    // idk 
    this->dialouge_container.setSize(sf::Vector2f(GUI::pixelpercentX(95, this->vm),GUI::pixelpercentY(33, this->vm)));
    this->dialouge_container.setFillColor(sf::Color(200, 100, 100, 50)); 

    this->dialouge_container.setPosition(sf::Vector2f(GUI::pixelpercentX(2.5 , this->vm), GUI::pixelpercentY(75, this->vm)));
   
}

void DialougeSystem::inittemplates()
{
    this->templates[DEBUG_TAG] = new Textbox(this->font, "hello", 500, 500, sf::Color::White, 12,  1000.f, 200.f, 0, 0);
    this->templates[DIALOUGE] = new Textbox(this->font, "", this->dialouge_container.getPosition().x, this->dialouge_container.getPosition().y, sf::Color::White, 12, 1000.f, 200.f, 0, 0);
}


void DialougeSystem::initfonts(std::string font_file)
{
    
   if (!this->font.loadFromFile(font_file))
       {
           std::cout << "unable to open font file" << font_file << std::endl;
       }
    
}

