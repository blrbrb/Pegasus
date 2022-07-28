
#ifndef ObjectTile_hpp 
#define Object_Tile_hpp 
#include "Tile.hpp"

class Tile;

class ObjectTile : public Tile
{ 
public: 
    ObjectTile(short type, int x, int y, float obX, float obY, sf::Vector2f gridsize_f,short object_type, bool collision_enabled = false);
    virtual ~ObjectTile(); 

    //Accessors 
    const std::string asString() const; 
  


    //Functions 
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f LightPosition = sf::Vector2f()); 
   virtual void update(); 
   // virtual void set_texture
   // virtual void init_textures(); 
    //Modifiers 
    //void add_object(short type, sf::Vector2f& object_position); 

private:  
   
    //Object* object;
   // Object* object;
   // short objecttype; 
    //bool hasobject;
}; 
#endif 