//
//  GUI.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 2/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "include/GUI.hpp"
#include "GUI.hpp"


/* BEGIN BUTTON */

/**
 * @brief initialize a text button with set of colors for the button's container, and text and each of their states 
 * 
 * 
 * @namespace GUI 
 * @class Button
 * @addtogroup GUI 
 * 
 * 
 * @param x The x on-screen coordinate of the button's position. 
 * @param y The y on-screen coordinate of the button's position. 
 * @param width The horizontal size of the button 
 * @param height The vertical size of the button
 * @param font Pointer to an`sf::Font` object. 
 * @details This font is used to set the text style for the button's text content. It defines
 * the font family, size, color, and other text properties for the displayed
 * @param text string thatrepresents the text to be rendered on to the button.
 * @details  In the provided code snippet, this text is being set to the `sf::Text` object associated with the button. The text will be displayed using
 * @param character_size unsigned int representing how large the text glyph will be rendered 
 * @param idle_color The color to display on the button when the button is in it's idle state. 
 * @details i.e., when the button is not being interacted with by the user.
 * @param hover_color The cololr to display on the button when the button is in it's hover state. 
 * @details i.e when it is being hovered over by a user's controller / pointer / mouse, but not being directly interacted with.
 * @param active_color the color to display on the button when the button is in it's active state.
 * @details i.e  when it is clicked or activated by the user.
 * @param ID The unique identifier for the button. It is used to distinguish this button from other buttons in the GUI.
 */
GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, const std::string& text, unsigned character_size, sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color outline_active_color, sf::Color outline_idle_color, sf::Color outline_hover_color, short unsigned ID) :  hover(false), pressed(false), resources_from_header(false)
{
    
    this->ID = ID;
    this->rectangle = new GUI::GradientElement(width, height, x, y);
    this->rectangle->setSize(sf::Vector2f(x,y));

    this->rectangle->setPosition(sf::Vector2f(width, height));
    
    this->ButtonState = IDLE_BUTTON;
    
    
    //Configure the text, and font used on the Button interface
    this-> font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    
    //Configure the Position of the Text on the Button to *roughly* match
    //the center the top left corner is at the center of the button rectangle
    //(Side note) I failed highschool geom. I have no fucking idea why this works, but it does
    
    this->text.setPosition(this->rectangle->getPosition().x + this->rectangle->getPosition().x/ 2.f + 40.f - this->rectangle->getPosition().x / 2.f, this->rectangle->getPosition().y + this->rectangle->getSize().y / 2.f - 40.f);
    
    //Button rect colors
    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;
    
    //Button Text colors
    this->text_idlecolor = text_idle_color;
    this->text_hovercolor = text_hover_color;
    this->text_activecolor = text_active_color;
    
    //Button Outline colors
    this->outline_idleColor = outline_idle_color;
    this->outline_hoverColor = outline_hover_color;
    this->outline_activeColor = outline_active_color;
    
    
    //this->rectangle.setFillColor(this->idleColor);
    //this->rectangle.setOutlineColor(outline_idle_color);
    //this->rectangle.setOutlineThickness(1.f);

}


/**
 * @brief initialize a text button using a specified set of textures. 
 * 
 * @overload GUI::Button() 
 * @namespace GUI 
 * @class Button
 * @addtogroup GUI 
 * 
 * 
 * @param x The x on-screen coordinate of the button's position. 
 * @param y The y on-screen coordinate of the button's position. 
 * @param width The horizontal size of the button 
 * @param height The vertical size of the button
 * @param font Pointer to an`sf::Font` object. 
 * @details This font is used to set the text style for the button's text content. It defines
 * the font family, size, color, and other text properties for the displayed
 * @param text string thatrepresents the text to be rendered on to the button.
 * @details  In the provided code snippet, this text is being set to the `sf::Text` object associated with the button. The text will be displayed using
 * @param character_size unsigned int representing how large the text glyph will be rendered 
 * @param idle_texture The file path to a texture that will be displayed on the button when it is in it's idle state 
 * @details i.e., when the button is not being interacted with by the user.
 * @param active_texture The file path to a texture that will be displayed on the button when it is in it's active state.
 * @details i.e  when it is clicked or activated by the user.
 * @param hover_texture The file path to a texture that will be displayed on the button when it is in it's hover state. 
 * @details i.e when it is being hovered over by a user's controller / pointer / mouse, but not being directly interacted with.
 * @param ID The unique identifier for the button. It is used to distinguish this button from other buttons in the GUI.
 */
GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, const std::string& text, unsigned int character_size, const std::string &idle_texture, const std::string &active_texture, const std::string &hover_texture, short unsigned ID) : hover(false), pressed(false), resources_from_header(false)
{
    //const int x = 1;
    ///const sf::Uint8* test = reinterpret_cast<sf::Uint8*>(red_button00_data);
  
  
    
    this->ButtonState = IDLE_BUTTON;
    this->ID = ID; 
    this->rectangle = new GUI::GradientElement(width, height, x, y);   
       this->rectangle->setSize(sf::Vector2f(x,y));
       this->rectangle->setPosition(sf::Vector2f(width, height));
       
      
       
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idlecolor);
    this->text.setCharacterSize(character_size);
    
     this->text.setPosition(this->rectangle->getPosition().x + this->rectangle->getPosition().x/ 2.f + 40.f - this->rectangle->getPosition().x / 2.f, this->rectangle->getPosition().y + this->rectangle->getSize().y / 2.f - 40.f);
    
    try
    {
       
        if (!this->idle.loadFromFile(idle_texture))
        {
            //LOG(WARNING) << "unable to initalize custom button [IDLE_BUTTON] texture " << idle_texture << " . Falling back on default button [IDLE_BUTTON] texture" << std::endl;
            //this->load_from_header();
        }

        if (!this->clicked.loadFromFile(active_texture))
        {

           // LOG(WARNING) << "unable to initalize custom button [PRESSED] texture " << active_texture << " . Falling back on default button [PRESSED] texture" << std::endl;
            //this->load_from_header();
        }
        if (!this->hover_texture.loadFromFile(hover_texture))
        {
            //LOG(WARNING) << "unable to initalize custom button [HOVER] texture " << hover_texture << " . Falling back on default button [HOVER] texture" << std::endl;
            //this->load_from_header();
        }

    }
    catch (std::invalid_argument& e)
    {
        std::cerr << e.exception::what() << std::endl;
        std::cout << e.what() << std::endl;
        //LOG(FATAL) << "GUI::BUTTON(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned int" << std::endl << "character_size, const std::string idle_texture, const std::string active_texture, const std::string" << std::endl << "hover_texture, short unsigned ID)" << std::endl;
    }
    
    //this->rectangle.setTexture(&idle);
    
    
}

/**
 * @brief initalize a GUI::Button() with a specified set of textures. 
 * 
 * @overload GUI::Button() 
 * @namespace GUI 
 * @class Button
 * @addtogroup GUI 
 * 
 * 
 * @param x The x on-screen coordinate of the button's position. 
 * @param y The y on-screen coordinate of the button's position. 
 * @param width The horizontal size of the button 
 * @param height The vertical size of the button
 * @param idle_texture The file path to a texture that will be displayed on the button when it is in it's idle state 
 * @details i.e., when the button is not being interacted with by the user. 
 * @param active_texture The file path to a texture that will be displayed on the button when it is in it's active state.
 * @details i.e  when it is clicked or activated by the user.
 * @param hover_texture The file path to a texture that will be displayed on the button when it is in it's hover state. 
 * @details i.e when it is being hovered over by a user's controller / pointer / mouse, but not being directly interacted with.
 * @param ID The unique identifier for the button. It is used to distinguish this button from other buttons in the GUI.
 */
GUI::Button::Button(float x, float y, float width, float height, const std::string &idle_texture, const std::string &active_texture, const std::string &hover_texture, short unsigned ID) : font(nullptr), hover(false), pressed(false), resources_from_header(false)
{
  

    this->rectangle = new GUI::GradientElement(width, height, x, y);
    this->rectangle->setSize(sf::Vector2f(x,y));

    this->rectangle->setPosition(sf::Vector2f(width, height));
    try
    {
        if (!this->idle.loadFromFile(idle_texture))
        {
            //LOG(WARNING) << "unable to initalize custom button [IDLE_BUTTON] texture " << idle_texture << " . Falling back on default button [IDLE_BUTTON] texture";
            //this->load_from_header(); 

        }
        
        if(!this->clicked.loadFromFile( active_texture))
        {
            
            //LOG(WARNING) << "unable to initalize custom button [PRESSED] texture " << active_texture << " . Falling back on default button [PRESSED] texture";
            //this->load_from_header();
        }
        if(!this->hover_texture.loadFromFile(hover_texture))
        {
            //LOG(WARNING) << "unable to initalize custom button [HOVER] texture " << hover_texture << " . Falling back on default button [HOVER] texture";
           // this->load_from_header();
        }
           
        //this->rectangle.setTexture(&idle);
    
    }
    catch (std::invalid_argument& e)
    {
        
        std::cout << e.what();
    }
    
    this->ID = ID;
          
 
          this->ButtonState = IDLE_BUTTON;
        
    

     // this->rectangle.setTextureRect(static_cast<sf::IntRect>(this->rectangle.getGlobalBounds())); 
    
}


/**
 * @brief initalizes a GUI::Button() with text and a specified font 
 * @overload GUI::Button()
 * 
 * @namespace GUI 
 * @class Button 
 * 
 * 
 * @param x The x on-screen coordinate of the button's position. 
 * @param y The y on-screen coordinate of the button's position. 
 * @param width The horizontal size of the button 
 * @param height The vertical size of the button
 * @param font Pointer to an`sf::Font` object. 
 * @details This font is used to set the text style for the button's text content. It defines
 * the font family, size, color, and other text properties for the displayed
 * @param text string thatrepresents the text to be rendered on to the button.
 * @details  In the provided code snippet, this text is being set to the `sf::Text` object associated with the button. The text will be displayed using
 * @param character_size unsigned int representing how large the text glyph will be rendered 
 * @param ID The unique identifier for the button. It is used to distinguish this button from other buttons in the GUI.
 */
GUI::Button::Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, unsigned int character_size, short unsigned ID) : hover(false), pressed(false), resources_from_header(true)
{
   
    this->ButtonState = IDLE_BUTTON;
    this->ID = ID;
    //load the default textures from header
    //this->load_from_header();
    //this->rectangle.setTexture(&idle);
     this->rectangle = new GUI::GradientElement(x,y, width, height);
    //this->rectangle->setSize(sf::Vector2f(x, y));
    this->rectangle->setPosition(sf::Vector2f(width, height));

  

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(character_size);

     //debug
     //std::cout << this->rectangle->getPosition().x << std::endl; 
    
    this->text.setPosition(this->rectangle->getPosition().x + this->rectangle->getPosition().x / 2.f- this->rectangle->getPosition().x / 2.f, this->rectangle->getPosition().y + this->rectangle->getSize().y / 2.f );
}

/**
 * @brief Initializes a GUI button with specified parameters and default textures. Accepting only coordinates, and size parameters
 * @namespace GUI 
 * @class Button
 * @name Button 
 * @overload GUI::Button()
 * @addtogroup GUI
 * @param x The x on-screen coordinate of the button's position. 
 * @param y The y on-screen coordinate of the button's position. 
 * @param width The horizontal size of the button 
 * @param height The vertical size of the button
 * @param ID The unique identifier for the button. It is used to distinguish this button from
 * other buttons in the GUI.
 */
GUI::Button::Button(float x, float y, float width, float height, short unsigned ID) :font(nullptr), hover(false), pressed(false), resources_from_header(true)
{
  
    this->ButtonState = IDLE_BUTTON;
    this->ID = ID;
    //load the default textures from header
    //this->load_from_header();
   // this->rectangle.setTexture(&idle);
    this->rectangle = new GUI::GradientElement(width, height, x, y);
    this->text.setFillColor(sf::Color::White); 
    this->text.setScale(sf::Vector2f(2, 2));
    //debug
    //std::cout << this->rectangle->getPosition().x << std::endl;
    this->text.setPosition(this->rectangle->getPosition().x + this->rectangle->getPosition().x / 2.f + 20.f - this->rectangle->getPosition().x / 2.f, this->rectangle->getPosition().y + this->rectangle->getSize().y / 2.f - 20.f);
}

GUI::Button::~Button() = default;


//Functions

void GUI::Button::update(const sf::Vector2i &Mousepos) {
    
    this->ButtonState = IDLE_BUTTON; 

    if (this->rectangle->getGlobalBounds().contains(static_cast<sf::Vector2f>(Mousepos)))
    {

        this->ButtonState = HOVER;
      
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
          this->ButtonState = PRESSED;
       
        }
    }
        
    switch (this->ButtonState) {

            
        case IDLE_BUTTON: //the Button is not being interacted with by the user
            
            //this->rectangle.setTexture(&idle);
            
            //if the button is not given a texture with one of the overload constructors, give it a fill color
            
            //if(this->rectangle.getTexture() == nullptr)
            //{
                //this->rectangle.setFillColor(this->idleColor);
                this->text.setFillColor(sf::Color::White); 
                this->rectangle->setColor(sf::Color(255, 190,111),sf::Color(246, 2, 0));
              //  this->rectangle.setOutlineColor(this->outline_idleColor);
            //}
            
            break;
            
        case HOVER: // the user's cursor is hovering over the button
            
            //this->rectangle.setTexture(&hover_texture);
            
            //if (this->rectangle.getTexture() == nullptr)
            //{
                //this->rectangle.setFillColor(this->hoverColor);
                this->text.setFillColor(sf::Color::White);
                this->rectangle->setColor(sf::Color(170, 10, 10, 255), sf::Color(200, 10, 10, 255));
              //  this->rectangle.setOutlineColor(this->outline_hoverColor);
            //}
            
            break;
            
        case PRESSED: // the button has been interacted with
           
            //this->rectangle.setTexture(&clicked);
             
            //if (this->rectangle.getTexture() == nullptr)
            //{
                //this->rectangle.setFillColor(this->activeColor);
               
                 this->text.setFillColor(sf::Color::White);
                 this->rectangle->setColor(sf::Color(191, 90, 90), sf::Color(246, 64, 64));
                //this->rectangle.setOutlineColor(this->outline_activeColor);
            //}
            
            break;
            
        default:
            //will appear if something is wrong with the initalizaiton of the button texture.
           // this->rectangle.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::Green);
            this->rectangle->setColor(sf::Color(191, 90, 90), sf::Color(246, 64, 64));
            //this->rectangle.setOutlineColor(sf::Color::Blue);
          std::cout << "ERROR CODE BUTTON:210 || GUI::BUTTON::UPDATE || UNABLE TO LOAD BUTTON FROM TEXTURE FILE CHECK BUTTON CONSTRUCTOR" << std::endl;
            break;
    }

}

    

void GUI::Button::render(sf::RenderTarget& target) {
    target.draw(*this->rectangle);
    target.draw(this->text);
    
    
}

//Accessors
// return the bolean for wether or not the user has pressed the button
bool GUI::Button::isPressed() const {
    
    if (this->ButtonState == PRESSED)
        return true; 
    
    
    
   return false;
}

//Debug, fix "returning refrence to local temp. object" warning later

std::string GUI::Button::getText() const
{
    return this->text.getString();
}

void GUI::Button::setText(const std::string &button_text)
{
    
    this->text.setString(button_text);
    
    
}

/**
 * @brief resize the button
 * 
 * @param newSize an `sf::Vector2f` object representing the new size that the
 * button should be resized to.
 */
void GUI::Button::resize(sf::Vector2f newSize)
{
    this->rectangle->setSize(newSize);
}
/**
 * @brief reposition the button
 * 
 * @param newSize an `sf::Vector2f` object representing the new position to place the button
 */
void GUI::Button::reposition(sf::Vector2f newPosition)
{
    this->rectangle->setPosition(newPosition);
}

void GUI::Button::recalculateCharacterSize(unsigned newSize)
{
    //TD
}

void GUI::Button::load_from_header()
{
    this->idle_loader.create(RED_BUTTON01.width, RED_BUTTON01.height, RED_BUTTON01.data);
    this->hover_loader.create(RED_BUTTON00.width, RED_BUTTON00.height, RED_BUTTON00.data); 
    this->active_loader.create(RED_BUTTON02.width, RED_BUTTON02.height, RED_BUTTON02.data);

    this->idle.loadFromImage(this->idle_loader);
    this->hover_texture.loadFromImage(this->hover_loader);
    this->clicked.loadFromImage(this->active_loader); 

}

/*END BUTTON*/




/*BEGIN DROPDOWNLIST*/


GUI::DropDownList::DropDownList(float x, float y,float width, float height, sf::Font& font, std::string list[], unsigned number_of_elements, unsigned default_index): keytime(2.f), keytime_max(10.f), font(font), display_list(false)
{
    //number_of_elements = sizeof(list) / sizeof(std::string);
    
  
    this->active_element = new GUI::Button(
    x, y, width, height,
    &this->font, list[default_index], 14, sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
    sf::Color(20, 20, 20, 200), sf::Color(20, 20, 20, 200), sf::Color(20, 20, 20, 200),
    sf::Color::Black, sf::Color::Black, sf::Color::Black);
   
        
    for(unsigned i=0; i < number_of_elements; i++)
    {
        this->list.push_back(new GUI::Button(x, y + ((i+1) * height), width, height, &this->font, list[i], 14, sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
        sf::Color(20, 20, 20, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
        sf::Color::Black, sf::Color::Black, sf::Color::Black,
      i));
        
        
    }
    
  
    
    
}



GUI::DropDownList::~DropDownList()
{
    delete this->active_element;
    
    for (auto *&i : this->list)
    {
        delete i;
    }
    
    
}

void GUI::DropDownList::update(const sf::Vector2i & mousePosWindow, const float& dt)
{
    /*!
     @brief Hide or render the Drop Down element based on wether or not the active element is pressed.
            
     @param const sf::Vector2i& mousePosWindow    The Mouse's position in the window
     
        
     @param const float& Delta Time
     
    @return void
     */
    this->updateKeyTime(dt);

    this->active_element->update(mousePosWindow);

        //Show and hide the list
    if (this->active_element->isPressed() && this->getKeyTime())
        {
            if (this->display_list)
                this->display_list = false;
            else
                this->display_list = true;
        }

        if (this->display_list)
        {
            for (auto &i : this->list)
            {
                i->update(mousePosWindow);

                if (i->isPressed() && this->getKeyTime())
                {
                    this->display_list = false;
                    this->active_element->setText(i->getText());
                    this->active_element->setID(i->getID());
                }
            }
        }
    }

void GUI::DropDownList::render(sf::RenderTarget& target)
{
    this->active_element->render(target);
    
    if(this->display_list)
        {
           
         for( auto &i : this->list)
          {
             i->render(target);
          }
       
       }
       
    
}


//Accessors

bool GUI::DropDownList::getKeyTime()
{
    if (this->keytime >= this->keytime_max)
    {
        this->keytime = 0.f;
        return true;
    }

    return false;
}

const unsigned short &GUI::DropDownList::getID() const
{
    return this->active_element->getID();
}


void GUI::DropDownList::updateKeyTime(const float& dt)
{
    if (this->keytime < this->keytime_max)
    this->keytime += 10.f * dt;
    
    
    
}

/*END DROPDOWN LIST*/




/* BEGIN TEXTURE SELECTOR*/

//this Is NOT the version of the texture Selector being called in EditorState
GUI::TextureSelector::TextureSelector(float x, float y, float width, float height, sf::Vector2f gridSize, const sf::Texture* texture_sheet, sf::Font& font, const std::string& text, bool using_imgui) :keyTime(0.f), keyTimeMax(2.f), multi_select(false), height(0.f), width(0.f)
{
    /*!
                @brief Construct's the Texture Selector Element
                @param float x          X position
                @param float y          Y position
                @param float width
                @param float height
                @param float gridSize
                @param const sf::Texture Texture_sheet
                @param sf::Font& font
                @param std::string text
                @return void

     */
sf::Vector2f offset = gridSize;

this->using_imgui = using_imgui;
this->bounds.setSize(sf::Vector2f(width, height));
this->bounds.setPosition(x + offset.x, y + offset.y);
this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
this->bounds.setOutlineThickness(1.f);
this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));
this->textureSheet = *texture_sheet;
this->size = texture_sheet->getSize();
this->sheet.setTexture(*texture_sheet);
this->sheet.setPosition(x + offset.x, y + offset.y);

if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
{
    this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
}
if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
{
    this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
}

//Configure the texture selector element
this->selector.setPosition(x + offset.x, y + offset.y);
this->selector.setSize(gridSize);
this->selector.setFillColor(sf::Color::Transparent);
this->selector.setOutlineColor(sf::Color::Green);
this->selector.setOutlineThickness(1.f);

this->active = false;
this->gridSize = gridSize;

this->textureRect.width = gridSize.x;
this->textureRect.height = gridSize.y;
this->hidden = false;

this->hide = new GUI::Button(x, y, gridSize.x, gridSize.y);

//debug
//std::cout << this->bounds.getGlobalBounds().width << std::endl;




}

//Functions



GUI::TextureSelector::~TextureSelector()
{
    delete this->hide;
}

void GUI::TextureSelector::update(const sf::Vector2i& MousePosWindow, const float& dt)
{

   

    this->updatekeytime(dt);
   

        this->hide->update((MousePosWindow));

     



        if (this->hide->isPressed() && this->getKeyTime())
        {
            if (this->hidden)
                this->hidden = false;

            else
                this->hidden = true;

        }

    

    //Update the Selector, if the Texture Selector element is not hidden
    
    if(!this->hidden)
    {
       

          if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousePosWindow)))
          {
              this->active = true;
              
              this->MousePosGrid.x = (MousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize.x);
              this->MousePosGrid.y = (MousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize.y);
              
              this->selector.setPosition(this->bounds.getPosition().x + static_cast<float>(this->MousePosGrid.x) * this->gridSize.x,
                                         this->bounds.getPosition().y + static_cast<float>(this->MousePosGrid.y) * this->gridSize.y);
              
              //Update the Texture Rectangle
              
              this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
              this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
              
              
              
            //  this->texture_rects.push_back(this->textureRect);
              
          }
          
    }
    else if (this->hidden)
        this->active = false;

  
   

    
    
}

void GUI::TextureSelector::updatekeytime(const float& dt)
{
    if (this->keyTime < this->keyTimeMax)
    {
        this->keyTime += 10.f * dt;
    }
    
}

void GUI::TextureSelector::render(sf::RenderTarget &target)
{
    if(!this->hidden)
    {
        target.draw(this->bounds);
        target.draw(this->sheet);
        
        if(this->active)
           target.draw(this->selector);
    }

    this->hide->render(target);
   
}


const bool &GUI::TextureSelector::getActive() const
{
    return this->active;
}

const sf::IntRect &GUI::TextureSelector::getTextureRect() const
{
    return this->textureRect;
}

const std::vector<sf::IntRect> & GUI::TextureSelector::getTextureRects() const
{
    return this->texture_rects;
}


bool GUI::TextureSelector::getKeyTime()
{
    if (this->keyTime >= this->keyTimeMax)
    {
        this->keyTime = 0.f;
        return true;
    }

    return false;
}


const sf::Vector2u& GUI::TextureSelector::getMaxSize() const
{
    return this->size; 
}

/*END TEXTURE SELECTOR*/




/*BEGIN CHECKBOX*/

GUI::CheckBox::CheckBox(float x, float y) : BoxState(0), checked(false), hovering(false)
{
    //HARD CODED CHECK BOX TEXTURES
    this->idle_box.loadFromFile("Resources/GUI/TickBox/Grey/grey_box.png");
    this->active_box.loadFromFile("Resources/GUI/TickBox/Orange/red_boxCheckmark.png");
    
    this->box.setSize(sf::Vector2f(static_cast<float>(this->idle_box.getSize().x), static_cast<float>(this->idle_box.getSize().y)));
    
}

GUI::CheckBox::~CheckBox() = default;
void GUI::CheckBox::update(const sf::Vector2i &MousePos)
{
    
    
    this->BoxState = IDLE_BOX;
        
        if (this->box.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousePos)))
        {

            this->BoxState = HOVER_BOX;
          
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
              this->BoxState = PRESSED_BOX;
           
            }
           
        }
            
        switch (this->BoxState) {

                
            case IDLE_BUTTON: //the Box is not being interacted with by the user
                
                this->box.setTexture(&idle_box);
                break;
                
            case HOVER: // the user's cursor is hovering over the box
                
                this->box.setTexture(&hover_box);
                break;
                
            case PRESSED: // the button has been interacted with
               
                this->box.setTexture(&active_box);
                break;
                
            default:
                //will appear if something is wrong with the initalizaiton of the checkbox texture.
                this->box.setFillColor(sf::Color::Red);
                this->box.setFillColor(sf::Color::Green);
                this->box.setOutlineColor(sf::Color::Blue);
                std::cout << "ERROR_CODE GUI:630 || CHECKBOX::UPDATE || UNABLE TO LOAD CHECKBOX FROM TEXTURE FILE CHECK CONSTRUCTOR" << std::endl;
                break;
        }

}
    


bool GUI::CheckBox::isPressed() const
{
    if(this->BoxState == PRESSED_BOX)
        return true;
    
    

    return false;
    
}

void GUI::CheckBox::render(sf::RenderTarget &target) { 
    target.draw(this->box);
}
/*END CHECKBOX */

/*BEGIN MISC*/
unsigned int GUI::calcCharSize(const sf::VideoMode& vm, const unsigned int &modifier)
{
    /*
    * Calculates the optimal size for text elements based on the current resolution
    *
    * @param   sf::VideoMode& vm   the current resolution stored as a SFML videoMode.
    *
    * @param   const unsigned modifier      a modifer to custimize the size of the text relative to the resolution.
    *
    * @return  unsigned            The calculated ideal text size.
    */
    
    return static_cast<unsigned>((vm.width + vm.height) / modifier);
    
}

const sf::Vector2f& GUI::pixelPercent(sf::Vector2f percent, const sf::VideoMode &resolution) {
    return sf::Vector2f(std::floor(static_cast<float>(resolution.width) * (percent.x / 100.f)), std::floor(static_cast<float>(resolution.height) / (percent.y / 100.f)));
}
/**
 * @brief calculates the pixel value corresponding to a given percentage of the
 * screen width.
 * 
 * @param percent a float value representing a percentage value that you
 * want to convert to pixels based on the width of the `sf::VideoMode` object `vm`.
 * @param vm sf::VideoMode() with the width and height of a window in pixels. 
 * 
 * @return a percentage of the width of the window's resolution.
 */
float GUI::pixelpercentX(const float &percent, const sf::VideoMode& vm)
{


    return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
}

/**
 * @brief calculates the pixel value corresponding to a given percentage of the
 * screen height.
 * 
 * @param percent a float value representing a percentage value that you
 * want to convert to pixels based on the height of the `sf::VideoMode()` object `vm`.
 * @param vm sf::VideoMode() with the width and height of a window in pixels. 
 * 
 * @return a percentage of the height of the window's resolution.
 */
float GUI::pixelpercentY(const float &percent, const sf::VideoMode& vm)
{
  
    
     return std::floor(static_cast<float>(vm.height) * (percent / 100.f));
}



std::string GUI::convertToString(char* a, int size)
{
    int i;
    std::string s;
    for (i = 0; i < size; i++) {
        s += s + a[i];
    }
    return s;
}




/**
 * @brief  initialize a progress bar with a default color and text 
 * 
 * @namespace GUI 
 * @class ProgressBar 
 * @addtogroup GUI 
 * 
 * @param x The x on-screen coordinate of the button's position. 
 * @param y The y on-screen coordinate of the button's position. 
 * @param width The horizontal size of the button 
 * @param height The vertical size of the button
 * @param vm sf::VideoMode() the current resolution of the window 
 * @param inner_color `sf::Color()` to fill the progress bar  with 
 * @param charSize size of the text glyph 
 * @param font pointer to an `sf::Font()`, the font to apply to the text
 * 
 */
GUI::ProgressBar::ProgressBar(float x, float y, float width, float height,sf::VideoMode& vm, sf::Color inner_color, unsigned charSize, sf::Font* font) :MaxVal(0)
{
    float _width = GUI::pixelpercentX(width, vm);
    float _height = GUI::pixelpercentY(height, vm);
    float xx = GUI::pixelpercentX(x, vm);
    float yy = GUI::pixelpercentY(y, vm);
    
    
   
    this->Max_width = _width;
    
    this->Exterior.setSize(sf::Vector2f(_width, _height));
    this->Exterior.setFillColor(sf::Color(50,50,50,200)); 
   
    this->Exterior.setPosition(xx,yy);
    
    this->Interior.setSize(sf::Vector2f(_width, _height));
    this->Interior.setFillColor(inner_color);
    this->Interior.setPosition(this->Exterior.getPosition());

    if(font)
    {
        this->text.setFont(*font);
    
    this->text.setCharacterSize(GUI::calcCharSize(vm, charSize));
        this->text.setPosition(this->Interior.getPosition().x + GUI::pixelpercentX(1.4, vm), this->Interior.getPosition().y + GUI::pixelpercentY(2, vm));
    }
}


GUI::ProgressBar::~ProgressBar() = default;


void GUI::ProgressBar::update(const int &current_value, const int &max_value)
{
    float percent = static_cast<float>(current_value) / static_cast<float>(max_value);
    
    
    this->Interior.setSize(sf::Vector2f(static_cast<float>(std::floor(this->Max_width * percent)), this->Interior.getSize().y));
    
    this->hpbarText = std::to_string(current_value) + "/" +
                     std::to_string(max_value);
    
    this->text.setString(hpbarText);
}

/**
 * @brief  render the progress bar to a specified sf::RenderTarget
 * 
 * @namespace GUI 
 * @class ProgressBar 
 * @addtogroup GUI 
 * 
 * @param target `sf::RenderTarget` reference to a suitable render surface
 * 
 */
void GUI::ProgressBar::render(sf::RenderTarget& target)
{

    target.draw(this->Exterior);
    target.draw(this->Interior);
    target.draw(this->text);

}


/**
 * @brief get the width of the progress bar on screen 
 * 
 * @namespace GUI 
 * @class ProgressBar 
 * @addtogroup GUI 
 * 
 * @return A reference to a constant float value representing the width of the progress bar.
 */
const float & GUI::ProgressBar::getWidth() const
{
    return this->Max_width;
}

/**
 * @brief get the height of the progress bar on screen
 * @namespace GUI 
 * @class ProgressBar 
 * @return A reference to a constant float value representing the current size of the progress bar's (filled) interior 
 */
const sf::Vector2f & GUI::ProgressBar::getSize()
{
    return this->Interior.getSize(); 
}

/* END PROGRESSBAR */


/*BEGIN ICON*/
 

GUI::Icon::Icon(float x, float y, const std::string &icon_texture)
{
    
    this->icontexture.loadFromFile( icon_texture);
    this->Box.setTexture(&icontexture);
    this->Box.setSize(sf::Vector2f(64, 64));
    this->Box.setPosition(x, y);

}


GUI::Icon::~Icon()= default;

void GUI::Icon::render(sf::RenderTarget& target)
{
    
    target.draw(this->Box);
    
}

GUI::GradientElement::GradientElement(const float width, const float height, const float x, const float y) 
{   
        this->_core.setPosition(sf::Vector2f(x,y)); 
        this->_core.setSize(sf::Vector2f(width, height));
      
       
       this->initVertexArray(sf::Vector2f(width, height), sf::Vector2f(x,y));
       
}

GUI::GradientElement::~GradientElement()
{

}

void GUI::GradientElement::initVertexArray(sf::Vector2f size, sf::Vector2f position)
{
    this->_core.setSize(size); 
    this->_core.setPosition(position); 

    //debug
    //std::cout << "left= " << position.x << std::endl << "top= " << position.y << std::endl;
    //std::cout << "width= " << size.x << std::endl << "height= " << size.y << std::endl;
    
    this->geom = sf::VertexArray(sf::Quads, 4);

    this->geom[0].position = this->_core.getPoint(0); 
    
    this->geom[1].position = this->_core.getPoint(1); 
    this->geom[2].position = this->_core.getPoint(2);
    this->geom[3].position = this->_core.getPoint(3);


    return; 

}


sf::FloatRect GUI::GradientElement::getGlobalBounds() const
{
    return this->_core.getGlobalBounds();
}

sf::Vector2f GUI::GradientElement::getPosition() const {
       return this->_core.getPosition(); 
    }

void GUI::GradientElement::setPosition(sf::Vector2f position)
{
     sf::Transform transform;
    transform.translate(position - this->geom[0].position);

    // Apply the transformation to each vertex of the rectangle
    for (std::size_t i = 0; i < this->geom.getVertexCount(); ++i) {
        this->geom[i].position = transform.transformPoint(this->geom[i].position);
    }
}

void GUI::GradientElement::setSize(sf::Vector2f size)
{  
    this->_core.setSize(size);
    this->geom[0].position = this->_core.getPoint(0);
    this->geom[1].position = this->_core.getPoint(1); 
    this->geom[2].position = this->_core.getPoint(2);
    this->geom[3].position = this->_core.getPoint(3);
}

void GUI::GradientElement::setColor(const sf::Color &colorA, const sf::Color &colorB)
{
    this->geom[0].color = colorA;
    this->geom[1].color = colorA;
    this->geom[2].color = colorB;
    this->geom[3].color = colorB;
}

sf::Vector2f GUI::GradientElement::getSize() const
{
    return this->_core.getSize();
    
}

void GUI::GradientElement::setUUID(unsigned long int unique_id)
{
    this->uuid = unique_id; //too big 
}

void GUI::GradientElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    
    target.draw(this->geom, states);
}

GUI::RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f& size, float radius, unsigned int cornerPointCount)
{
    this->size = size;
    this->radius = radius;
    this->cornerpointCount = cornerPointCount;
    update();
}

////////////////////////////////////////////////////////////
void GUI::RoundedRectangleShape::setSize(const sf::Vector2f& size)
{
    this->size = size;
    update();
}

////////////////////////////////////////////////////////////
const sf::Vector2f& GUI::RoundedRectangleShape::getSize() const
{
    return this->size;
}

////////////////////////////////////////////////////////////
void GUI::RoundedRectangleShape::setCornersRadius(float radius)
{
    this->radius = radius;
    update();
}

////////////////////////////////////////////////////////////
float GUI::RoundedRectangleShape::getCornersRadius() const
{
    return this->radius;
}

////////////////////////////////////////////////////////////
void GUI::RoundedRectangleShape::setCornerPointCount(unsigned int count)
{
    this->cornerpointCount = count;
    update();
}

////////////////////////////////////////////////////////////
std::size_t GUI::RoundedRectangleShape::getPointCount() const
{
    return this->cornerpointCount*4;
}

////////////////////////////////////////////////////////////
sf::Vector2f GUI::RoundedRectangleShape::getPoint(std::size_t index) const
{
    if(index >= this->cornerpointCount*4)
        return sf::Vector2f(0,0);

    float deltaAngle = 90.0f/(this->cornerpointCount-1);
    sf::Vector2f center;
    unsigned int centerIndex = index/this->cornerpointCount;
    static const float pi = 3.141592654f;
    
    switch(centerIndex)
    {
        case 0: center.x = this->size.x - this->radius; center.y = this->radius; break;
        case 1: center.x = this->radius; center.y = this->radius; break;
        case 2: center.x = this->radius; center.y = this->size.y - this->radius; break;
        case 3: center.x = this->size.x - this->radius; center.y = this->size.y - this->radius; break;
    }

    return sf::Vector2f(this->radius*cos(deltaAngle*(index-centerIndex)*pi/180)+center.x,
                        -this->radius*sin(deltaAngle*(index-centerIndex)*pi/180)+center.y);
}


GUI::PillButton::PillButton(float x, float y, float width, float height, unsigned cornerCount)
{
    this->b_geom.setSize(sf::Vector2f(width,height)); 
    this->b_geom.setPosition(sf::Vector2f(x,y));
    this->b_geom.setFillColor(sf::Color(255, 190,111));
}

GUI::PillButton::PillButton(float x, float y, float width, float height, unsigned cornerCount, sf::Font &font, const std::string &text)
{
    this->b_geom.setSize(sf::Vector2f(width,height)); 
    this->b_geom.setPosition(sf::Vector2f(x,y));
    this->b_geom.setFillColor(sf::Color(255, 190,111));

    this->font = &font; 
    this->text.setString(text);

    this->text.setPosition(sf::Vector2f(this->b_geom.getPosition().x + this->b_geom.getPosition().x / 2.f + 20.f - this->b_geom.getPosition().x / 2.f, this->b_geom.getPosition().y + this->b_geom.getSize().y / 2.f - 20.f));
}

GUI::PillButton::~PillButton()
{
}

void GUI::PillButton::update(const sf::Vector2i &Mousepos)
{
    this->b_state= IDLE_BUTTON; 

    if (this->b_geom.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mousepos)))
    {

        this->b_state = HOVER;
      
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
          this->b_state = PRESSED;
          this->pressed = true;
       
        }
    }
        
    switch (this->b_state) {

            
        case IDLE_BUTTON: //the Button is not being interacted with by the user
            
            //this->b_geom.setTexture(&idle);
            
            //if the button is not given a texture with one of the overload constructors, give it a fill color
            
            //if(this->b_geom.getTexture() == nullptr)
            //{
                //this->b_geom.setFillColor(this->idleColor);
                this->text.setFillColor(sf::Color::White); 
                this->b_geom.setFillColor(sf::Color(246, 2, 0));
              //  this->b_geom.setOutlineColor(this->outline_idleColor);
            //}
            
            break;
            
        case HOVER: // the user's cursor is hovering over the button
            
            //this->b_geom.setTexture(&hover_texture);
            
            //if (this->b_geom.getTexture() == nullptr)
            //{
                //this->b_geom.setFillColor(this->hoverColor);
                this->text.setFillColor(sf::Color::White);
                this->b_geom.setFillColor(sf::Color(200, 10, 10, 255));
              //  this->b_geom.setOutlineColor(this->outline_hoverColor);
            //}
            
            break;
            
        case PRESSED: // the button has been interacted with
           
            //this->b_geom.setTexture(&clicked);
             
            //if (this->b_geom.getTexture() == nullptr)
            //{
                //this->b_geom.setFillColor(this->activeColor);
               
                 this->text.setFillColor(sf::Color::White);
                 this->b_geom.setFillColor(sf::Color(246, 64, 64));
                //this->b_geom.setOutlineColor(this->outline_activeColor);
            //}
            
            break;
            
        default:
            //will appear if something is wrong with the initalizaiton of the button texture.
           // this->b_geom.setFillColor(sf::Color::Red);
           
            this->b_geom.setFillColor(sf::Color(246, 64, 64));
            //this->b_geom.setOutlineColor(sf::Color::Blue);
          std::cout << "ERROR CODE BUTTON:210 || GUI::BUTTON::UPDATE || UNABLE TO LOAD BUTTON FROM TEXTURE FILE CHECK BUTTON CONSTRUCTOR" << std::endl;
            break;
    }
}

void GUI::PillButton::render(sf::RenderTarget &target)
{
    target.draw(this->b_geom);
}

void GUI::PillButton::setCharacterSize(const unsigned &characterSize)
{ 
 
        this->text.setCharacterSize(characterSize);
}

const bool &GUI::PillButton::isPressed()
{
   if(this->b_state == PRESSED)
        return true;

    return false;
}
