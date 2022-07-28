#ifndef Object_hpp
#define Object_hpp 

#include "Entity.hpp"
#include "ObjectTile.hpp"

enum ObjectTypes { EMPTY = 0, LANTERN };
class Entity;

class Object : public Entity
{
public:

    Object();
    Object(float x, float y);
    virtual ~Object();

    virtual void update(const float& dt, sf::Vector2f& MousePosView) = 0;

    virtual void updateAnimation(const float& dt) = 0;

    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light = sf::Vector2f(), const bool render_hitbox = false) = 0;


    //Acessors
    //virtual const short& gettype() const; 
    virtual const std::string asString() const = 0;

protected:

    //child class variables
    std::string name;
    sf::Sprite rect;
    sf::Texture texture; 
    std::map<std::string, sf::Texture> textures; 

    short type;
    bool is_object;
    //ObjectTile& tile;

private:
    //initalizer functions
    void inittextures(); 
    
   
   
 
   

};

#endif /* Object_hpp */

