//
//  AnimationComponet.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/30/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//


#ifndef AnimationComponet_hpp
#define AnimationComponet_hpp


/**
    
 @brief When applied to an object, can be used to stitch a spritesheet into a working animation
 
 
 */
class AnimationComponet {
    
private:
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

        Animation(sf::Texture& texturesheet, sf::Sprite& sprite, float animationtimer, int start_x, int start_y, int end_x, int end_y, int width, int height) :
            sprite(sprite), texturesheet(texturesheet), width(width), height(height), animationtimer(animationtimer), timer(0.f), done(false), start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y)
        {
            this->width = width;
            this->height = height;
           
            this->startRect = sf::IntRect(start_x * width, start_y * height, width, height);
            this->currentrect = startRect;
            this->endRect = sf::IntRect(end_x * width, end_y * height, width, height);


            this->sprite.setTexture(this->texturesheet, true);
            this->sprite.setTextureRect(this->startRect);

        }


        //*Functions*

        const bool& play(const float& dt)
        {
            this->done = false;
            this->timer += 100.f * dt;

            if (this->timer >= this->animationtimer)
            {
                //clear the timer
                this->timer = 0.f;

                //start the animation
                if (this->currentrect != this->endRect)
                {
                    this->currentrect.left += this->width;
                }


                else //restart the animation
                {
                    this->done = true;
                    this->currentrect.left = this->startRect.left;
                }


                this->sprite.setTextureRect(this->currentrect);
            }
            return this->done;
        }

        ///Overloaded play function with user-definable animation speed parameters
        const bool& play(const float& dt, float speed_percent)
        {

            if (speed_percent < 0.f)
            {
                speed_percent = 0.5f;
            }

            this->done = false;
            this->timer += speed_percent * 100.f * dt;

            if (this->timer >= this->animationtimer)
            {
                //clear the timer
                this->timer = 0.f;

                //start the animation
                if (this->currentrect != this->endRect)
                {
                    this->currentrect.left += this->width;
                }


                else //restart the animation
                {
                    this->currentrect.left = this->startRect.left;
                    this->done = true;
                }


                this->sprite.setTextureRect(this->currentrect);
            }
            return this->done;
        }


        void reset()
        {
            this->timer = 0.f;
            this->currentrect = this->startRect;


        }

        //*End Functions*

        //*Accessors*
        //There needs to be a much much more efficent way to access all of these private class values. 
        //fuckin return a struct that contains all of the animation data in a single object or something man idk 
        ///The player's controllable character should resemble as closely as possible the framewidth inbetween movements to appear like friendship is magic 
        //don't fuck around with the float timer please. 
        //that means you, kenneth. 
        
        
      
                                                                                                                                                                                                                                             
        const bool& getDone() const
        {
            return this->done;

        }

        const float& getTimer() const 
        {
            return this->animationtimer;
        }

        const int& getStartRectLeft() const
        {
            return this->startRect.left;

        }
        const int& getStartRectTop() const 
        {
            return this->startRect.top;
        }       
        const int& getStartRectWidth() const
        {
            return this->startRect.width;
        }
        const int& getStartRectHeight() const
        {
            return this->startRect.height;
        }
        const int& getEndRectLeft() const
        {
            return this->endRect.left;

        }
        const int& getEndRectTop() const
        {
            return this->endRect.top;
        }
        const int& getEndRectWidth() const
        {
            return this->endRect.width;
        }
        const int& getEndRectHeight() const
        {
            return this->endRect.height;
        }
        const int& getAnimationWidth() const
        {
            return this->width;
        }
        const int& getAnimationHeight() const
        {
            return this->height;
        }
        const int& getStartX() const
        {
            return this->startRect.left / this->width;
        }
        const int& getStartY() const
        {
            return this->startRect.top / this->height;
        }
        const int& getEndX() const
        {
            return this->endRect.left / this->width; 
        }
        const int& getEndY() const
        {
            return this->endRect.top / this->height;
        }
        
        //*End Accessors*
    };
    
    
    ///Why are we using an external library for the animation container? We could make a pretty decent one with std::map? 
    //is there an issue with the unordered nature of the maps? Would vectors be a better use case here? 
    typedef boost::bimaps::bimap<std::string, Animation*> animations;
    typedef boost::bimaps::bimap<std::string, Animation*>::value_type animation;
    typedef boost::bimaps::bimap<std::string, Animation*>::left_map::iterator name;
    typedef boost::bimaps::bimap<std::string, Animation*>::right_map::iterator data; 
    
    ///
    sf::Sprite& sprite;
    sf::Texture& texturesheet;
   

    animations Animations;
    ///i.e right here, the names of the animations are being indexed. See Pony.xml, where they aren't stored with a string name at all
    std::vector<std::string> names;
    Animation* lastAnimation;
    Animation* priorityAnimation;





public:
    
   
    AnimationComponet(sf::Sprite& sprite, sf::Texture& texturesheet);
    virtual ~AnimationComponet();
    
    /**
        @brief Is called in order to add an animation to an object. The new animation is stored in a map container, and can be fetched with the play animation function
        @param A string naming the animation, how fast to 
 the animation, the start X frame, the Start Y frame, the End X frame, the End Y Frame, the width of the Frame(s), the height of the Frame(s)
        @returns void
     
     */
     void add_animation(const std::string& key,float animationtimer,int start_x, int start_y, int end_x, int end_y, int width, int height);
    
    /**
                @brief Play the animation
                @param the name of the animation, delta time, (bool) priority
                @returns a constant boolean value representing wether or not the animation has finished playing
     */
     const bool& play(const std::string& key, const float& dt, const bool priority = false);
     const bool& play(const std::string& key, const float& dt, const float& speed, const float& speed_max, const bool priority = false);
     void update(const float& dt);
    
    //Accessors
     const bool& getDone(const std::string key); 
     const std::string& getName(int index); 
     const int& getWidth(int index);
     const int& getHeight(int index);

    
       
     const int& getStartRectLeft(int index);
     const int& getStartRectTop(int index);
     const int& getStartRectWidth(int index);
     const int& getStartRectHeight(int index);
     const float& getTimer(int index);
    
     ///@params index the iterator used to access a specific animation in the map. 
     const int& getEndRectLeft(int index);
     const int& getEndRectTop(int index);
     const int& getEndRectWidth(int index);
     const int& getEndRectHeight(int index);
     const int& getSize() const; 
     const int& getStartX(int index) const;
     const int& getStartY(int index) const;
     const int& getEndX(int index) const;
     const int& getEndY(int index) const;

    
    

};

#endif /* AnimationComponet_hpp */
