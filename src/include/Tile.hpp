//
//  Tile.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Tile_hpp
#define Tile_hpp

#include "GUI.hpp"


/**
 * @enum TileTypes Types tile.
 */
enum TileTypes : int {
    /**
     * @brief default tile, no special properties or render order
     *
     */
    NORMAL = 0,
    /**
     * @brief tile with collision
     *
     */
    IMPASSABLE,
    /**
     * @brief tile to be rendered on a seperate layer
     *
     */
    OBJECT,
    /**
     * @brief tile with animations
     *
     */
    ANIMATED,
    /**
     * @brief tile that emits light
     *
     */
    LIGHT,
};

/**
 * @brieff  Base abstract tile object. Contains pure virtual method definitions for rendering, collisions, and basic on screen transformations
 * @class Tile()
 *
 */
class Tile {
private:
protected:
    sf::Sprite rect;
    short type;
    short object_type;
    unsigned gid;
    bool collison_enabled;

public:
    Tile ( sf::Texture* texture = nullptr );
    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param type short tiletype
    /// \param x float: the horizontal on screen pixel coordinate
    /// \param y float: the vertical on screen pixel coordinate
    /// \param gridsizeF sf::Vector2f:
    /// \param texture sf::Texture&: the tilesheet
    /// \param
    /// \return
    ///
    /////////////////////////////////////////////////
    Tile ( short type, float x, float y, sf::Vector2f gridsizeF, sf::Texture& texture, const sf::IntRect& textureRect, bool collisionEnabled = false );

    Tile (short type, sf::Vector2f& position, sf::Vector2f gridsizeF, sf::Texture& texture, const sf::IntRect& textureRect, bool collisionEnabled = false );
    //////////////
    /// @overload
    /// @brief construct a tile using a gid index value from a tiled tilemap file'
    /// the on screen pixel coordinates, and grid position of the tile will be calculated using the gid
    ///
    /// @param type p_type: TileType enum val
    /// @param gid p_gid: the tile's tiled gid'
    /// @param texture p_texture: the texture to source the tiles from
    /// @param collision_enabled p_collision_enabled: should this tile have collision?
    ///
    Tile ( short type, int gid, sf::Texture& texture, bool collisionEnabled = false );

    virtual ~Tile();

    // Accessors

   /**
   * @brief (depreciated) Stream the tile data in plaintext
   *
   * @return const std::string
   */
    virtual const std::string asString() const = 0;
    virtual const short& gettype() const;
    /**
     * @brief returns the current on screen (x,y) pixel coordinates of the tile's bounding rectangle
     *
     * @return const sf::Vector2f&
     */
    virtual const sf::Vector2f& getPosition() const;
    /**
     * @brief true if this tile has collision
     *
     * @return const bool&
     */
    virtual const bool& getCollision() const;
    /**
     * @brief returns true if the tile's bounding rectangle is within a bounds'
     *
     * @param bounds sf::FloatRect: The bounding rectangle of the object to compare
     * @return const bool
     */
    virtual const bool intersects ( const sf::FloatRect bounds ) const;
    /**
     * @brief returns the tile's bounding rectangle'
     *
     * @return const sf::FloatRect
     */
    virtual const sf::FloatRect getGlobalBounds() const;
    /**
     * @brief returns the current on screen (x,y) pixel coordinates of the tile's center'
     *
     * @return const sf::Vector2f
     */
    virtual const sf::Vector2f getCenter() const;
    /**
     * @brief returns the tile's texture rectangle within the current texture sheet'
     *
     * @return const sf::IntRect
     */
    virtual const sf::IntRect getTextureRect() const;
    virtual const short& getObjectType() const;
    virtual void savetoFile ( std::ofstream& out ) = 0;
    /**
     * @brief returns the tiled gid of the current tile'
     *
     * @return const unsigned int&
     */
    virtual const unsigned& getGid() const;

    /**
     * @brief
     *
     * @param
     * @param
     * @param
     */


    /////////////////////////////////////////////////
    /// \brief calculates the tile gid of the tile based on the tile's position within the texture sheet'
    ///
    /// \param tileCoords sf::Vector2i: current on screen (x,y) pixel coordinates of the tile
    /// \param tileSize sf::Vector2i:  the size of an individual tile on the tilemap (grid size)
    /// \param textureSize sf::Vector2u: the (x,y) pixel size of the tilesheet texture
    /// \return
    ///
    /////////////////////////////////////////////////
    virtual void calcGid ( sf::Vector2i tileCoords, sf::Vector2i tileSize, sf::Vector2u textureSize );



    // Functions
    virtual void update ( const float& dt ) = 0;
    virtual void render ( sf::RenderTarget& target, sf::Shader* shader = nullptr, sf::Vector2f LightPosition = sf::Vector2f() ) = 0;


};

#endif /* Tile_hpp */
