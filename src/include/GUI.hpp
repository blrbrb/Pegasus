/**
///  GUI.hpp
///
///
@author Eli Reynolds on 2/5/20
@copyright © 2020 Eli Reynolds.
*/

#ifndef GUI_hpp
#define GUI_hpp

#include "red_button00.h"
#include "red_button01.h"
#include "red_button02.h"


#include "imgui-SFML.h"
#include "imgui.h"
#include <cmath>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "loading_icon.h"

/// The three possible states for GUI Button elements to be in
enum ButtonStates { IDLE_BUTTON = 0, ///< Button has not been interacted with
    HOVER, ///< User's Mouse is hovering over the Button
    PRESSED ///< The Button has been pressed };
};

/// The three possible states for GUI Box elements to be in, similar to
///  @see ButtonStates
enum BoxStates { IDLE_BOX = 0, ///< The box has not been interacted with
    HOVER_BOX, ///< User's Mouse is hovering over the Button
    PRESSED_BOX

};

struct Pallete {
    Pallete();
    ~Pallete();
    sf::Color idle;
    sf::Color hover;
    sf::Color active;
    sf::Color accent;
};

namespace GUI {

/////////////////////////////////////////////////
/// \brief clamp to a percentage of the total renderable window space
///
/// \param percent sf::Vector2f
/// \param resolution const sf::VideoMode&
/// \return const sf::Vector2f&
///
/////////////////////////////////////////////////
const sf::Vector2f& pixelPercent(sf::Vector2f percent, const sf::VideoMode& resolution);

/////////////////////////////////////////////////
/// \brief clamp to a percentage of the total width of the renderable window space
///
/// \param percent const float&
/// \param vm const sf::VideoMode&
/// \return float
///
/////////////////////////////////////////////////
float pixelpercentX(const float& percent, const sf::VideoMode& vm);

/////////////////////////////////////////////////
/// \brief clamp to a percentage of the total height of the renderable window space
///
/// \param percent const float&
/// \param vm const sf::VideoMode&
/// \return float
///
/////////////////////////////////////////////////
float pixelpercentY(const float& percent, const sf::VideoMode& vm);

std::string convertToString(char* a, int size);

/////////////////////////////////////////////////
/// \brief calculate an ideal character size for text based on the total size of the renderable window space,
///
/// \param vm const sf::VideoMode&
/// \param const unsigned int& modifier = 60
/// \return unsigned int
///
/////////////////////////////////////////////////
unsigned int calcCharSize(const sf::VideoMode& vm, const unsigned int& modifier = 60);


/////////////////////////////////////////////////
/// \brief base class for GUI objects with gradient color shapes
/////////////////////////////////////////////////
class GradientElement : public sf::Drawable {
public:
    /////////////////////////////////////////////////
    /// \brief construct a GradientElement
    ///
    /// \param const float width = 256
    /// \param const float height = 256
    /// \param const float x = 0
    /// \param const float y = 0
    /// \return explicit
    ///
    /////////////////////////////////////////////////
    explicit GradientElement(const float width = 256, const float height = 256, const float x = 0, const float y = 0);
    ~GradientElement();


    /////////////////////////////////////////////////
    /// \brief the global bounding box
    ///
    /// \return sf::FloatRect
    ///
    /////////////////////////////////////////////////
    sf::FloatRect getGlobalBounds() const;
    /////////////////////////////////////////////////
    /// \brief the current screen position
    ///
    /// \return sf::Vector2f
    ///
    /////////////////////////////////////////////////
    sf::Vector2f getPosition() const;

    /////////////////////////////////////////////////
    /// \brief set the screen position
    ///
    /// \param position sf::Vector2f
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setPosition(sf::Vector2f position);
    /////////////////////////////////////////////////
    /// \brief set the pixel size
    ///
    /// \param size sf::Vector2f
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setSize(sf::Vector2f size);
    /////////////////////////////////////////////////
    /// \brief set the colors to split across the gradient
    ///
    /// \param colorA const sf::Color&
    /// \param colorB const sf::Color&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void setColor(const sf::Color& colorA, const sf::Color& colorB);
    /////////////////////////////////////////////////
    /// \brief the pixel size
    ///
    /// \return sf::Vector2f
    ///
    /////////////////////////////////////////////////
    sf::Vector2f getSize() const;

    void setUUID(unsigned long int unique_id);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::VertexArray geom;
    sf::RectangleShape _core;
    sf::Color colorA;
    sf::Color colorB;
    unsigned long int uuid;
    void initVertexArray(sf::Vector2f size, sf::Vector2f position);
    std::stack<sf::Vertex> renderBuffer;
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
    sf::Font* font;
    sf::Text* text;

    sf::Image idle_loader;
    sf::Image hover_loader;
    sf::Image active_loader;

    // degug colors remove later
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;



    sf::Color outline_idleColor;
    sf::Color outline_hoverColor;
    sf::Color outline_activeColor;

    sf::Color text_idlecolor;
    sf::Color text_hovercolor;
    sf::Color text_activecolor;

    bool hover;
    bool pressed;
    bool resources_from_header;

public:

    /////////////////////////////////////////////////
    /// \brief  Construct a button with user definable colors for (text, active state, idle state, hover state).
    ///  Additionally, you can choose to supply outline colors and create advanced visually complete UI elements.
    ///  At the bare minimum can be constructed with only values for position, and size. Will load default textures from header file
    ///  In all cases, can either contain text or be blank
    ///
    /// \param x screen position x to draw the button float
    /// \param y screen position y to draw the button float
    /// \param width float
    /// \param height float
    /// \param font sf::Font*
    /// \param text const std::string&
    /// \param character_size unsigned
    /// \param idle_color sf::Color
    /// \param hover_color sf::Color
    /// \param active_color sf::Color
    /// \param text_idle_color sf::Color
    /// \param text_hover_color sf::Color
    /// \param text_active_color sf::Color
    /// \param sf::Color::Transparent sf::Color outline_active_color=
    /// \param sf::Color::Transparent sf::Color outline_idle_color=
    /// \param sf::Color::Transparent sf::Color outline_hover_color=
    /// \param short unsigned ID = 0
    ///
    /////////////////////////////////////////////////
    Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, unsigned character_size, sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color outline_active_color = sf::Color::Transparent, sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, short unsigned ID = 0);

    /////////////////////////////////////////////////
    /// \brief construct a button
    ///  \overload
    /// \param x float
    /// \param y float
    /// \param width float
    /// \param height float
    /// \param font sf::Font*
    /// \param text const std::string&
    /// \param character_size unsigned
    /// \param idle_texture const std::string&
    /// \param active_texture const std::string&
    /// \param hover_texture const std::string&
    /// \param short unsigned ID = 0
    ///
    /////////////////////////////////////////////////
    Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, unsigned character_size, const std::string& idle_texture, const std::string& active_texture, const std::string& hover_texture, short unsigned ID = 0);

    Button(float x, float y, float width, float height, const std::string& idle_texture, const std::string& active_texture, const std::string& hover_texture, short unsigned ID = 0, sf::Font* font = nullptr);

    /////////////////////////////////////////////////
    /// \brief construct a button with a specified font and button text
    /// \overload
    /// \param x float
    /// \param y float
    /// \param width float
    /// \param height float
    /// \param font sf::Font*
    /// \param text const std::string&
    /// \param character_size unsigned int
    /// \param short unsigned ID = 0
    ///
    /////////////////////////////////////////////////
    Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, unsigned int character_size, short unsigned ID = 0);

    /////////////////////////////////////////////////
    /// \brief construct a button with default textures
    /// \overload
    /// \param x float
    /// \param y float
    /// \param width float
    /// \param height float
    /// \param short unsigned ID = 0
    ///
    /////////////////////////////////////////////////
    Button(float x, float y, float width, float height, short unsigned ID = 0);

    virtual ~Button();

    ///
    /// @brief Updates the button by tracking the mouse's position within the window, and
    /// monitoring for clicks within the button's bounding box
    ///
    /// @param target p_target:...
    ///
    void update(const sf::Vector2i& Mousepos);

    void render(sf::RenderTarget& target);
    ///
    /// @brief Has the button been clicked?
    ///
    /// @return bool
    ///
    bool isPressed() const;
    ///
    /// @brief fetch the text on the button
    ///
    /// @return std::string
    std::string getText() const;
    ///
    /// @brief fetch the button's ID (if set)
    ///
    /// @return const short unsigned int&
    ///
    const short unsigned& getID() const;

    ///
    /// @brief change the button's text'
    ///
    /// @param button_text p_button_text:...
    ///
    void setText(const std::string& button_text);
    /// Change, or set the Button's unique id
    ///
    /// @brief change or set the button's ID'
    ///
    /// @param id p_id:...
    ///
    void setID(unsigned short id);

    ///
    /// @brief change the size of the button
    ///
    /// @param newSize p_newSize:...
    ///
    void resize(sf::Vector2f newSize);
    ///
    /// @brief change the position of the button
    ///
    ///@param newPosition p_newPosition:...
    ///
    void reposition(sf::Vector2f newPosition);
    ///
    /// @brief recalculate the ideal character width to display on the button
    /// based on the current video resolution (unimplemented)
    ///
    /// @param newSize p_newSize:...
    ///
    void recalculateCharacterSize(unsigned newSize);

    void load_from_header();
};

class DropDownList {
private:
    float keytime;
    float keytime_max;

    GUI::Button* active_element;
    std::vector<GUI::Button*> list;
    sf::Font& font;

public:

    /////////////////////////////////////////////////
    /// \brief constructs a GUI Drop Down List
    ///
    /// \param x screen position float
    /// \param y screen position float
    /// \param width float
    /// \param height float
    /// \param font sf::Font&
    /// \param list[] std::string
    /// \param number_of_elements unsigned
    /// \param 0 unsigned default_index=
    ///
    /////////////////////////////////////////////////
    DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned number_of_elements, unsigned default_index = 0);
    ~DropDownList();

    // Accessors

    /////////////////////////////////////////////////
    /// \brief Calculates the number of frames that have passed between inputs and checks to see if a minimum time value has been met
    /// before allowing another input
    ///
    /// \return bool
    ///
    /////////////////////////////////////////////////
    bool getKeyTime();
    bool display_list;
    const unsigned short& getID() const;

    // Functions
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i& MouseposWindow, const float& dt);
    void updateKeyTime(const float& dt);
};

class TextureSelector {
private:
    bool active;
    bool using_imgui;
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

    /////////////////////////////////////////////////
    /// \brief constructs a GUI Texture Selector
    ///
    /// \param x screen position float
    /// \param y screen position float
    /// \param width float
    /// \param height float
    /// \param gridSize sf::Vector2f
    /// \param texture_sheet const sf::Texture*
    /// \param text const std::string&
    /// \param false bool using_imgui=
    ///
    /////////////////////////////////////////////////
    TextureSelector(float x, float y, float width, float height, sf::Vector2f gridSize, const sf::Texture* texture_sheet, const std::string& text, bool using_imgui = false);

    ~TextureSelector();


    /////////////////////////////////////////////////
    /// \brief is the user's mouse hovering over the texture selector?
    ///
    /// \return const bool&
    ///
    /////////////////////////////////////////////////
    const bool& getActive() const;
    const sf::Vector2u& getMaxSize() const;

    /////////////////////////////////////////////////
    /// \brief get the current selected texture rectangle
    ///
    /// \return const sf::IntRect&
    ///
    /////////////////////////////////////////////////
    const sf::IntRect& getTextureRect() const;
    const std::vector<sf::IntRect>& getTextureRects() const;
    bool getKeyTime();

    // Functions
    void update(const sf::Vector2i& MousePosWindow, const float& dt);
    /////////////////////////////////////////////////
    /// \brief Calculates the number of frames that have passed between inputs and checks to see if a minimum time value has been met
    /// before allowing another input
    ///
    /// \return bool
    ///
    /////////////////////////////////////////////////
    void updatekeytime(const float& dt);
    void render(sf::RenderTarget& target);
    bool hidden;
    std::vector<sf::IntRect> texture_rects;
};

class ProgressBar {

private:
    std::string hpbarText;
    sf::Text text;
    float Max_width;
    sf::RectangleShape Interior;
    sf::RectangleShape Exterior;
    sf::Texture texture;
    // sf::Sprite bar;
    int MaxVal;

public:

    /////////////////////////////////////////////////
    /// \brief constructs a GUI ProgressBar
    ///
    /// \param x screen position float
    /// \param y screen position float
    /// \param width float
    /// \param height float
    /// \param vm sf::VideoMode&
    /// \param inner_color sf::Color
    /// \param charSize unsigned
    /// \param nullptr sf::Font* font=
    ///
    /////////////////////////////////////////////////
    ProgressBar(float x, float y, float width, float height, sf::VideoMode& vm, sf::Color inner_color, unsigned charSize, sf::Font* font = nullptr);

    ~ProgressBar();

    void update(const int& current_value, const int& max_value);
    void render(sf::RenderTarget& target);



    /////////////////////////////////////////////////
    /// \brief get the pixel width of the progress bar
    ///
    /// \return const float&
    ///
    /////////////////////////////////////////////////
    const float& getWidth() const;

    /////////////////////////////////////////////////
    /// \brief get the pixel height and width of the progress bar
    ///
    /// \return const sf::Vector2f&
    ///
    /////////////////////////////////////////////////
    const sf::Vector2f& getSize();
};

class Icon {
public:
    /////////////////////////////////////////////////
    /// \brief constructs a GUI Icon
    ///
    /// \param x screen position float
    /// \param y screen position float
    /// \param icon_texture const std::string&
    ///
    /////////////////////////////////////////////////
    Icon(float x, float y, const std::string& icon_texture);
    virtual ~Icon();

    void render(sf::RenderTarget& target);

private:
    sf::RectangleShape Box;
    sf::Texture icontexture;
    sf::Sprite* IconBar;
};

}

#endif /* GUI_hpp */
