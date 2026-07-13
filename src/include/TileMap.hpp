//
//  TileMap.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef TileMap_hpp
#define TileMap_hpp



#include "Entity.hpp"
#include "NormalTile.hpp"
#include "ObjectTile.hpp"
#include "Tile.hpp"
#include "easylogging++.h"
#include "tinyxml2.h"

class EnemySpawner;
class Tile;
class NormalTile;

class Entity;
/////////////////////////////////////////////////
/// \brief tilemap
/////////////////////////////////////////////////

class TileMap {
private:

    int layers;
    sf::Vector2i gridsizeI;
    sf::Vector2f grid_sizeF;
    sf::Vector2u grid_sizeU;
    size_t texturefilesize;

    std::string texture_file;
    sf::Vector2i MaxSizeWorldGrid;
    sf::Vector2f MaxSizeWorld_F;


    std::stack<Tile*> renderdefered;

    sf::RectangleShape physicsrect;

    // TileMap vector
    /////////////////////////////////////////////////
    /// \brief tile data container  Map[x][y][z][layer]
    ////////////////////////////////////
    std::vector<std::vector<std::vector<std::vector<Tile*>>>> Map;

    sf::Font font;
    sf::Texture tileTextureSheet;
    sf::Texture tilegenerationSheet;

    //unimplemented
    std::map<std::string, sf::Texture> object_textures;
    //unimplemented
    std::map<std::string, sf::Vector2i> geometry;

    //for saving tile collision prop reading from .tmx files
    //TD find a better way to do this
    std::map<int, bool> collisionGIDRegister;
    /////////////////////////////////////////////////
    /// \brief erase all data
    ///
    /// \return void
    ///
    /////////////////////////////////////////////////
    void clear();
    void initobjecthandler();
    void initgeometry();
    void initvariables();
    void initloggingthread();


    // tile culling
    int FromX;
    int ToX;
    int ToY;
    int FromY;
    int layer;

public:

    /////////////////////////////////////////////////
    /// \brief create an empty tilemap
    ///
    /// \param gridSize sf::Vector2f
    /// \param width int
    /// \param height int
    /// \param texture_file any object resolvable to std::filesystem::path
    /// \return
    ///
    /////////////////////////////////////////////////
    TileMap ( sf::Vector2f gridSize, int width, int height, std::string texture_file );


    /////////////////////////////////////////////////
    /// \brief load tile data from a plaintext file
    /// \deprecated
    /// \param map_file any object resolvable to std::filesystem::path
    /////////////////////////////////////////////////
    TileMap(const std::string map_file);

    TileMap();
    virtual ~TileMap();

    // Variables
    bool lock_layer;
    bool isEntityColliding;

    // Accessors


    /////////////////////////////////////////////////
    /// \brief the source texture for the tiles
    ///
    /// \return const sf::Texture*
    ///
    /////////////////////////////////////////////////
    const sf::Texture* getTileSheet() const;


    /////////////////////////////////////////////////
    /// \brief true if there are no tiles at x,y,z
    /// \param x const int
    /// \param y const int
    /// \param z const int
    /// \return const bool const
    ///
    /////////////////////////////////////////////////
    const bool TileEmpty ( const int x, const int y, const int z ) const;

    /////////////////////////////////////////////////
    /// \brief the tile type of tile at x,y,z
    /// \param x const int
    /// \param y const int
    /// \param z const int
    /// \param type const int
    /// \see TileTypes
    /// \return
    ///
    /////////////////////////////////////////////////
    const bool checktype ( const int x, const int y, const int z, const int type ) const;


    /////////////////////////////////////////////////
    /// \brief how many tiles are placed at x,y,layer
    ///
    /// \param x const int
    /// \param y const int
    /// \param z const int
    /// \return
    ///
    /////////////////////////////////////////////////
    const int getLayerSize ( const int x, const int y, const int layer ) const;


    const std::vector<int> getLayer(const int& layer) const;

    /////////////////////////////////////////////////
    /// \brief the maximum size of the tilemap
    /// (how many tiles span the width and height)
    ///
    /// \return const sf::Vector2i&
    ///
    /////////////////////////////////////////////////
    const sf::Vector2i& getMaxSizeGrid() const;


    /////////////////////////////////////////////////
    /// \brief the maximum pixel size of the tilemap
    ///  (the pixel width and height)
    /// \return const sf::Vector2f
    ///
    /////////////////////////////////////////////////
    const sf::Vector2f getMaxSize() const;

    const sf::Vector2f get_objectTile();

    // render functions

    void render ( sf::RenderTarget& target, const sf::View& view, const sf::Vector2i& gridposition, const bool render_collision = false, sf::Shader* shader = NULL, const sf::Vector2f PlayerPosition = sf::Vector2f() );


    void defferedRender ( sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f PlayerPosition = sf::Vector2f() );


   /////////////////////////////////////////////////
   /// \brief add a tile at position x, y, layer z
   ///
   /// \param x const int
   /// \param y const int
   /// \param z const int
   /// \param texture_rect the texture rect of the tile to place sf::IntRect
   /// \param collision if the tile should have collision const bool&
   /// \param type the type of tile to place const short&
   /// \return
   /////////////////////////////////////////////////
   void addTile ( const int x, const int y, const int z, const sf::IntRect texture_rect, const bool& collision, const short& type );


   void addTile ( const int x, const int y, const int z, float obX, float obY, const short type );


   void addObject ( const short type, const int x, const int y );

   /////////////////////////////////////////////////
   /// \brief automatically calculate the texture rectangle for a tile within a tilesheet given it's gid
   ///
   /// \param gid the gid of the tile const int&
   /// \param tileSize the size of an individual tile sf::Vector2i
   /// \return
   ///
   /////////////////////////////////////////////////
   sf::IntRect calcTileRect ( const int& gid, sf::Vector2i tileSize );





  /////////////////////////////////////////////////
  /// \brief remove a tile at position x,y, layer z
  /// \param x tilemap grid X position const int
  /// \param y tilemap grid Y position const int
  /// \param z tilemap layer const int
  /// \param type of tile to place const int
  /// \return
  ///
  /////////////////////////////////////////////////
  void removeTile ( const int x, const int y, const int z, const int type );

  /////////////////////////////////////////////////
  /// \brief write tilemap data in plaintext
  /// \deprecated
  /// \param filename anything resolvable to std::filesystem::path
  /// \return bool
  ///
  /////////////////////////////////////////////////
  // TODO (): make use of std::optional ...
  //
  bool saveToFile ( const std::string& filename );

   /////////////////////////////////////////////////
   /// \brief write the tilemap in csv format to a .tmx file
   /// compatible with tiled
   /// \param filename anything resolvable to const std::filesystem::path&
   /// \return
   ///
   /////////////////////////////////////////////////
   bool exportTMX ( const std::filesystem::path& filename );
   bool importTMX ( const std::filesystem::path& filename );


   /////////////////////////////////////////////////
   /// \brief load the tilemap from plaintext
   /// \deprecated
   /// \param
   /// \param
   /// \return bool
   ///
   /////////////////////////////////////////////////
   bool loadFromFile ( const std::string filename );

   const std::vector<Tile*>& getLayer();


   /////////////////////////////////////////////////
   /// \brief update the tilemap
   /// calls both updateWorldBoundsCollision and updateTiles
   ///
   /// \param entity the entity to check against
   /// \param dt delta-time const float&
   /// \return
   ///
   /////////////////////////////////////////////////
   void update ( Entity* entity, const float& dt );

   /////////////////////////////////////////////////
   /// \brief update global collision
   ///
   /// \param entity entity to check against Entity*
   /// \param dt delta-time const float&
   ///
   /////////////////////////////////////////////////
   void updateWorldBoundsCollision ( Entity* entity, const float& dt );

   void updateTiles ( Entity* entity, const float& dt );

   /////////////////////////////////////////////////
   /// \brief update collision between an entity and individual tiles with a collision property
   ///
   /// \param entity entity to check against Entity*
   /// \param dt delta-time const float&
   ///
   /////////////////////////////////////////////////
   void updateTileCollision ( Entity* entity, const float& dt );



};

#endif /* TileMap_hpp */
