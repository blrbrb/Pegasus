#include "stdafx.h"
#include "AudioComponent.h"

using namespace Sound;
MusicPlayer::MusicPlayer()
{
	this->initmusic();
	this->playtime_interval = 0.f;
	this->playtime_intervalMax = 10; 
	
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::add_music(std::string key, sf::SoundBuffer& buffer)
{


}

const bool& MusicPlayer::play(int key)
{

	std::cout << this->songs[key] << std::endl;
	this->music.openFromFile(this->songs[key]); 
	
	this->music.play();
	return false;
}

const bool& MusicPlayer::playing()
{
	return this->music.getStatus() == sf::SoundSource::Status::Playing; 
}

const bool& MusicPlayer::paused()
{
	return this->music.getStatus() == sf::SoundSource::Status::Paused;
}

const bool& MusicPlayer::stopped()
{
	return this->music.getStatus() == sf::SoundSource::Status::Stopped;
}

const bool MusicPlayer::getPlayInterval()
{
	if (this->playtime_interval >= this->playtime_intervalMax)
	{
		this->playtime = 0.f;
		return true;
	}

	return false;
}

void MusicPlayer::set_volume(float volume)
{
	this->music.setVolume(volume);
}

const std::string& MusicPlayer::current_track_title()
{
	return " "; 
}

const int MusicPlayer::current_track_no()
{
	return 0;
}

void MusicPlayer::skip()
{
}

void MusicPlayer::play_random()
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 11); // define the range

	
	if (this->music.getStatus() == sf::SoundSource::Playing) 
	{
		this->music.stop(); 
		LOG(INFO) << this->songs[distr(gen)];
		LOG(INFO) << distr(gen); 
		this->music.openFromFile(this->songs[distr(gen)]);
		this->music.play();
	}
	else
	{
		this->music.openFromFile(this->songs[distr(gen)]);
		this->music.play();
	}      




}

void MusicPlayer::pause()
{
}

void MusicPlayer::stop()
{ 
	
	if (this->music.getStatus() == sf::SoundSource::Status::Playing)
	{
		this->music.stop(); 
	}

}

void MusicPlayer::set_speed(float sp)
{


}

void MusicPlayer::update(const float& dt)
{

	this->update_interval(dt); 
	if (this->getPlayInterval()) {
		this->play_random();
	}

}

void MusicPlayer::update_interval(const float& dt)
{
	if (this->playtime_interval < this->playtime_intervalMax)
	{
		this->playtime_interval += 10.f * dt;
	}
}


bool MusicPlayer::initmusic()
{
	std::string path = "Resources/Sounds/music";
	//std::file p("Resources/Sounds/music");'
	int x = 0;
	
	for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{
		
		std::string item = ""; 
		//int items = std::distance(std::filesystem::directory_iterator(path), std::filesystem::directory_iterator{});
		LOG(INFO) << "Loading music " << entry.path().string(); 
	
		//LOG(INFO) << entry.path().extension();
		///this->music.at(entry.path().string()).loadFromFile(entry.path().string());
		
		this->songs[x] = entry.path().string();

		
		//this->music.at(entry.path().string())->loadFromFile(entry.path().string()); 
		//return true;

	}

	

	return false; 
}



Speaker::Speaker(sf::Sound& sound, sf::SoundBuffer& buffer) : sound(sound), buffer(buffer)
{


}

Speaker::~Speaker()
{
}

void Speaker::play(const std::string key)
{



}

void Speaker::add_sound(const std::string key)
{

	this->sounds[key] = new Sound(this->buffer, this->sound);


}
