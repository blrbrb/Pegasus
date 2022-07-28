#ifndef ObjectHandler_hpp 
#define ObjectHandler_hpp 

#include "Object.hpp"
#include "Lantern.hpp"




class ObjectHandler
{
public:

    //variables

    

    ObjectHandler(std::vector<Object*>& Objects, std::map<std::string, sf::Texture>& textures);
    virtual ~ObjectHandler();

    //Accessors


    //Functions
    void Place_Object(short type, const float x, const float y);
    void Remove_Object(const int index);

   void update(const float& dt);

    void render(sf::RenderTarget* target);
    std::vector<Object*>& Objects;
    //Acessors 
    const int getSize();
private:

    void init_textures(); 
    std::map<std::string, sf::Texture>& textures;
   
    

protected:

    
};

#endif /* ObjectHandler_hpp */


