//
//  DialougeSystem.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 6/25/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

//ToDO Write a function that will auto-wrap any and all text that spills over the boundary of the dialouge container

#ifndef DialougeSystem_hpp
#define DialougeSystem_hpp

#include "GUI.hpp"

enum DialougeTypes {DEBUG_TAG = 0, NPC, EVENT, POSITIVE, NEGATIVE, DIALOUGE};

class DialougeSystem
{
    
private:
    class Textbox

    {
    private:
        
        float directionY;
        float directionX;
        float life_time;
        float speed;
        
        sf::Text text;
        
    public:
        
        Textbox(sf::Font& font, std::string text, float x, float y, sf::Color color, unsigned char_size, float lifetime, float speed, float dir_x, float dir_y)
        {
            this->text.setFont(font);
            this->text.setPosition(x, y);
            this->text.setFillColor(color);
            this->text.setCharacterSize(char_size);
            this->text.setString(text);
            
            this->directionX = dir_x;
            this->directionY = dir_y;

            this->speed = speed;
            this->life_time = lifetime; 
            
        }
        //This is the overload constructor called when the Dialouge template Class is made 
        //Make sure to come back here and add more constructors each time you want to create a new template class 
        //All of the values for the text are initalized in the textbox constructor, it's 
        //the responsibility of the overload constructors to initalize class-specific variables

        Textbox(Textbox* textbox, std::string text)
        {
            this->text = textbox->text;
           // this->text.setFont(this->Textbox->font)
            this->text.setString(text);
            //this->text.setPosition(x, y);
            this->text.setColor(sf::Color::White); 
            this->text.setCharacterSize(24); 
            


        }
        
        ~Textbox()
        {
            
        }
        
        //Accessor
        inline const bool is_removable() const {return this->life_time <= 0.f;}
        
        //Functions
        void update(const float& dt)
        {
            if(this->life_time >= 0.f)
            {
                this->life_time -= 100.f * dt;
                
                this->text.move(this->directionX * this->speed * dt, this->directionY * this->speed * dt);
            }
        }
        void render(sf::RenderTarget& target)
        {
            target.draw(this->text);
        }
        
    };
    
    sf::Font font;
    sf::RectangleShape dialouge_container; 
    //internal array of text box elements
    
    std::vector<Textbox*> boxes;
    sf::VideoMode& vm;
    std::map<unsigned, Textbox*> templates; 
    int current_box; 
    int total_boxes; 
    void initvariables();
    void inittemplates();
    void initfonts(std::string font_file); 


   
    
public:
    
    DialougeSystem(std::string font_file, sf::VideoMode &vm);
    virtual ~DialougeSystem();
    
    void addTextbox(unsigned type, std::string text);
    void removeTextbox(); 

    
    void advance(); 
    void update(const float& dt);

    void render(sf::RenderTarget& target);
    
    const bool finished() const;

    //Acessors 
    

    
};

#endif /* DialougeSystem_hpp */
