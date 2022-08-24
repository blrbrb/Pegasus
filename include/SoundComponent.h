#ifndef SoundComponent_h
#define SoundComponent_h

class SoundComponent
{
public:

    SoundComponent();
    virtual ~SoundComponent();
    
        void add_sound(const std::string & key, float timer, sf::SoundBuffer& buffer);

    /**
                @brief Play the animation
                @param the name of the animation, delta time, (bool) priority
                @returns a constant boolean value representing wether or not the animation has finished playing
     */
    
    const bool& play(const std::string& key, const float& dt, const float& speed); 
    const bool stop(const std::string& key);
    void update(const float& dt);

    //Accessors
    const bool& getDone(const std::string key);




private:
    class Sound {



    public:

        sf::SoundBuffer& sound_buffer; 
        sf::Sound sound; 
     
        bool done;
        float soundtimer; 
        float timer;
        float speed;

        Sound(sf::SoundBuffer& sound_buffer, float soundtimer) :
            sound_buffer(sound_buffer), soundtimer(soundtimer), timer(0.f), done(false)
        {
            this->sound.setBuffer(this->sound_buffer); 

        }

        const bool& play(const float& dt)
        {
            this->done = false;
            this->timer += 100.f * dt;

            if (this->timer >= this->soundtimer)
            {
                //clear the timer
                this->timer = 0.f;

                this->sound.play(); 

   
                //play the sound 
               
            }
            return this->done;
        }

        const bool& play(const float& dt, float speed_percent)
        {

            if (speed_percent < 0.f)
            {
                speed_percent = 0.5f;
            }

            this->done = false;
            this->timer += speed_percent * 100.f * dt;

            if (this->timer >= this->soundtimer)
            {
                //clear the timer
                this->timer = 0.f;

                //start the sound
                

                this->sound.play(); 
                

                //play the sound 
               
            }
            return this->done;
        }



        void reset()
        {
            this->timer = 0.f;
            
        }




        const bool& getDone() const
        {
            return this->done;

        }



    };

    std::map<std::string, Sound*> sounds;



};
#endif //SoundComponent_hpp
