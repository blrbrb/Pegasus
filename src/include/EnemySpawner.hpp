//
//  EnemySpawner.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef EnemySpawner_hpp
#define EnemySpawner_hpp
#include "Tile.hpp"

class Tile;

class EnemySpawner : public Tile
{
    
private:
    
    
    sf::Vector2i gridPosition;
    sf::RectangleShape tile; 
    int Enemy_type;
    int Enemy_amount;
    int Enemy_counter;
    sf::Clock SpawnTimer;
    sf::Int32 timer;
    float maxDistance;
    bool Spawned;  

  
    
public:
    //construtor and destructor
    EnemySpawner(float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, int type, int amount, sf::Int32 time_to_spawn, float max_distance);
    virtual ~EnemySpawner();
  
    //modifiers
    void SetSpawned(const bool spawned);  
    void add_object(short type, sf::Vector2f& object_position); 
    
    //Accessors
    const std::string asString() const;
    void savetoFile(std::ofstream& out);
  
    const bool& getSpawned() const;
    const int& getEnemyAmount() const;
    const int& getEnemyCounter() const; 
    const float& getMaxDistance() const; 
    const int& getEnemyType() const ;
    const sf::Int32& getTime() const; 
    //Functions
    const bool canSpawn() const;
    void increaseEnemyCounter();
    void decreaseEnemyCounter();
    
    void clear();
    void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f LightPosition = sf::Vector2f());
    

    // Inherited via Tile
    

};

#endif /* EnemySpawner_hpp */

