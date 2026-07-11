//
//  NormalTile.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef NormalTile_hpp
#define NormalTile_hpp
#include "Tile.hpp"

class Tile;

/////////////////////////////////////////////////
/// \brief a normal tile with no special properties
/////////////////////////////////////////////////
class NormalTile : public Tile
{

public:
    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param type short
    /// \param x float
    /// \param y float
    /// \param gridsize_f sf::Vector2f
    /// \param texture sf::Texture&
    /// \param texturerect const sf::IntRect&
    /// \param false bool collision_enabled=
    ///
    /////////////////////////////////////////////////
    NormalTile(short type, float x, float y, sf::Vector2f gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled = false);

    /////////////////////////////////////////////////
    ///
    /// \overload
    /// \param type short
    /// \param guid short
    /// \param gridsize_f sf::Vector2f
    /// \param texture sf::Texture&
    /// \param false bool collision_enabled=
    ///
    /////////////////////////////////////////////////
    NormalTile(short type,short guid, sf::Vector2f gridsize_f, sf::Texture& texture,bool collision_enabled = false);
    virtual ~NormalTile();


    /////////////////////////////////////////////////
    /// \brief get the bounding rectangle of the tile
    ///
    /// \return const sf::FloatRect
    ///
    /////////////////////////////////////////////////
    const sf::FloatRect getGlobalBounds() const override;

    /////////////////////////////////////////////////
    /// \brief stream the tile in plaintext
    /// \deprecated
    /// \return const std::string
    ///
    /////////////////////////////////////////////////
    const std::string asString() const override;

    /////////////////////////////////////////////////
    /// \brief save the tile in plaintext
    /// \deprecated
    /// \param in std::ofstream&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void savetoFile(std::ofstream& in) override;



    void update(const float& dt) override;
    void render(sf::RenderTarget & target, sf::Shader* shader = nullptr, sf::Vector2f LightPosition = sf::Vector2f()) override;

    //Modifiers
    /////////////////////////////////////////////////
    /// \brief add an object to the tile (unimplemented)
    ///
    /// \param type short
    /// \param object_position sf::Vector2f&
    /// \return void
    ///
    /////////////////////////////////////////////////
    void add_object(short type, sf::Vector2f& object_position);
protected:




};

#endif /* NormalTile_hpp */
