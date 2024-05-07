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

GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, const std::string& text, unsigned character_size, sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color outline_active_color, sf::Color outline_idle_color, sf::Color outline_hover_color, short unsigned ID) :  hover(false), pressed(false), resources_from_header(false)
{
    /*!
     
     @brief Default Constructor for a GUI button element
        
     @param float X
     @param float Y
     @param float width
     @param float height
     @param sf::Font *font
     @param std::string text
     @param unsigned character_size
     @param sf::Color idle_color
     @param sf::Color hover_color
     @param sf::Color active_color
     @param sf::Color text_idle_color
     @param sf::Color text_hover_color
     @param sf::Color text_active_color
     @param sf::Color outline_activecolor
     @param sf::Color outline_idlecolor
     @param sf::Color outline_hover_color
     @param short  unsigned ID
     
     */
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

GUI::Button::Button(float x, float y, float width, float height, const std::string &idle_texture, const std::string &active_texture, const std::string &hover_texture, short unsigned ID) : font(nullptr), hover(false), pressed(false), resources_from_header(false)
{
  
    
    /*!
    
    @brief Simplified Constructor for the GUI Button Element.
     
    @discussion Unlike the full constructor, this version initalizes the button rectangle with a texture rather than with a color and also does not include the option to have text.
     Useful for GUI elements that require a texture
       
    @param float X
    @param float Y
    @param float width
    @param float height
  
    @param const_std::string Idle_texture
      @param const_std::string active_texture
      @param const_std::string hover_texture
     
    
    @param short  unsigned ID
    
    */
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


     std::cout << this->rectangle->getPosition().x << std::endl; 
     //this->text.setPosition(this->rectangle->getGlobalBounds().top, this->rectangle->getGlobalBounds().width)
    this->text.setPosition(this->rectangle->getPosition().x + this->rectangle->getPosition().x / 2.f- this->rectangle->getPosition().x / 2.f, this->rectangle->getPosition().y + this->rectangle->getSize().y / 2.f );
}

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

    std::cout << this->rectangle->getPosition().x << std::endl;
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

void GUI::Button::resize(sf::Vector2f newSize)
{
    this->rectangle->setSize(newSize);
}

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

const unsigned short &GUI::Button::getID() const
{
    return this->ID;
}


void GUI::Button::setID(const unsigned short id)
{
    this->ID = id;
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

this->hide = new GUI::Button(x, y, gridSize.x, gridSize.y,9);

std::cout << this->bounds.getGlobalBounds().width << std::endl;

if (this->using_imgui)
{
    int count = 0;
    for (auto& p : std::filesystem::recursive_directory_iterator("Resources/GUI/Icons/guitile"))
    {
        if (p.path().extension() == ".png") {

            count++;
            std::cout << p.path() << std::endl;
            std::cout << p.path().filename() << std::endl;

            std::string path = p.path().string();


            std::cout << "Resources/GUI/Icons/guitile/" + p.path().filename().string() << std::endl;

            //do not use emplace_back, we need a temporary object with the size of an empty sf::Texture
            this->guiTextures.push_back(sf::Texture());
            this->guiTextures[count - 1].loadFromFile("Resources/GUI/Icons/guitile/" + p.path().filename().string());



        }


    }
    this->hide = nullptr;
}


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

        //ImGui::Image(this->sheet);    



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
    if(!this->using_imgui)
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
float GUI::pixelpercentX(const float &percent, const sf::VideoMode& vm)
{


    return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
}

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


void GUI::ProgressBar::render(sf::RenderTarget& target)
{

    target.draw(this->Exterior);
    target.draw(this->Interior);
    target.draw(this->text);

}


const float & GUI::ProgressBar::getWidth() const
{
    return this->Max_width;
}

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
      
       std::cout << "width= " << width << " " << "height= " << height << " " << "x= " << x << " " << "y= " << y << std::endl;
       this->initVertexArray(sf::Vector2f(width, height), sf::Vector2f(x,y));
       
}

GUI::GradientElement::~GradientElement()
{

}

void GUI::GradientElement::initVertexArray(sf::Vector2f size, sf::Vector2f position)
{
    this->_core.setSize(size); 
    this->_core.setPosition(position); 


    std::cout << "left= " << position.x << std::endl << "top= " << position.y << std::endl;
    //size = bottom right corner
    std::cout << "width= " << size.x << std::endl << "height= " << size.y << std::endl;
    
    this->geom = sf::VertexArray(sf::Quads, 4);

    this->geom[0].position = this->_core.getPoint(0); 
    
    this->geom[1].position = this->_core.getPoint(1); 
    this->geom[2].position = this->_core.getPoint(2);
    this->geom[3].position = this->_core.getPoint(3);
    
   // if(std::size_t & this->geom.getVertexCount()) 
   // {
        //c_assert("you fucking retard "); 
        //this->colorA = nullptr; 
        //this->
   // } 


    //push all points to the render buffer
   

    //vertical gradient is  AABB or BBAA 
    //horizontal gradient is ABBA or BAAB
    //this->geom[0].color = sf::Color(191, 64, 64,255); 
    //this->geom[1].color = sf::Color(191, 64, 64,255); 
    //this->geom[2].color = sf::Color(246, 2, 0,255); 
    //this->geom[3].color = sf::Color(246, 2, 0,255); 

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
