

#include "include/EditorState.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <imgui-SFML.h>

EditorState::EditorState(StateData* state_data)
    : State(state_data)
    , cameraSpeed(120.f)
    , pMenu(nullptr)
    , Tilemap(nullptr)
    , str_size(0)

{


    this->initEditorStateData();
    this->initFonts();
    this->initTileMap();
    this->initVariables();

    // this->initEditorStateData();
    this->initModes();


    this->initView();

    this->initPauseMenu();
    this->initButtons();

    this->initRenderSprite();


    this->activeMode = EDITOR_MODES::DEFAULT_MODE;
}

EditorState::~EditorState()
{

    auto it = buttons.begin();
    for (it = buttons.begin(); it != this->buttons.end(); ++it)

    {
        delete it->second;
    }
    delete this->pMenu;

    delete this->Tilemap;

    for (size_t i = 0; i > this->modes.size(); i++) {
        delete this->modes[i];
    }
}

// initialization functions
void EditorState::initVariables()
{
    this->cameraSpeed = 200.f;
}

// initalizer functions
void EditorState::initButtons()
{
    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    this->buttons["Save"] = new GUI::Button(GUI::pixelpercentX(10.f,vm), GUI::pixelpercentY(10.f, vm), GUI::pixelpercentX(2.f,vm), GUI::pixelpercentY(2.f, vm), &this->font, "save", GUI::calcCharSize(vm));
}

void EditorState::initTileMap()
{
    this->Tilemap = new TileMap(this->gridSize, 100, 100, "Resources/Assets/Tiles/sheet.png");
    //this->Tilemap->importTMX();
}

void EditorState::initView()
{
    this->mainView.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.size.x) / 4.f, static_cast<float>(this->state_data->gfxsettings->resolution.size.y) / 4.f));

    this->mainView.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.size.x) / 2.f,
        static_cast<float>(this->state_data->gfxsettings->resolution.size.y) / 2.f));
    sf::Vector2f Screen_Left(static_cast<float>(this->state_data->gfxsettings->resolution.size.x) / 4.f, static_cast<float>(this->state_data->gfxsettings->resolution.size.y) / 4.f);
    sf::Vector2f Screen_Right(static_cast<float>(this->state_data->gfxsettings->resolution.size.x) / 2.f,
        static_cast<float>(this->state_data->gfxsettings->resolution.size.y) / 2.f);

    this->view_default_reset = sf::FloatRect(sf::Vector2f(Screen_Left.x, Screen_Left.y), sf::Vector2f(Screen_Right.x, Screen_Right.y));
}

void EditorState::initPauseMenu()
{

    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;

    this->pMenu = new PauseMenu(this->state_data->gfxsettings->resolution, this->font);

    this->pMenu->addbutton("Editor_Pause_Quit_Button", GUI::calcCharSize(vm), "Quit", GUI::pixelpercentX(33.f, vm), GUI::pixelpercentY(15.f, vm), GUI::pixelpercentY(10.f, vm));
    this->pMenu->addbutton("Editor_Pause_Save_Button", GUI::calcCharSize(vm), "Save", GUI::pixelpercentX(33.f, vm), GUI::pixelpercentY(15.f, vm), GUI::pixelpercentY(38.2f, vm));
    this->pMenu->addbutton("Editor_Pause_Load_Button", GUI::calcCharSize(vm), "Load", GUI::pixelpercentX(33.f, vm), GUI::pixelpercentY(15.f, vm), GUI::pixelpercentY(61.8f, vm));
}

void EditorState::updatePauseMenuButtons()
{

    // Quit: Back to Main
    if (this->pMenu->isButtonPressed("Editor_Pause_Quit_Button")) {
        this->endState();
    }

    // Save the TileMap
    if (this->pMenu->isButtonPressed("Editor_Pause_Save_Button")) {
        // handle TileMap saving errors
        try {

            //this->Tilemap->saveToFile("Data/TileMap/text.slmp");
            //this->Tilemap->exportTMX("Data/TileMap/test.")
        }

        catch (std::runtime_error& e) {

            std::cout << e.what();
        }
    }

    // Load the TileMap
    if (this->pMenu->isButtonPressed("Editor_Pause_Load_Button")) {
        try {
            this->Tilemap->importTMX("Data/TileMap/test.tmx");
            //this->Tilemap->loadFromFile("Data/TileMap/text.slmp");
        }

        catch (std::runtime_error& e) {
            std::cout << e.what();
        }
    }
}

void EditorState::initkeybinds()
{

    std::ifstream ifs("Init/EditorState_Keys.ini", std::fstream::in);

    if (ifs.is_open()) {
        std::string key;
        std::string key2;
        // std::cout << "editorstate keyBinds exist" << std::endl;
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
            // std::cout << key << key2 << std::endl;
        }
    }

    if (!ifs.is_open()) {
        // LOG(WARNING) << "Editor State Keybinds Do Not Exist";
    }
    ifs.close();
}

void EditorState::initModes()
{
    // INIT LEVELS MUST ALWAYS, ALWAYS BE CALLED FIRST FOR THIS FUNCTION TO WORK!!!!!!!!!!!
    this->modes.push_back(new DefaultMode(this->state_data, this->Tilemap, &this->editorStateData));


    this->activeMode = EDITOR_MODES::DEFAULT_MODE;
}


void EditorState::handleFonts()
{

    // LOG(INFO) << "attempting to handle exception";
    std::string custom_font_path;

    for (auto& p : std::filesystem::recursive_directory_iterator("Resources/Assets/Fonts")) {
        if (p.path().extension() == ".ttf") {

            custom_font_path = p.path().string();
            break;
        }
    }
    std::cout << custom_font_path << std::endl;

    if (!this->font.openFromFile(custom_font_path)) {
        std::cout << "retard" << std::endl;
    }

    std::cout << "Successfully loaded fonts";
}

void EditorState::initSidebar()
{
    // config the sidebar
}

void EditorState::initGUI()
{
}

/* Initalizer Functions */


void EditorState::initRenderSprite()
{
    this->renderTexture = new sf::RenderTexture({ this->state_data->gfxsettings->resolution.size.x, this->state_data->gfxsettings->resolution.size.y });

    if (!this->renderTexture) {
        // LOG(FATAL) << "failed to create renderTexture at " << this->state_data->gfxsettings->resolution.width << "x" << this->state_data->gfxsettings->resolution.height;
        throw std::runtime_error("unable to create rendertextrue GameState Line 78");
    }
    this->renderSprite = new sf::Sprite(this->renderTexture->getTexture());

    this->renderSprite->setTextureRect(
        sf::IntRect(sf::Vector2i(
                        0,
                        0),
            sf::Vector2i(
                this->state_data->gfxsettings->resolution.size.x,
                this->state_data->gfxsettings->resolution.size.y)));
}

void EditorState::initFonts()
{

    if (!this->font.openFromFile("Resources/Assets/Fonts/OpenSans-Variable.ttf")) {

        throw std::runtime_error("ERROR unable to load default font file EditorState lin 233");
    }
}


void EditorState::initEditorStateData()
{

    this->editorStateData.keybinds = &this->keyBinds;
    this->editorStateData.keytime = &this->keyTime;
    this->editorStateData.ketyimeMax = &this->keyTimeMax;

    this->editorStateData.mouseposGridI = &this->MousePosGridI;
    this->editorStateData.mousePosView = &this->MousePosView;
    this->editorStateData.mousePosWindow = &this->MousePosWindow;
    this->editorStateData.mousePosScreen = &this->MousePosScreen;
    this->editorStateData.mouseposGridF = &this->MousePosGridF;
    this->editorStateData.view = &this->mainView;
    this->editorStateData.font = &this->font;
    std::cout << "keytime max editor state data EditorState.cpp | 319" << this->editorStateData.ketyimeMax << std::endl;
    std::cout << "mousepos screen x editor state data EditorState.cpp | 319 | " << this->editorStateData.mousePosScreen->x << std::endl;
    std::cout << "keytime editor state data EditorState.cpp | 320 " << *this->editorStateData.keytime << std::endl;
}

/*Update Functions*/

void EditorState::update(const float& dt)
{

    this->updateMousePosition(&this->mainView);

    this->updateKeyTime(dt);
    this->updateEditorInput(dt);

    if (!this->paused) // Unpaused
    {
        this->updateButtons();
        this->updateGUI(dt);

        this->updateInput(dt);
        this->updateModes(dt);
    } else // Paused
    {
        this->pMenu->update(this->MousePosScreen);
        this->updatePauseMenuButtons();
    }
}

void EditorState::updateInput(const float& dt)
{

    if (ImGui::GetIO().WantCaptureMouse)
        return;
    else

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->mainView.move(sf::Vector2f(this->cameraSpeed * dt, 0.f));
       // this->Tilemap->exportTMX("Data/TileMap/test.tmx");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->mainView.move(sf::Vector2f(-this->cameraSpeed * dt, 0.f));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->mainView.move(sf::Vector2f(0.f, -this->cameraSpeed * dt));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this->mainView.move(sf::Vector2f(0.f, this->cameraSpeed * dt));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && this->getKeyTime()) {
        if (this->Tilemap->lock_layer)
            this->Tilemap->lock_layer = false;

        else
            this->Tilemap->lock_layer = true;
    }



    // Zoom the World Builder View in or out
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
        this->mainView.zoom(1.01);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && this->getKeyTime()) {
        this->mainView.zoom(0.5);
    }

    // inc the current editor mode
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {

        if (this->activeMode > 0) {
            this->activeMode--;
        } else {
            std::cout << "ERROR CODE EditorState:2 || updateinput || CHANGE MODE DOWN!" << "\n";
        }
    }

    // dec the current editor mode

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && this->getKeyTime()) {
        if (this->activeMode < this->modes.size() - 1) {
            this->activeMode++;
        } else {
            std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE UP!" << "\n";
        }
    }
}

void EditorState::updateButtons()
{
    /*!
    @class EditorState
    @brief Update the user's Input for buttons
    @param void
    @return void
    */

    for (auto& it : this->buttons) {
        it.second->update(this->MousePosWindow);
    }


}

void EditorState::updateEditorInput(const float& dt)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->getKeyTime()) {
        if (!this->paused)
            this->pause();

        else
            this->unpause();
    }
}

void EditorState::updateGUI(const float& dt)
{
    static char str0[128] = "My Island";
    static char str1[128] = "New Area";
    static int switchTabs;
    static bool p_open = NULL;
    static bool save;
    static bool save_as;
    static bool view;
    static bool file;
    static bool edit;
    static bool load;
    // ImGui::ShowDemoWindow();
    std::string ofilename(str0);
    std::replace(ofilename.begin(), ofilename.end(), ' ', '-');


    std::transform(ofilename.begin(), ofilename.end(), ofilename.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    ofilename += ".tmx";
    ImGui::Begin("Map Editor", &p_open, ImGuiWindowFlags_MenuBar);
    // is there any way to set the window flags from within this loop?
    // that would be pretty poggers, I think

    // if (ImGui::Button(view_is_local ? "Local###ViewMode" : "Global###ViewMode"))
    if (ImGui::BeginMenuBar()) {

        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Zoom In") && this->getKeyTime()) {
                this->mainView.zoom(0.5);
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Zoom In");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            if (ImGui::MenuItem("Reset View") && this->getKeyTime()) {

                this->mainView.setViewport(this->renderTexture->getDefaultView().getViewport());
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Set the view back to it's default position");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }

            if (ImGui::MenuItem("Zoom In") && this->getKeyTime()) {
                this->mainView.zoom(0.5);
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Zoom In");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }

            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Zoom Out");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            ImGui::EndMenu();
        }
    }
    ImGui::EndMenuBar();
    ImGui::SameLine(0.0, 8.0f);
    if (ImGui::Button("Load Island", sf::Vector2f(125.f, 25.f))) {
        this->Tilemap->importTMX(ofilename);
        // LOG(INFO) << "attempting to load tilemap data from " << "Data/TileMap/" + GUI::convertToString(str0, this->str_size);
        // this->Tilemap->loadFromFile("Data/TileMap/" + GUI::convertToString(str0, this->str_size), false);

    }
    ImGui::SameLine(0.0, 8.f);
    ImGui::InputText("New File", str0, IM_ARRAYSIZE(str0));
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("Load a previously saved island");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
    ImGui::SameLine();

    ImGui::Separator();

        if (ImGui::Button("Save", sf::Vector2f(150.f, 25.f))) {
            std::cout << "saving map.." << std::endl;
            this->Tilemap->exportTMX(ofilename);


        }

    ImGui::SameLine(0.0, 2.0f);

    std::stringstream cursor_text;
    cursor_text << "MouseX: " << this->MousePosView.x << "\n"
                << "MouseY:" << this->MousePosView.y;
    std::string text = cursor_text.str();

    ImGui::Separator();

    ImGui::Text(text.c_str());

    this->str_size = sizeof(str0) / sizeof(char);

    ImGui::End();
}

/*Render Functions*/

void EditorState::render(sf::RenderTarget* target)
{

    if (!target)
        target = this->window;

    target->setView(this->mainView);
    this->Tilemap->render(*target, this->mainView, this->MousePosGridI);
    this->Tilemap->DefferedRender(*target);

    this->window->setView(this->mainView);

    this->window->setView(this->window->getDefaultView());
    // this->renderTexture->display();
    // target->draw(*this->renderSprite);
    this->renderModes(*target);


    if (this->paused) {
        this->window->setView(this->window->getDefaultView());
        this->pMenu->render(*target);
    }

        this->window->setView(this->window->getDefaultView());
        this->renderButtons(*target);
}

void EditorState::renderGUI(sf::RenderTarget& target)
{
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

void EditorState::updateModes(const float& dt)
{
    this->modes[this->activeMode]->update(dt);
}

void EditorState::renderModes(sf::RenderTarget& target)
{
    this->modes[this->activeMode]->render(target);
}
