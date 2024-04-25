
#include "include/CharacterTab.hpp"

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player) :Tab(vm, font, player, false)
{

 
    //Background 
    this->characterTabBack.setFillColor(sf::Color(50, 50, 50, 180));
    this->characterTabBack.setSize(sf::Vector2f(GUI::pixelpercentX(30.f, this->vm), static_cast<float>(this->vm.height)));
    //Text  
    this->CharacterInfo.setString("FUCK FUCK FUCK FUCK FUCK FUCK FUCK FUCK FUCK FUCK FUCK"); 
    this->CharacterInfo.setFont(this->font);
    this->CharacterInfo.setCharacterSize(GUI::calcCharSize(this->vm, 200.f));
    this->CharacterInfo.setFillColor(sf::Color::White);
    this->CharacterInfo.setPosition(this->characterTabBack.getPosition().x + GUI::pixelpercentX(1, this->vm), this->characterTabBack.getPosition().y + 20.f);
    
   
}

CharacterTab::~CharacterTab()
{




}

void CharacterTab::update()
{
    if (!this->hidden)
    {

        this->CharacterInfo.setString(this->player.toString());
    
    }
}

void CharacterTab::render(sf::RenderTarget& target)
{ 
    if (!this->hidden)
    {
        target.draw(this->characterTabBack);
        target.draw(this->CharacterInfo);

    } 
    else 
    {
        return; 
    }
   
}
