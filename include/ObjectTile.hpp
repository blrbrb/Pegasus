
#ifndef ObjectTile_hpp 
#define ObjectTile_hpp 
#include "Tile.hpp"

#include "AnimationComponet.hpp"
enum ObjectTypes { LANTERN = 64,  }; 

class ObjectTile : public Tile
{ 
public: 
    ObjectTile(float obX, float obY,sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect,short object_type);
    virtual ~ObjectTile(); 

    //Accessors 
    const std::string asString() const; 
    virtual const sf::Texture* getTexture() const; 
    virtual const sf::Vector2f& getObjectposition() const;

    //Functions 
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f LightPosition = sf::Vector2f()); 
    void update(const float& dt); 
  
   // virtual void set_texture
   // virtual void init_textures(); 
    //Modifiers 
    //void add_object(short type, sf::Vector2f& object_position); 
protected: 

  
    short object_type; 
    sf::Sprite object_rect;
    AnimationComponet* animationcomponent; 
    
private:  
   
    void create_animation_componet();
    virtual void initAnimations(); 
    sf::Texture texture; 
  
}; 
#endif 