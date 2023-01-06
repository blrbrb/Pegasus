#pragma once
#ifndef AudioComponent_h
#define AudioComponent_h 
#include <SFML/Audio.hpp>
namespace Sound {

	enum Tracks { wipe_away_those_tears = 0, rainbowrush, all_my_love_to_you, magic_rainbow, happy_tune, forget_me_not_in_f_major_loop, forget_me_not_in_f_major, christmas_synths };

	struct SoundSystem {};

	class MusicPlayer

	{
	public:

		MusicPlayer();
		virtual ~MusicPlayer();

		void add_music(std::string key, sf::SoundBuffer& buffer);

		const bool& play(int key);
		const bool& playing();
		const bool& paused();
		const bool& stopped();
		const bool getPlayInterval();
		void set_volume(float volume);

		const std::string& current_track_title();

		const int current_track_no();

		void skip();

		void play_context();
		void play_random();
		void pause();
		void stop();
		void set_speed(float sp);
		void update(const float& dt);

		void update_interval(const float& dt);


		//fetch the sound buffer from the key and move it from private storage

		//Song current();

	private:
		std::map<int, std::string> songs;
		//std::vector<std::string> titles;
		sf::Clock clock;
		sf::Music music;
		bool initmusic();
		float playtime;
		float playtime_max;

		float playtime_interval;
		float playtime_intervalMax;
	};   



	class Speaker 
	{
	public: 
		Speaker(sf::Sound& sound, sf::SoundBuffer& buffer);
		virtual ~Speaker(); 

		void play(const std::string key);

		void add_sound(const std::string key); 
	private:

		class Sound
		{
		public: 
			sf::SoundBuffer& buffer;
			sf::Sound& sound;



			Sound(sf::SoundBuffer& buffer, sf::Sound& sound) : buffer(buffer), sound(sound)
			{


				this->sound.setBuffer(buffer);

			}

			void play()
			{
				this->sound.play();
			}

			/// <summary>
			/// Set the pitch of the sound playing, also has the effect of changing the speed of the sound played 
			/// see SFML SoundSource.setPitch(); 
			/// </summary>
			/// <param name="pitch"></param>
			void setPitch(float pitch)
			{
				this->sound.setPitch(pitch);
			}



		};

		std::map<std::string, Sound*> sounds; 
		sf::Sound& sound; 
		sf::SoundBuffer& buffer;
		float speed; 
		Sound* previous_sound;         
	
	};
};
#endif 
//MusicPlayer_h 

