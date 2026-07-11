//
//  AnimationManager.hpp
//
//
//  Created by Eli Reynolds on 1/30/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef AnimationManager_hpp
#define AnimationManager_hpp
#include <SFML/Graphics.hpp>
#include <map>


class AnimationManager
 {

private:
    /**
     * @struct Animation
     * @brief represents an ordered sequence of sf::IntRects
     *
     */
    class Animation {

    public:
        sf::Sprite& sprite;
        sf::Texture& texturesheet;
        sf::IntRect startRect;
        sf::IntRect currentrect;
        sf::IntRect endRect;
        bool done;
        int width;
        int height;
        float animationtimer;
        float timer;
        int start_x;
        int start_y;
        int end_x;
        int end_y;
        float speed;

        /////////////////////////////////////////////////
        /// \brief Animation
        ///
        /// \param texturesheet sf::Texture&
        /// \param sprite sf::Sprite&
        /// \param animationtimer float
        /// \param start_x int
        /// \param start_y int
        /// \param end_x int
        /// \param end_y int
        /// \param width int
        /// \param height int
        ///
        /////////////////////////////////////////////////
        Animation(sf::Texture& texturesheet, sf::Sprite& sprite, float animationtimer, int start_x, int start_y, int end_x, int end_y, int width, int height)
            : sprite(sprite)
             , done(false)
            , texturesheet(texturesheet)
            , width(width)
            , height(height)
            , animationtimer(animationtimer)
            , timer(0.f)
            , start_x(start_x)
            , start_y(start_y)
            , end_x(end_x)
            , end_y(end_y)

        {
            this->width = width;
            this->height = height;

            this->startRect = sf::IntRect(sf::Vector2i(start_x * width, start_y * height), sf::Vector2i(width, height));
            this->currentrect = startRect;
            this->endRect = sf::IntRect(sf::Vector2i(end_x * width, end_y * height), sf::Vector2i(width, height));

            this->sprite.setTexture(this->texturesheet, true);
            this->sprite.setTextureRect(this->startRect);
        }



        /////////////////////////////////////////////////
        /// \brief play the animation
        ///
        /// \param dt const float&
        /// \return const bool&
        ///
        /////////////////////////////////////////////////
        const bool& play(const float& dt)
        {
            this->done = false;
            this->timer += 100.f * dt;

            if (this->timer >= this->animationtimer) {
                // clear the timer
                this->timer = 0.f;

                // start the animation
                if (this->currentrect != this->endRect) {
                    this->currentrect.position.x += this->width;
                }

                else // restart the animation
                {
                    this->done = true;
                    this->currentrect.position.x = this->startRect.position.x;
                }

                this->sprite.setTextureRect(this->currentrect);
            }
            return this->done;
        }


        /////////////////////////////////////////////////
        /// \brief play the animation at a specified speed
        /// \param dt const float&
        /// \param speed_percent float
        /// \return const bool&
        ///
        /////////////////////////////////////////////////
        const bool& play(const float& dt, float speed_percent)
        {

            if (speed_percent < 0.f) {
                speed_percent = 0.5f;
            }

            this->done = false;
            this->timer += speed_percent * 100.f * dt;

            if (this->timer >= this->animationtimer) {
                // clear the timer
                this->timer = 0.f;

                // start the animation
                if (this->currentrect != this->endRect) {
                    this->currentrect.position.y += this->width;
                }

                else // restart the animation
                {
                    this->currentrect.position.y = this->startRect.position.y;
                    this->done = true;
                }

                this->sprite.setTextureRect(this->currentrect);
            }
            return this->done;
        }


        /////////////////////////////////////////////////
        /// \brief resets the animation timer to zero
        ///
        /// \return void
        ///
        /////////////////////////////////////////////////
        void reset()
        {
            this->timer = 0.f;
            this->currentrect = this->startRect;
        }



        /////////////////////////////////////////////////
        /// \brief true if the animation has finished playing all of it's frames
        ///
        /// \return const bool&
        ///
        /////////////////////////////////////////////////
        const bool& getDone() const
        {
            return this->done;
        }

        /////////////////////////////////////////////////
        /// \brief the current delta time since the animation began playing
        ///
        /// \return const float&
        ///
        /////////////////////////////////////////////////
        const float& getTimer() const
        {
            return this->animationtimer;
        }
        /////////////////////////////////////////////////
        /// \brief the first frame's X position
        ///
        /// \return const int& const
        ///
        /////////////////////////////////////////////////
        const int& getStartRectLeft() const
        {
            return this->startRect.position.y;
        }
        /////////////////////////////////////////////////
        /// \brief the first frame's Y position
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getStartRectTop() const
        {
            return this->startRect.position.y;
        }
        /////////////////////////////////////////////////
        /// \brief the first frame's width
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getStartRectWidth() const
        {
            return this->startRect.size.x;
        }
        /////////////////////////////////////////////////
        /// \brief the first frame's height
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getStartRectHeight() const
        {
            return this->startRect.size.y;
        }
        /////////////////////////////////////////////////
        /// \brief the last frame's X position
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getEndRectLeft() const
        {
            return this->endRect.position.x;
        }
        /////////////////////////////////////////////////
        /// \brief the last frame's Y position
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getEndRectTop() const
        {
            return this->endRect.position.y;
        }
        /////////////////////////////////////////////////
        /// \brief the last frame's width
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getEndRectWidth() const
        {
            return this->endRect.size.x;
        }
        /////////////////////////////////////////////////
        /// \brief the last frame's height
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getEndRectHeight() const
        {
            return this->endRect.size.y;
        }
        /////////////////////////////////////////////////
        /// \brief the width of a frame
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getAnimationWidth() const
        {
            return this->width;
        }
        /////////////////////////////////////////////////
        /// \brief the height of a frame
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getAnimationHeight() const
        {
            return this->height;
        }
        /////////////////////////////////////////////////
        /// \brief the first frame's X index
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getStartX() const
        {
            return this->startRect.position.x / this->width;
        }
        /////////////////////////////////////////////////
        /// \brief the first frame's Y index
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getStartY() const
        {
            return this->startRect.position.y / this->height;
        }
        /////////////////////////////////////////////////
        /// \brief the last frame's X index
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getEndX() const
        {
            return this->endRect.position.y / this->width;
        }
        /////////////////////////////////////////////////
        /// \brief the last frame's Y index
        ///
        /// \return const int&
        ///
        /////////////////////////////////////////////////
        const int& getEndY() const
        {
            return this->endRect.position.y / this->height;
        }


    };

    std::map<std::string, Animation*> animations;

    sf::Sprite& sprite;
    sf::Texture& texturesheet;

    std::vector<std::string> names;
    Animation* lastAnimation;
    Animation* priorityAnimation;

public:
    /////////////////////////////////////////////////
    /// \brief The animation manager
    /// stores many individual animation objects in a map
    /// \param sprite sf::Sprite&
    /// \param texturesheet sf::Texture&
    ///
    /////////////////////////////////////////////////
    AnimationManager (sf::Sprite& sprite, sf::Texture& texturesheet);
    virtual ~AnimationManager();


    void add_animation(const std::string& key, float animationtimer, int start_x, int start_y, int end_x, int end_y, int width, int height);

    /**
                @brief Play the animation
                @param the name of the animation, delta time, (bool) priority
                @returns a constant boolean value representing wether or not the animation has finished playing
     */
    const bool& play(const std::string& key, const float& dt, const bool priority = false);
    /////////////////////////////////////////////////
    /// \brief play the animation within a set speed range
    ///
    /// \param key const std::string&
    /// \param dt const float&
    /// \param speed const float&
    /// \param speed_max const float&
    /// \param const bool priority = false
    /// \return const bool&
    ///
    /////////////////////////////////////////////////
    const bool& play(const std::string& key, const float& dt, const float& speed, const float& speed_max, const bool priority = false);
    void update(const float& dt);


    /////////////////////////////////////////////////
    /// \brief true if the animation at [key] has finished playing
    ///
    /// \param key const std::string&
    /// \return const bool&
    ///
    /////////////////////////////////////////////////
    const bool& getDone(const std::string& key);


    const std::string& getName(int index);
    /////////////////////////////////////////////////
    /// \brief the width of the animation at [index]
    ///
    /// \param index int
    /// \return const int&
    ///
    /////////////////////////////////////////////////
    const int& getWidth(int index);
    /////////////////////////////////////////////////
    /// \brief the height of the animation at [index]
    ///
    /// \param index int
    /// \return const int&
    ///
    /////////////////////////////////////////////////
    const int& getHeight(int index);

    /////////////////////////////////////////////////
    /// \brief the first frame's X position at [index]
    ///
    /// \param index int
    /// \return const int&
    ///
    /////////////////////////////////////////////////
    const int& getStartRectLeft(int index);
    /////////////////////////////////////////////////
    /// \brief the first frame's Y position at [index]
    ///
    /// \param index int
    /// \return const int&
    ///
    /////////////////////////////////////////////////
    const int& getStartRectTop(int index);
    /////////////////////////////////////////////////
    /// \brief the first frame's width
    ///
    /// \param index int
    /// \return const int&
    ///
    /////////////////////////////////////////////////
    const int& getStartRectWidth(int index);
    /////////////////////////////////////////////////
    /// \brief the first frame's height
    ///
    /// \param index int
    /// \return const int&
    ///
    /////////////////////////////////////////////////
    const int& getStartRectHeight(int index);
    /////////////////////////////////////////////////
    /// \brief the time passed since the animation at [index] began playing
    ///
    /// \param index int
    /// \return const float&
    ///
    /////////////////////////////////////////////////
    const float& getTimer(int index);

    ///@params index the iterator used to access a specific animation in the map.
    const int& getEndRectLeft(const std::string& key);
    const int& getEndRectTop(const std::string& key);
    const int& getEndRectWidth(const std::string& key);
    const int& getEndRectHeight(const std::string& key);
    [[nodiscard]] const int& getSize() const;
    [[nodiscard]] const int& getStartX(const std::string& key) const;
    [[nodiscard]] const int& getStartY(const std::string& key) const;
    [[nodiscard]] const int& getEndX(const std::string& key) const;
    [[nodiscard]] const int& getEndY(const std::string& key) const;
};

#endif /* AnimationComponet_hpp */
