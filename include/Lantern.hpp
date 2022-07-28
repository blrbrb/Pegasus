#ifndef Lantern_hpp
#define Lantern_hpp
#include "Object.hpp"

class Entity; 

class Lantern :
    public Object 
{ 
public: 

    Lantern(float x, float y);
    virtual ~Lantern(); 

    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light = sf::Vector2f(), const bool render_hitbox = false);

    void update(const float& dt,sf::Vector2f& MousePosView);

    void updateAnimation(const float& dt);  

    //Acessors 
    const std::string asString() const;
private: 
    void initanimations(); 
    void initvariables(); 
  
    // Inherited via Object
   
};

#endif