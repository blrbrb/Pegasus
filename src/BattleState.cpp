//
//  BattleState.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 4/11/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#
#include "include/BattleState.hpp"


BattleState::BattleState(StateData* state_data, GameStateData* gamestatedata, Player* player, class PlayerGUI* Player_GUI, Enemy* enemy) : State(state_data), Gamestatedata(gamestatedata), player(player), Player_GUI(Player_GUI), enemy(enemy), eventtimeMax(15.f)
{

    try
    {
        this->initVariables();
        this->initrender();
        this->initview();
        this->initpausemenu();
        this->initplayerGUI();
        this->initbackground(); 
        this->initdialouge(); 
    }
    
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl; 
       
    }
    
    //Player always takes first turn
    this->PlayerTurn = true;
    
    
}

BattleState::~BattleState()
{
    
    delete this->battleGUI;
    delete this->pMenu;
   
  

}


void BattleState::initVariables()
{
    this->eventtime = 0.f;
    this->enemy->setPosition(GUI::pixelpercentX(50, this->state_data->gfxsettings->resolution), GUI::pixelpercentY(66, this->state_data->gfxsettings->resolution));
}


void BattleState::initrender()
{
    

        if(!this->rendertexture.create(this->state_data->gfxsettings->resolution.width,this->state_data->gfxsettings->resolution.height))
        {
            throw std::runtime_error("unable to create rendertextrue");
        }

        this->rendersprite.setTexture(this->rendertexture.getTexture());
       
        this->rendersprite.setTextureRect(
            sf::IntRect(
                0,
                0,
                        this->state_data->gfxsettings->resolution.width,
                        this->state_data->gfxsettings->resolution.height
            )
      
                                                                            );
        
}

void BattleState::initbackground()
{ 
    this->bg_texture.loadFromFile("Resources/Assets/image.png"); 
    this->bg_texture.setRepeated(true); 


    this->background.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width), static_cast<float>(this->state_data->gfxsettings->resolution.height)));
    this->background.setTexture(&this->bg_texture);
    this->background.setPosition(0.f, 0.f);
}

void BattleState::initdialouge()
{ 
    this->dialougecomponent = new DialougeSystem("Resources/Assets/Fonts/PressStart2P.ttf", this->state_data->gfxsettings->resolution);
    this->dialougecomponent->addTextbox(1, "fuck my ass fuck my ass fuck my fucking ass bro"); 
}



void BattleState::initview()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.F, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));

    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.f,        static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));
}

void BattleState::initpausemenu()
{
    
    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
       
    this->pMenu = new PauseMenu(this->state_data->gfxsettings->resolution, this->font);
       
    this->pMenu->addbutton("Pause_Quit_Button",GUI::calcCharSize(vm),"Quit",GUI::pixelpercentX(13.f, vm), GUI::pixelpercentY(6.f, vm), 200.f);
    
}


void BattleState::updateBattleGUI(const float &dt)
{
    this->battleGUI->update(dt); 
    this->dialougecomponent->update(dt);
}

void BattleState::updatePauseMenu()
{
        if(this->pMenu->isButtonPressed("Pause_Quit_Button"))
        {
            this->endstate();
        }
}

void BattleState::updateInput(const float& dt)
{
    
    this->updateButtons(dt);

    
    
    
}
void BattleState::updateevents(sf::Event* event)
{




}

void BattleState::updateButtons(const float& dt)
{
    this->battleGUI->updatebuttons(this->MousePosScreen);
    

    if(this->battleGUI->isButtonPressed("MAGIC") && this->getEventtime())
    {
        
        this->PlayerAttack(); 
        this->dialougecomponent->advance(); 
        std::stringstream ss; 
        ss << this->player->attributes->Magic; 
        this->dialougecomponent->addTextbox(1, "You used ... on .... \n and did" + ss.str() + "damage!");
        this->enemy->animationcomponet->play("ATTACKED", dt);
      
        if (this->PlayerTurn) {
            this->PlayerTurn = false;
            this->dialougecomponent->advance();
        }
            else
                this->PlayerTurn = true;
        
    }
    
    
    

}



void BattleState::PlayerAttack()
{
    
    this->enemy->loseHP(this->player->attributes->strength * this->player->attributes->attributepts);
    
}

void BattleState::updateevents()
{ 



}



void BattleState::updateEnemies(const float& dt)
{
    this->enemy->update(dt, this->MousePosView);
    this->enemy->sprite.setScale(10, 10);
    
    if(this->PlayerTurn == false)
    {
        
        this->player->getStatusComponet()->loseHP(this->enemy->attributes->strength);
        
        if(!this->PlayerTurn)
            this->PlayerTurn = true;
        else
            this->PlayerTurn = false;
    }
    
    if(this->enemy->isDead())
    {
        this->player->attributes->gainEXP(this->enemy->getGainExp());
        
        this->states->pop();
    }
   
}

void BattleState::updatePlayerGUI(const float& dt)
{
    this->Player_GUI->update(dt);
}






void BattleState::updateeventtime(const float& dt)
{
    if (this->eventtime < this->eventtimeMax)
    {
        this->eventtime += 10.f * dt;
    }
}



void BattleState::update(const float &dt)
{
    
    this->updateeventtime(dt);
    this->updateMousePosition();
    this->updatePlayerGUI(dt);
  

    
    
    if(!this->paused) //Update while unpaused
      {
          if(this->PlayerTurn) //Update while it's the player's turn
          {
            this->updateBattleGUI(dt);
            this->updateInput(dt);
              
          }
    
          this->updateEnemies(dt);
        
      }
    
     else // Update while Paused
      {
          this->pMenu->update(this->MousePosWindow);
      }
    

}



void BattleState::renderBattleGUI(sf::RenderTarget& target)
{
    target.draw(this->background);
    this->battleGUI->render(target); 
    this->dialougecomponent->render(target); 
    
}


void BattleState::render(sf::RenderTarget *target)
{

    if (!target)
        target = this->window;
    
    this->rendertexture.clear();
    this->renderBattleGUI(this->rendertexture);
    this->Player_GUI->render(this->rendertexture);
    
    if(!this->enemy->isDead())
    {
        this->enemy->render(this->rendertexture);
    }
   
    
    if(this->paused)
    {
        this->rendertexture.setView(this->rendertexture.getDefaultView());
        this->pMenu->render(this->rendertexture);
    }
  
    //this->window->clear(); 
    this->rendertexture.display();
    

    target->draw(this->rendersprite);
    
}



void BattleState::initkeybinds()
{
    
    
}

void BattleState::GiveEnemyDamage(const float& dt)
{
    
    this->enemy->animationcomponet->play("ATTACKED", dt);
    this->enemy->loseHP(this->player->attributes->damageMin);
    
}


void BattleState::initplayerGUI()
{
    sf::VideoMode &vm = this->state_data->gfxsettings->resolution;
    
    this->battleGUI = new BattleGUI(this->player, this->enemy, vm);
}



const bool BattleState::getEventtime()
{
    if (this->eventtime >= this->eventtimeMax)
        {
            this->eventtime = 0.f;
            return true;
        }

        return false;
    
}
