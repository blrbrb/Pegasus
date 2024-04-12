#ifndef LevelManagerMode_hpp 
#define LevelManagerMode_hpp  

#include "EditorModes.hpp"
class LevelManagerMode :
    public EditorModes
{

public: 

    LevelManagerMode(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata, Levels* levels = nullptr);
    virtual ~LevelManagerMode(); 



    // Inherited via EditorModes
    virtual void updateInput(const float& dt) override; 

    virtual void update(const float& dt) override;

    virtual void updateGUI(const float& dt) override;

    virtual void renderGUI(sf::RenderTarget& target) override;

    virtual void render(sf::RenderTarget& target) override;

  


private: 
    void initvariables(); 
    

};

#endif LevelManagerMode_hpp