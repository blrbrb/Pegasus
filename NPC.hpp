#ifndef NPC_hpp 
#define NPC_hpp 
#include "Entity.hpp"

//Abstraction of the Entity class that will be used to build NPC ponies 

class NPC :
    public Entity 
{
public: 

    NPC(); 
    virtual ~NPC(); 

    void update(const float& dt, sf::Vector2f& MousePosView);

    void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light, const bool render_hitbox);

  
    void updateAnimation(const float& dt); 
private:
    
    void initvariables();
    void initcomponets();
    void initanimations();
    void initinventory(); 

};

#endif 