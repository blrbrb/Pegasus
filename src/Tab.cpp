#
#include "include/Tab.hpp"

Tab::Tab(sf::VideoMode& vm, sf::Font& font, Player& player, bool hidden) : vm(vm), font(font), player(player), hidden(hidden)
{


}

Tab::~Tab() =default;

const bool& Tab::getHidden() const
{
	return this->hidden; 
}

const bool& Tab::getOpen() const
{
    //compiler will complain about a local temporary here, this is expected behaviour. MsClang and G++
    //have no way to determine what my intentions are, but reset assured. This is supposed to happen
	return !this->hidden;
}

void Tab::toggle()
{

	if (this->hidden)
		this->hidden = false;
	else
		this->hidden = true; 

}

void Tab::hide()
{
	this->hidden = true; 
}

void Tab::show()
{
	this->hidden = false;
}
