//
//  DefaultMode.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "include/DefaultMode.hpp"
#include "include/Tile.hpp"

DefaultMode::DefaultMode(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata)
    : EditorModes(statedata, tilemap, editorstatedata)

{

    this->initvariables();
    this->inittext();
    this->initgrid();
    this->initGUI();
    std::cout << this->tilemap->getMaxSize().x << " " << "sanity check max tilemap size X DefaultMode | 19" << std::endl;
}

DefaultMode::~DefaultMode()
{
}

void DefaultMode::updateInput(const float& dt)
{

   // this->TextureRect = this->texture_selector->getTextureRect();

    if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->getkeytime())) {

        // if the user's mouse is not on the sidebar
       // std::cout << this->texture_selector->getActive() << " texture selector state " << std::endl;
        // if the texure selector is not active
        if (!this->texture_selector->getActive()) {

                // if adding tiles is locked to one layer
                if (this->tilemap->lock_layer)
                {
                    if (this->tilemap->TileEmpty(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, 0))
                    {
                        this->tilemap->addTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, this->TextureRect, collision, this->type);
                        // this->tilemap->addTile(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y, this->layer, this->TextureRect, collision, this->type);
                       // std::cout << "LOCKED: Tile Added" << std::endl;
                    }


                }
                // else if the cursor is not within the texture selector
                else
                {
                    this->tilemap->addTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, this->TextureRect, collision, this->type);
                    //std::cout << "TILE ADDED " << std::endl;
                }
        }
        else
        {
            this->TextureRect = this->texture_selector->getTextureRect();

        }

    }


    // Remove a tile
    else if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete) && this->getkeytime())) {

        // if the user's mouse is not inside the texture selector
        if (!this->texture_selector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorstatedata->mousePosWindow))) {
            // if the cursor is over a valid tile, ok to place
            if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) != -1) {

                if (this->tilemap->lock_layer) {
                    if (!this->tilemap->TileEmpty(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer)) {
                        this->tilemap->removeTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, TileTypes::NORMAL);
                        //std::cout << "LOCKED: Tile Removed" << std::endl;
                    } else {
                        // LOG(INFO) << "editor tried to place more than one tile on a locked layer";
                    }

                }

                else {
                    this->TextureRect = this->texture_selector->getTextureRect();
                }
                // else if adding tiles is not locked to one layer
                if (!this->tilemap->lock_layer) {

                    this->tilemap->removeTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, TileTypes::NORMAL);

                    //std::cout << "Tile Removed" << std::endl;
                }

            }

            else if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) == -1) {
                std::cerr << "tried to place tile on invalid layer" << '\n';
            }
        }
    }

    // Toggle Collision on Tiles
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && this->getkeytime()) {
        if (this->collision)
            this->collision = false;
        else
            this->collision = true;

        std::cout << "Collision Tog" << std::endl;
    }

    // Toggle Type of Tile to increase or decrease
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->getkeytime()) {
        ++this->type;
        std::cout << "Type up" << std::endl;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && this->getkeytime()) {
        if (this->type > 0)
            --this->type;
        std::cout << "Type down" << std::endl;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && this->getkeytime()) {
        // this->select_Rect.rotate(90);

        // this Is how you rotate things to the left, dear god, thank christ
        this->TextureRect.size.x = -this->TextureRect.position.y * this->TextureRect.position.x;

        std::cout << this->select_Rect.getTextureRect().position.y << " After Transformation" << std::endl;

        // this->TextureRect.size.y = reverse.size.y;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && this->getkeytime()) {
        this->TextureRect.size.y = -this->TextureRect.size.y;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && this->getkeytime()) {
        std::cout << "object added" << std::endl;
        this->tilemap->addTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, ObjectTypes::LANTERN);
        // this->tilemap->addObject(this->editorStateData->mousePosWindow->x, this->editorStateData->mousePosWindow->y);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4) && this->getkeytime()) {
        if (this->TextureRect.position.x >= static_cast<int>(this->texture_selector->getMaxSize().x))
            return;
        else
            this->TextureRect.position.x += 32;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6) && this->getkeytime()) {
        if (this->TextureRect.position.x <= 0)
            return;
        else
            this->TextureRect.position.x -= 32;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8) && this->getkeytime()) {
        if (this->TextureRect.position.y >= static_cast<int>(this->texture_selector->getMaxSize().y))
            return;
        else
            this->TextureRect.position.y += 24;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2) && this->getkeytime()) {
        if (this->TextureRect.position.y <= 0)
            return;
        else
            this->TextureRect.position.y -= 24;
    }
}

void DefaultMode::update(const float& dt)
{
    // std::cout << "updating default editor state mode" << std::endl;
    this->updateGUI(dt);

    if (ImGui::GetIO().WantCaptureMouse == false) {
        this->updateInput(dt);
    }

    this->updateInput(dt);
}

void DefaultMode::updateGUI(const float& dt)
{
    // std::cout << "default mode updating the GUI" << std::endl;
    this->texture_selector->update(*this->editorstatedata->mousePosWindow, dt);
    //this->select_Rect.setTextureRect(this->texture_selector->getTextureRect());

    ImGui::Begin("Map Editor", NULL, ImGuiWindowFlags_NoMove);

    this->texturesample->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>(this->statedata->gridSize.x), static_cast<int>(this->statedata->gridSize.y)), sf::Vector2i(0, 0)));

    if (!this->texture_selector->getActive()) {

        this->select_Rect.setTextureRect(this->TextureRect);
        this->texturesample->setTextureRect(this->TextureRect);
        this->select_Rect.setPosition(sf::Vector2f(this->editorstatedata->mouseposGrid->x * this->statedata->gridSize.x, this->editorstatedata->mouseposGrid->y * this->statedata->gridSize.y));
    }
    this->texturesample->setTexture(*this->select_Rect.getTexture());

    this->select_Rect.setOrigin(sf::Vector2f(this->select_Rect.getLocalBounds().size.x, this->select_Rect.getLocalBounds().size.y) / 2.f);

    //this->select_Rect.setTextureRect(this->texture_selector->getTextureRect());
    this->texturesample->setTextureRect(this->TextureRect);
    // std::stringstream cursor_text;
    //  cursor_text << "MouseX: " << this->editorstatedata->mousePosView->x << "\n"
    //         << "MouseY:" << this->editorstatedata->mousePosView->y
    //            << "\n"
    //           << "GridX: " << this->editorstatedata->mouseposGrid->x
    //           << "\n"
    //            << "GridY: " << this->editorstatedata->mouseposGrid->y
    //            << "\n"
    //            << "TextureRectX: " << this->TextureRect.position.x
    //            << "\n"
    //            << "TextureRectY: " << this->TextureRect.position.y
    //            << "\n"
    //           << "Collision: " << this->collision
    //            << "\n"
    //            << "Type: " << EnumStrings[this->type]
    //            << "\n"
    //            << "Tiles:" << this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer);
    // this->statedata->gridSize.
    // std::string text = cursor_text.str();

    // ImGui::Text(text.c_str());
    ImGui::SameLine();

    ImGui::Image(*this->texturesample);

    ImGui::Separator();

    ImGui::Checkbox("Lock Tile Placement to this layer", &this->tilemap->lock_layer);
    ImGui::Checkbox("Hide Texture Selector", &this->texture_selector->hidden);
    ImGui::SameLine(0.f, 8.f);
    ImGui::Checkbox("Show Grid", &this->showgrid);
    // ImGui::LableText("Texture Rectangle Controls");

    if (ImGui::ArrowButton("##up", ImGuiDir_Up)) {
        this->TextureRect.position.y += 24;
    }
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {
        this->TextureRect.position.x += 32;
    };
    ImGui::SameLine(0.0f, 0.5f);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
        this->TextureRect.position.x -= 32;
    }
    if (ImGui::ArrowButton("##down", ImGuiDir_Down)) {
        this->TextureRect.position.y -= 24;
    }
    ImGui::SameLine();

    if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) < -1) {
        ImGui::TextColored(sf::Color::Red, "Invalid Tile Space");
    }


    ImGui::End();

    // this->tilemap->updateTiles(dt);
}

void DefaultMode::renderGUI(sf::RenderTarget& target)
{
    // std::cout << "rendering default mode gui DefaultMode.cpp | 374 " << std::endl;
    if (!this->texture_selector->getActive()) {
        target.setView(*this->editorstatedata->view);
        target.draw(this->select_Rect);
    }

    // std::cout << "rendering default mode gui DefaultMode.cpp | 385 " << std::endl;
    if (this->showgrid) {
        for (auto& it : this->grid) {
            target.draw(it);
        }
    }

    target.setView(this->statedata->window->getDefaultView());
    this->texture_selector->render(target);

    // std::cout << "rendering default mode gui DefaultMode.cpp | 405 " << std::endl;
    target.setView(*this->editorstatedata->view);
    // target.draw(*this->cursortext);
}

void DefaultMode::render(sf::RenderTarget& target)
{

    this->renderGUI(target);
}

void DefaultMode::initvariables()
{
    this->TextureRect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 24));
    this->collision = false;
    this->type = TileTypes::NORMAL;
    this->layer = 0;
}

void DefaultMode::inittext()
{
}

void DefaultMode::initGUI()
{
    sf::VideoMode vm = statedata->gfxsettings->resolution;

    // this->select_Rect.setOrigin(sf::Vector2f(this->select_Rect.getGlobalBounds().size.x / 2.f / this->statedata->gridSize - static_cast<float>(this->editorstatedata->mouseposGridF->x), this->select_Rect.getGlobalBounds().size.y / 2.f / this->statedata->gridSize - static_cast<float>(this->editorstatedata->mouseposGridF->y)));


    this->select_Rect.setSize(sf::Vector2f(statedata->gridSize.x, statedata->gridSize.y));
    this->select_Rect.setTexture(tilemap->getTileSheet());


    this->texturesample = std::make_shared<sf::Sprite>(*this->select_Rect.getTexture(), this->select_Rect.getTextureRect());
    this->texturesample->setScale(sf::Vector2f(3, 3));

    // this->texturesample.setPosition(GUI::pixelpercentX(100, vm), GUI::pixelpercentY(20, vm));


    this->texture_selector = new GUI::TextureSelector(100.f, 20.f, 798.f, 798.f, this->statedata->gridSize, this->tilemap->getTileSheet(), "X");
}

void DefaultMode::initgrid()
{
    this->grid.resize(100);

    this->showgrid = false;

    sf::VideoMode& vm = this->statedata->gfxsettings->resolution;

    float X = GUI::pixelpercentX(0, vm);
    float Y = GUI::pixelpercentY(0, vm);

    for (int x = 0; x <= 1000; x++) {
        X += GUI::pixelpercentX(3.2, vm);

        if (X >= GUI::pixelpercentX(100, vm) || Y >= GUI::pixelpercentY(1000, vm)) {
            Y += GUI::pixelpercentY(2.4, vm);
            X = GUI::pixelpercentX(0, vm);
        }

        this->grid.push_back(sf::RectangleShape());
        this->grid.at(x).setSize(sf::Vector2f(this->statedata->gridSize.x, this->statedata->gridSize.y));
        this->grid.at(x).setFillColor(sf::Color::Transparent);
        this->grid.at(x).setOutlineColor(sf::Color::White);
        this->grid.at(x).setOutlineThickness(0.1f);
        this->grid.at(x).setPosition(sf::Vector2f(X, Y));
    }
}
