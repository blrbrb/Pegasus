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
#include "gui_gradient.h"
#include "gui_gradient.h"

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

struct Pallete
{
    Pallete();
    ~Pallete(); 
    sf::Color idle; 
    sf::Color hover;
    sf::Color active; 
    sf::Color accent; 
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


const sf::Vector2f& pixelPercent(sf::Vector2f percent, const sf::VideoMode& resolution);
float pixelpercentX(const float &percent, const sf::VideoMode& vm);

float pixelpercentY(const float &percent, const sf::VideoMode& vm);


std::string convertToString(char* a, int size);

/// Calculate a good character size for text based on the total size of the renderable window space
/// @param vm A refrence to the sf::VideoMode
///@returns const unsigned character size
    unsigned int calcCharSize(const sf::VideoMode& vm, const unsigned int &modifier = 60);




class RoundedRectangleShape : public sf::Shape
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param size Size of the rectangle
        /// \param radius Radius for each rounded corner
        /// \param cornerPointCount Number of points of each corner
        ///
        ////////////////////////////////////////////////////////////
        explicit RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0);

        ////////////////////////////////////////////////////////////
        /// \brief Set the size of the rounded rectangle
        ///
        /// \param size New size of the rounded rectangle
        ///
        /// \see getSize
        ///
        ////////////////////////////////////////////////////////////
        void setSize(const sf::Vector2f& size);

        ////////////////////////////////////////////////////////////
        /// \brief Get the size of the rounded rectangle
        ///
        /// \return Size of the rounded rectangle
        ///
        /// \see setSize
        ///
        ////////////////////////////////////////////////////////////
        const sf::Vector2f& getSize() const;

        ////////////////////////////////////////////////////////////
        /// \brief Set the radius of the rounded corners
        ///
        /// \param radius Radius of the rounded corners
        ///
        /// \see getCornersRadius
        ///
        ////////////////////////////////////////////////////////////
        void setCornersRadius(float radius);

        ////////////////////////////////////////////////////////////
        /// \brief Get the radius of the rounded corners
        ///
        /// \return Radius of the rounded corners
        ///
        /// \see setCornersRadius
        ///
        ////////////////////////////////////////////////////////////
        float getCornersRadius() const;

        ////////////////////////////////////////////////////////////
        /// \brief Set the number of points of each corner
        ///
        /// \param count New number of points of the rounded rectangle
        ///
        /// \see getPointCount
        ///
        ////////////////////////////////////////////////////////////
        void setCornerPointCount(unsigned int count);

        ////////////////////////////////////////////////////////////
        /// \brief Get the number of points defining the rounded rectangle
        ///
        /// \return Number of points of the rounded rectangle
        ///
        ////////////////////////////////////////////////////////////
        virtual std::size_t getPointCount() const;

        ////////////////////////////////////////////////////////////
        /// \brief Get a point of the rounded rectangle
        ///
        /// The result is undefined if \a index is out of the valid range.
        ///
        /// \param index Index of the point to get, in range [0 .. GetPointCount() - 1]
        ///
        /// \return Index-th point of the shape
        ///
        ////////////////////////////////////////////////////////////
        virtual sf::Vector2f getPoint(std::size_t index) const; 


    
       

    private:
         ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::Vector2f size;
        float radius;
        unsigned int cornerpointCount;
};

class GradientElement : public sf::Drawable
{
    public: 
          explicit GradientElement(const float width=256, const float height=256, const float x=0, const float y=0);  
            ~GradientElement(); 

        
        void initVertexArray(sf::Vector2f size, sf::Vector2f position); 
      
        sf::FloatRect getGlobalBounds() const; 
        sf::Vector2f getPosition() const; 

        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setColor(const sf::Color& colorA, const sf::Color& colorB);
        sf::Vector2f getSize() const; 
        
        void setUUID(unsigned long int unique_id);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:

        sf::VertexArray geom;  
        sf::RectangleShape _core; 
        sf::Color colorA; 
        sf::Color colorB; 
        unsigned long int uuid; //set this to the GL states whatever uuid. 
        std::stack<sf::Vertex> renderBuffer; //not to be confused with the v abstract render deferred layer for picasso 
       

};
///A GUI element designed to handle user input visually, can be customized with text and color

class PillButton
{
    public: 
         PillButton(float x, float y, float width, float height, unsigned cornerCount); 

         PillButton(float x, float y, float width, float height, unsigned cornerCount, sf::Font& font, const std::string& text="");

        ~PillButton(); 
        
        void update(const sf::Vector2i& Mousepos);  

        void render(sf::RenderTarget& target);

        void setCharacterSize(const unsigned& characterSize);

        const bool& isPressed();
    private: 
        Pallete b_colors; 
        sf::Font* font; 
        sf::Text text;
        RoundedRectangleShape b_geom;
        unsigned short b_state; 
        bool hover;
        bool active; 
        bool pressed;
        
};


class Button {

private:
   
   
    short unsigned ButtonState;
    short unsigned ID;
    GradientElement* rectangle;
   
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
    /// <param name="idle_color">idle color</param>
    /// <param name="hover_color">mouseover color</param>
    /// <param name="active_color">active color </param>
    /// <remarks> the <paramref name="active_color"/> is the color that the button texture will be updated with when it is being interacted with <type name="sf::Color"/> </remarks>
    /// <param name="text_idle_color">text idle color</param>
    /// <param name="text_hover_color">text hover color</param>
    /// <param name="text_active_color">text_active_color</param>
    /// <param name="outline_active_color">outline active color</param>
    /// <param name="outline_idle_color">outline idle color</param>
    /// <param name="outline_hover_color">outline hover color</param>
    /// <param name="ID">optional ID</param>
    Button(float x, float y, float width, float height, sf::Font *font, const std::string& text, unsigned character_size, sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color outline_active_color = sf::Color::Transparent, sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, short unsigned ID = 0);


   
	/**
	 * @brief Construct a button UI element
	 * @param x - the horizontal position of the button relative to the screen
	 * @param y - the vertical position of the button relative to the screen
	 * @param width - the width of the button relative to the screen
	 * @param height - the height of the button relative to the screen
	 * @param font - the font, if text is rendered to the button
	 * @param text - text to render onto the button
	 * @param character_size - the size of the text on the button
	 * @param idle_texture - the button's idle texture (a mouse or controller has not clicked and are not hovering over the button)
	 * @param active_texture - the button's active texture (a mouse or controller has clicked on the button)
	 * @param hover_texture - the button's hover texture (a mouse of controller is currently hovering over the button)
	 * @param ID - the button's unique ID for easy indexing
	 */
	Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, unsigned character_size, const std::string &idle_texture, const std::string &active_texture, const std::string &hover_texture, short unsigned ID = 0);
    
    
    
   

	Button(float x, float y, float width, float height, const std::string &idle_texture, const std::string &active_texture, const std::string &hover_texture, short unsigned ID = 0);

	Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, unsigned int character_size, short unsigned ID = 0);


    Button(float x, float y, float width, float height, short unsigned ID=0);


    

    virtual ~Button();
   
    
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i& Mousepos);

    
     //Accessors
     /// Retreive wether or not the user has pressed the button
     bool isPressed() const;
    
     ///Retreive the text on the Button
     std::string getText() const;
     const short unsigned& getID() const;
   
     
    //Modifiers
    ///Change, or set the Button's button_text
    void setText(const std::string &button_text);
    ///Change, or set the Button's unique id
    void setID(short unsigned id);

    void resize(sf::Vector2f newSize);
    void reposition(sf::Vector2f newPosition);
    void recalculateCharacterSize(unsigned newSize);

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
    /**
     * @brief Calculates the number of frames that have passed inbetween inputs and checks to see if a minimum time value has been met
     * @example
     * @code
     * if(DropDownList.getKeyTime())
     * {
     * /let the user register another input again
     * }
     * @endcode
     * @return
     */
    bool getKeyTime();
    bool display_list;
    [[nodiscard]] const unsigned short& getID() const;
    
    //Functions
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i& MouseposWindow, const float& dt);
    void updateKeyTime(const float& dt);
    
};

class TextureSelector
{
private:
    
    bool active;
    bool using_imgui;
    //bool hidden;
    bool multi_select; 
    sf::Vector2f gridSize;
    float keyTime;
    float height;
    float width;
    const float keyTimeMax;
    sf::Vector2u size;
    sf::Texture textureSheet;
    sf::RectangleShape bounds;
    sf::RectangleShape selector;
    sf::RectangleShape sidebar;
    std::vector<sf::Sprite> guiSprites;
    std::vector<sf::Texture> guiTextures;
    std::map<std::string, int> guiTextureKeys; 
    sf::Sprite sheet;
  
    sf::Vector2u MousePosGrid;
    sf::IntRect textureRect;
     Button* hide;
  
  
    
public:
    
    /// @brief Generate a GUI Texture Selector element
    /// @discussion In general, this is a GUI element designed almost entierly for the editor mode. Allowing the user to select from a png containing many different possible tile types and textures
    /// @param x the X position of the Texture Selector
    /// @param y the Y position of the Texture Selector
    /// @param width the width of the Texture Selector
    /// @param height the height of the Texture Selector
    /// @param gridSize the gridSize
    /// @param texture_sheet the texture sheet for the Texture Selector element to source tile textures from
    /// @param font the font for the Texture Selector to use
    /// @param text a string of text for the Texture Selector
    TextureSelector(float x, float y, float width, float height, sf::Vector2f gridSize, const sf::Texture* texture_sheet, sf::Font& font, const std::string& text, bool using_imgui = false);
    




   
    ~TextureSelector();
    
    //Accessors
    ///Returns whether or not the user's mouse is hovering over the Texture selector element
    const bool& getActive() const;
    const sf::Vector2u& getMaxSize() const; 
    ////Return an sf::IntRect refrence to the texture rectangle the user has selected
    const sf::IntRect& getTextureRect() const;
    const std::vector<sf::IntRect> & getTextureRects() const;
    bool getKeyTime();
    
    
    
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
    
        
      void update(const sf::Vector2i &MousePos);
      bool isPressed() const;
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
    /// @param charSize the character size for text above the ProgressBar
    ProgressBar(float x, float y, float width, float height, sf::VideoMode& vm, sf::Color inner_color, unsigned charSize, sf::Font* font = nullptr);
    
    
    ~ProgressBar();
    
    void update(const int &current_value, const int &max_value);
    void render(sf::RenderTarget& target);
  
    //Accessors
    const float & getWidth() const;
    ///Return a sf::Vector2f to the size of the ProgressBar
    const sf::Vector2f & getSize();
};

class Icon
{
public:
    
    /// @brief Construct a simple GUI Icon element
    /// @discussion The Icon element is the simplest form of a Graphical Interface element. This particular Icon is non-clickable, and mainly intended to decorate other GUI elements.
    /// @param x the X position of the Icon element on screen
    /// @param y the Y position of the Icon on screen
    /// @param icon_texture std::string to a texture file to source the icon from
    Icon(float x, float y, const std::string &icon_texture);
    virtual ~Icon();
    
    void render(sf::RenderTarget& target);
    
private:
    
    sf::RectangleShape Box;
    sf::Texture icontexture; 
    sf::Sprite IconBar; 
    
    
};


}









#endif /* GUI_hpp */
