/**
///  GUI.hpp
///  engineFramework
///
@author Eli Reynolds on 2/5/20
@copyright © 2020 Eli Reynolds. 
*/

#ifndef GUI_hpp
#define GUI_hpp


#include "red_button00.h"
#include "red_button01.h"
#include "red_button02.h" 
//Core
#include <deque>
#include <map>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string_view>
#include <mutex>
#include <random>
#include "imgui.h"
#include "imgui-SFML.h"



//SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp> 

//Candle 
//Windows Debug Tools 


//Boost FileSystem


#include "Utilities.h"

#include "loading_icon.h"


///The three possible states for GUI Button elements to be in
enum ButtonStates{IDLE_BUTTON = 0, ///< Button has not been interacted with
    HOVER, ///< User's Mouse is hovering over the Button
    PRESSED ///< The Button has been pressed };
};


///The three possible states for GUI Box elements to be in, similar to
/// @see ButtonStates
enum BoxStates{IDLE_BOX = 0, ///<The box has not been interacted with
    HOVER_BOX, ///< User's Mouse is hovering over the Button
    PRESSED_BOX
    
};
///Namespace containing all of the GUI objects
namespace GUI {



/// <summary>
///  Convert a percantage value, to a percentage of the total width of the renderable window space
/// </summary>
/// <param name="percent"></param>
/// <param name="vm"></param>
/// <param name="view"></param>
/// <returns>newly calculated size / position for gui object</returns>
const float pixelpercentX(const float percent, const sf::VideoMode& vm);

const float pixelpercentY(const float percent, const sf::VideoMode& vm);


const std::string convertToString(char* a, int size);

/// Calculate a good character size for text based on the total size of the renderable window space
/// @param vm A refrence to the sf::VideoMode
///@returns const unsigned character size
   const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);


///A GUI element designed to handle user input visually, can be customized with text and color
class Button {

private:
   
    short unsigned ButtonState;
    short unsigned ID;
    sf::RectangleShape rectangle;
    sf::FloatRect ButtonBounds; 
    sf::Texture idle;
    sf::Texture clicked; 
    sf::Texture hover_texture;
    sf::Font *font;
    sf::Text text;
    

    sf::Image idle_loader; 
    sf::Image hover_loader; 
    sf::Image active_loader; 

    //degug colors remove later
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    //debug colors removce later
   
   
    /// <value>outline color</value> 
    sf::Color outline_idleColor;
    sf::Color outline_hoverColor;
    sf::Color outline_activeColor;
    //debug colors remove later
    sf::Color text_idlecolor;
    sf::Color text_hovercolor;
    sf::Color text_activecolor;
    
    bool hover;
    bool pressed;
    bool resources_from_header; 
    
public:
     
    /// <summary>
    ///  Construct a GUI button element with user definable colors for text, active state, idle state, hover state. 
    ///  Additionally, you can choose to supply outline colors and create advanced visually complete UI elements. 
    ///  At the bare minimum can be constructed with only values for position, and size. Will load default textures from header file
    ///  In all cases, can either contain text or be blank  
    ///
    ///  
    /// </summary>
    /// <param name="x">position x</param>
    /// <param name="y">position y</param>
    /// <param name="width">width</param>
    /// <param name="height">height</param>
    /// <param name="font"><type name ="sf::Font"/>font</param>
    /// <param name="text">text</param>
    /// <param name="character_size">text size</param>
    /// <param name="idlecolor">idle color</param>
    /// <param name="hovercolor">mouseover color</param>
    /// <param name="activecolor">active color </param>
    /// <remarks> the <paramref name="activecolor"/> is the color that the button texture will be updated with when it is being interacted with <type name="sf::Color"/> </remarks> 
    /// <param name="text_idlecolor">text idle color</param>
    /// <param name="text_hovercolor">text hover color</param>
    /// <param name="text_activecolor">text_activecolor</param>
    /// <param name="outline_activeColor">outline active color</param>
    /// <param name="outline_idleColor">outline idle color</param>
    /// <param name="outline_hoverColor">outline hover color</param>
    /// <param name="ID">optional ID</param>
    Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size, sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor, sf::Color text_idlecolor, sf::Color text_hovercolor, sf::Color text_activecolor,sf::Color outline_activeColor = sf::Color::Transparent, sf::Color outline_idleColor = sf::Color::Transparent, sf::Color outline_hoverColor = sf::Color::Transparent, short unsigned ID = 0);


   
	
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size, const std::string idle_texture, const std::string active_texture, const std::string hover_texture, short unsigned ID = 0);
    
    
    
   

	Button(float x, float y, float width, float height, const std::string idle_texture, const std::string active_texture, const std::string hover_texture, short unsigned ID = 0);

	Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned int character_size, short unsigned ID = 0);


    Button(float x, float y, float width, float height, short unsigned ID);

    virtual ~Button();
   
    
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i Mousepos);

    
     //Accessors
     /// Retreive wether or not the user has pressed the button
     const bool isPressed() const;
    
     ///Retreive the text on the Button
     const std::string getText() const;
     const short unsigned& getID() const;
   
     
    //Modifiers
    ///Change, or set the Button's text
    void setText(const std::string text);
    ///Change, or set the Button's unique ID
    void setID(const short unsigned ID);

    void resize(sf::Vector2f newsize);
    void reposition(sf::Vector2f newposition);
    void recalc_CharSize(unsigned newsize); 

    void load_from_header();
    

};


class DropDownList
{
private:
    float keytime;
    float keytime_max;
    
    GUI::Button* active_element;
    std::vector<GUI::Button*> list;
    sf::Font& font;
    
    
public:
    
    /// @brief Construct a GUI Drop Down List element
    ///  @discussion Use a GUI Drop Down List element for user interactions that require a list of options. e.g, a list a resolutions
    ///     in a graphics settings menu, a list of possible dialouge options.
    /// @param x the X position of the Drop Down List
    /// @param y the Y position of the Drop Down List
    /// @param width the width of the Drop Down List
    /// @param height the height of the Drop Down List
    /// @param font the font for the Drop Down Lists's text
    /// @param list the elements to display
    /// @param number_of_elements number of elements to display 
    DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned number_of_elements, unsigned default_index = 0);
    ~DropDownList();
    
    //Accessors
    const bool getkeytime();
    bool display_list;
    const unsigned short& getID() const;
    
    //Functions
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i& MouseposWindow, const float& dt);
    void updateketime(const float& dt);
    
};

class TextureSelector
{
private:
    
    bool active;
    bool ImGui; 
    //bool hidden;
    bool multi_select; 
    sf::Vector2f gridsize; 
    float keytime;
    float height;
    float width;
    const float keytimeMax;
    sf::Vector2u size;
    sf::Texture texturesheet; 
    sf::RectangleShape bounds;
    sf::RectangleShape selector;
    sf::RectangleShape sidebar;
    std::vector<sf::Sprite> guisprites;
    std::vector<sf::Texture> guitextures; 
    std::map<std::string, int> guiTextureKeys; 
    sf::Sprite sheet;
  
    sf::Vector2u MousePosGrid;
    sf::IntRect texturerect;
    sf::IntRect textureRect2; 
    Button* hide;
  
  
    
public:
    
    /// @brief Generate a GUI Texture Selector element
    /// @discussion In general, this is a GUI element designed almost entierly for the editor mode. Allowing the user to select from a png containing many different possible tile types and textures
    /// @param x the X position of the Texture Selector
    /// @param y the Y position of the Texture Selector
    /// @param width the width of the Texture Selector
    /// @param height the height of the Texture Selector
    /// @param gridsize the gridSize
    /// @param texture_sheet the texture sheet for the Texture Selector element to source tile textures from
    /// @param font the font for the Texture Selector to use
    /// @param text a string of text for the Texture Selector
    TextureSelector(float x, float y, float width, float height, sf::Vector2f gridsize, const sf::Texture* texture_sheet, sf::Font& font, std::string text, bool ImGui = false);
    



    /// <summary>
    /// Overload For ImGui Texture Editor
    /// </summary>
   
    ~TextureSelector();
    
    //Accessors
    ///Return wether or not the user's mouse is hovering over the Texture selector element
    const bool& getActive() const;
    const bool& getMulitSelect() const;
    const sf::Vector2u& getMaxSize() const; 
    ////Return an sf::IntRect refrence to the texture rectangle the user has selected
    const sf::IntRect& getTextureRect() const;
    const std::vector<sf::IntRect> getTextureRects() const;
    const bool getkeytime();
    
    
    
    //Functions
    void update(const sf::Vector2i& MousePosWindow, const float& dt);
    void updatekeytime(const float& dt);
    void render(sf::RenderTarget &target);
    bool hidden;
    std::vector<sf::IntRect> texture_rects;
};

class CheckBox
{
    
private:
    short unsigned BoxState;
    sf::Texture idle_box;
    sf::Texture hover_box; 
    sf::Texture active_box;
    sf::RectangleShape box;
    bool checked;
    bool hovering;
    
public:
    
    /// @brief Generate a simple GUI Checkbox element
    ///  @discussion use in lists where the user must "check off" options
    /// @param x the X position of the Checkbox on screen
    /// @param y the Y position of the Checkbox on screen
    CheckBox(float x, float y);
    ~CheckBox();
    
        
      void update(const sf::Vector2i Mousepos);
      const bool isPressed() const;
      void render(sf::RenderTarget& target);
    
};

class ProgressBar
{
    
private:
    
    std::string hpbarText;
    sf::Text text;
    float Max_width;
    sf::RectangleShape Interior;
    sf::RectangleShape Exterior;
    sf::Texture texture; 
    sf::Sprite bar; 
    int MaxVal; 
    
public:
    /// @brief Construct a GUI ProgressBar element
    /// @discussion Can be used to visuallly display progress percentages in a variety of applications. e.g, a Player's health, loading progress, percentages
    /// @param x the X position of the ProgressBar on screen
    /// @param y the Y position of the ProgressBar on screen
    /// @param width the width of the ProgressBar
    /// @param height the height of the ProgressBar
    /// @param MaxValue the Maximum percentage value for the ProgressBar to display, e.g (blank out of blank)
    /// @param vm the sf::VideoMode
    /// @param inner_color sf::Color, the inner color of the ProgressBar
    /// @param charsize the character size for text above the ProgressBar
    ProgressBar(float x, float y, float width, float height,sf::VideoMode& vm, sf::Color inner_color, unsigned charsize, sf::Font* font = nullptr);
    
    
    ~ProgressBar();
    
    void update(const int current_value, const int max_value);
    void render(sf::RenderTarget& target);
  
    //Accessors
    const float getWidth();
    ///Return a sf::Vector2f to the size of the ProgressBar
    const sf::Vector2f getSize(); 
};

class Icon
{
public:
    
    /// @brief Construct a simple GUI Icon element
    /// @discussion The Icon element is the simplest form of a Graphical Interface element. This particular Icon is non-clickable, and mainly intended to decorate other GUI elements.
    /// @param x the X position of the Icon element on screen
    /// @param y the Y position of the Icon on screen
    /// @param icon_texture std::string to a texture file to source the icon from
    Icon(float x, float y, const std::string icon_texture);
    virtual ~Icon();
    
    void render(sf::RenderTarget& target);
    
private:
    
    sf::RectangleShape Box;
    sf::Texture icontexture; 
    sf::Sprite IconBar; 
    
    
};


}









#endif /* GUI_hpp */
