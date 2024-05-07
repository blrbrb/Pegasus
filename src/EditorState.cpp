

#include "include/EditorState.hpp"
#include "include/loading_icon.h"
#include "include/imgui.h"
#include "include/imgui-SFML.h"

EditorState::EditorState(StateData* state_data): State(state_data), cameraSpeed(120.f), pMenu(nullptr), Tilemap(nullptr),
                                                 levels(nullptr), str_size(0), animations(nullptr)
{
    this->initVariables();
    this->initShader();
    this->initEditorStateData();
    this->initView();
    this->initFonts();
    this->initPauseMenu();
    this->initButtons();
    this->initTileMap();
    this->initLevels();
    this->initbg();
    this->initRenderSprite();
    this->initGUI();
    this->initModes();
    this->activeMode = EDITOR_MODES::DEFAULT_MODE;
   
 
    
     

}

EditorState::~EditorState() {
    

     auto it = buttons.begin();
     for (it = buttons.begin(); it != this->buttons.end(); ++it)
    
     {
         delete it->second;
      }
    delete this->pMenu;
     
    delete this->Tilemap;
    
  
    
    for (size_t i = 0; i > this->modes.size(); i++)
    {
        delete this->modes[i];
    }
    
    
}



//initialization functions
void EditorState::initVariables()
{
    this->cameraSpeed = 200.f;
    
}


//initalizer functions
void EditorState::initButtons()
{

}

void EditorState::initTileMap()
{
    this->Tilemap = new TileMap(this->gridSize, 100, 100, "Resources/Assets/Tiles/sheet.png");
    //this->Tilemap->addGenerationTexture("Resources/Assets/Tiles/sheet.png");
}

void EditorState::initView()
{
    this->mainView.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.f, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f ));
    
    
    this->mainView.setCenter(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 2.f,
                             static_cast<float>(this->state_data->gfxsettings->resolution.height) / 2.f);
    sf::Vector2f Screen_Left(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.f, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f);
    sf::Vector2f Screen_Right(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 2.f,
        static_cast<float>(this->state_data->gfxsettings->resolution.height) / 2.f);

    this->view_default_reset = sf::FloatRect(Screen_Left.x, Screen_Left.y, Screen_Right.x, Screen_Right.y);
      
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
    
    //Quit: Back to Main
    if(this->pMenu->isButtonPressed("Editor_Pause_Quit_Button"))
    {
        this->endState();
    }

    
    //Save the TileMap
    if(this->pMenu->isButtonPressed("Editor_Pause_Save_Button"))
    {
        //handle TileMap saving errors
        try
        {

            this->Tilemap->saveToFile("Data/TileMap/test.dat");
        }
        
        catch (std::runtime_error& e)
        {
            
            std::cout << e.what();
        }

    }
    
    //Load the TileMap
    if(this->pMenu->isButtonPressed("Editor_Pause_Load_Button"))
    {
        try
        {
            this->Tilemap->loadFromFile("Data/TileMap/test.dat");
        }
        
        catch (std::runtime_error& e)
        {
            std::cout << e.what();
        }

    }
        
}






void EditorState::initkeybinds()
{
  
    std::ifstream ifs("Init/EditorState_Keys.ini", std::fstream::in);

         if (ifs.is_open())
         {
             std::string key;
             std::string key2;
             //std::cout << "editorstate keyBinds exist" << std::endl;
             while (ifs >> key >> key2)
             {
                 this->keyBinds[key] = this->supportedKeys->at(key2);
                // std::cout << key << key2 << std::endl; 
                
 
             }


         }

   
    
    if (!ifs.is_open()) 
    {
        //LOG(WARNING) << "Editor State Keybinds Do Not Exist";
    }
    ifs.close();
}

void EditorState::initModes()
{
    //INIT LEVELS MUST ALWAYS, ALWAYS BE CALLED FIRST FOR THIS FUNCTION TO WORK!!!!!!!!!!!
    this->modes.push_back(new DefaultMode(this->state_data, this->levels->getCurrent(), &this->editorStateData, this->levels));
    this->modes.push_back(new EnemyEditorMode(this->state_data, this->Tilemap, &this->editorStateData, this->levels));
    this->modes.push_back(new EnviornmentalMode(this->state_data, this->Tilemap, &this->editorStateData, this->levels));
    //this->modes.push_back(new LevelManagerMode(this->state_data, this->Tilemap, &this->editorStateData, this->levels));
    this->modes.push_back(new ShaderEditorMode(this->state_data, this->levels->getCurrent(), &this->editorStateData, this->levels));
    
    this->activeMode = EDITOR_MODES::DEFAULT_MODE;
}

void EditorState::initLevels()
{
    this->levels = new Levels(*this->state_data->gridSize);
    this->levels->add_level("Map"); 
    this->curr_level = "Map";
    this->levels->set_current_level(this->curr_level); 

}

void EditorState::handleFonts()
{

    //LOG(INFO) << "attempting to handle exception";
    std::string custom_font_path;

    for (auto& p : std::filesystem::recursive_directory_iterator("Resources/Assets/Fonts"))
    {
        if (p.path().extension() == ".ttf") {
           
            custom_font_path = p.path().string();
            break;
        }
    }
    std::cout << custom_font_path << std::endl;
    this->font.loadFromFile(custom_font_path);
    std::cout << "Successfully loaded fonts";

}

void EditorState::initSidebar()
{
    //config the sidebar
    
  
}

void EditorState::initGUI()
{
    sf::Image image;
    //this->loading_texture.loadFromImage(header_to_image("loading"));
    image.create(LOADING_ICON.width, LOADING_ICON.height, LOADING_ICON.data);
    this->loading_texture.loadFromImage(image);
    this->loading_sprite.setTexture(this->loading_texture); 
    this->loading_sprite.setScale(sf::Vector2f(10.f, 10.f));
    this->buffering = false;
}

void EditorState::initbg()
{
   
    
    sf::FloatRect screen = sf::FloatRect(0, 0, this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height); 
    this->bg.setSize(sf::Vector2f(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height));   
      //this->bg.setSize(sf::Vector2f(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height));   
    this->bg_interior.setSize(this->levels->getCurrent()->getMaxSize());
    this->bg_interior.setPosition(sf::Vector2f(0.f, 0.f)); 
    this->bg_interior.setFillColor(sf::Color::Black); 
    this->bg.setFillColor(sf::Color(250.f, 0.f, 0.f, 90.f)); 
     

}


/* Initalizer Functions */



bool EditorState::initShader()
{
  //  sf::VideoMode& vm = sf::VideoMode::get
    if (!this->core_shader.loadFromFile("Data/Shader/vertex_shader.vert", "Data/Shader/fragment_shader.frag"))
        return false;
    return true;
    sf::Vector2f resolution = sf::Vector2f(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height);
    this->core_shader.setUniform("resolution", resolution);
    
   /// this->core_shader.setUniform("LightPos",this->editorStateData.mousePosView);
}

void EditorState::initRenderSprite()
{
    if (!this->renderTexture.create(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height))
    {
       // LOG(FATAL) << "failed to create renderTexture at " << this->state_data->gfxsettings->resolution.width << "x" << this->state_data->gfxsettings->resolution.height;
        throw std::runtime_error("unable to create rendertextrue GameState Line 78");

    }

    this->renderSprite.setTexture(this->renderTexture.getTexture());

    this->renderSprite.setTextureRect(
        sf::IntRect(
            0,
            0,
            this->state_data->gfxsettings->resolution.width,
            this->state_data->gfxsettings->resolution.height
        ));



}

void EditorState::initFonts() {
    
    if (!this->font.loadFromFile("Resources/Assets/Fonts/OpenSans-Variable.ttf"))
    {
        
        throw std::runtime_error("ERROR unable to load default font file EditorState lin 233"); 
        
    }
    
}


void EditorState::initbackground()
{

    
    
    
}


void EditorState::initEditorStateData()
{
    //this->editorStateData.view = &this->view;
    this->editorStateData.keybinds = &this->keyBinds;
    this->editorStateData.keytime = &this->keyTime;
    this->editorStateData.ketyimeMax = &this->keyTimeMax;

    this->editorStateData.mouseposGridI = &this->MousePosGridI;
    this->editorStateData.mousePosView = &this->MousePosView;
    this->editorStateData.mousePosWindow = &this->MousePosWindow;
    this->editorStateData.mousePosScreen= &this->MousePosScreen;
    this->editorStateData.mouseposGridF = &this->MousePosGridF;
    this->editorStateData.view = &this->mainView;
    this->editorStateData.font = &this->font;
    this->editorStateData.selection_color = ImVec4(sf::Color::Transparent);
    this->editorStateData.shader = &this->core_shader;
    
    
}

/*Update Functions*/

void EditorState::update(const float& dt) {
    
   
   
    this->updateMousePosition(&this->mainView);

    this->updateKeyTime(dt);
    this->updateEditorInput(dt);
    
   
   
   
    if (!this->paused) //Unpaused
    {
        this->updateButtons();
            this->updateGUI(dt);
        
        this->updateInput(dt);
        this->updateModes(dt);
    }
    else //Paused
    {
        this->pMenu->update(this->MousePosScreen);
        this->updatePauseMenuButtons();
    }
    
}


void EditorState::updateInput(const float& dt) {
    
    if (ImGui::GetIO().WantCaptureMouse)
        return;
    else



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_RIGHT"))))
    {
        this->mainView.move(this->cameraSpeed * dt, 0.f);
       // this->Tilemap->saveToFile("text.slmp");
        //std::cout << "camera right" << std::endl;
      //  std::cout << "Map Saved" << std::endl;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_LEFT"))))
    {
        this->mainView.move(-this->cameraSpeed * dt, 0.f);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_UP"))))
    {
        this->mainView.move(0.f, -this->cameraSpeed * dt);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_DOWN"))))
    {
        this->mainView.move(0.f, this->cameraSpeed * dt);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && this->getKeyTime())
    {
        if(this->levels->getCurrent()->lock_layer)
       this->Tilemap->lock_layer = false;
        
      else
          this->levels->getCurrent()->lock_layer = true;
    }
    
    
    /**std::cout << sf::Keyboard::L << std::endl;
    std::cout << "A = "<< " "<< sf::Keyboard::A << std::endl;
    std::cout << "B = "<< " "<< sf::Keyboard::B << std::endl;
    std::cout << "C = "<< " "<< sf::Keyboard::C << std::endl;
    std::cout << "D = "<< " "<< sf::Keyboard::D << std::endl;
    std::cout << "E = "<< " "<< sf::Keyboard::E << std::endl;
    std::cout << "F = "<< " "<< sf::Keyboard::F << std::endl;
    std::cout << "G = "<< " "<< sf::Keyboard::G << std::endl;
    std::cout << "H = "<< " "<< sf::Keyboard::H << std::endl;
    std::cout << "I = "<< " "<< sf::Keyboard::I << std::endl;
    std::cout << "G = "<< " "<< sf::Keyboard::J << std::endl;
    std::cout << "K = "<< " "<< sf::Keyboard::K << std::endl;
    std::cout << "L = "<< " "<< sf::Keyboard::L << std::endl;
    std::cout << "M = "<< " "<< sf::Keyboard::M << std::endl;
    std::cout << "N = "<< " "<< sf::Keyboard::N << std::endl;
    std::cout << "O = "<< " "<< sf::Keyboard::O << std::endl;
    std::cout << "P = "<< " "<< sf::Keyboard::P << std::endl;
    std::cout << "Q = "<< " "<< sf::Keyboard::Q << std::endl;
    std::cout << "R = "<< " "<< sf::Keyboard::R << std::endl;
    std::cout << "S = "<< " "<< sf::Keyboard::S << std::endl;
    std::cout << "T = "<< " "<< sf::Keyboard::T << std::endl;
    std::cout << "U = "<< " "<< sf::Keyboard::U << std::endl;
    std::cout << "V = "<< " "<< sf::Keyboard::V << std::endl;
    std::cout << "W = "<< " "<< sf::Keyboard::W << std::endl;
    std::cout << "X = "<< " "<< sf::Keyboard::X << std::endl;
    std::cout << "Y = "<< " "<< sf::Keyboard::Y << std::endl;
    std::cout << "Z = "<< " "<< sf::Keyboard::Z << std::endl; */
    
    //Zoom the World Builder View in or out
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
    {
        this->mainView.zoom(1.01);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && this->getKeyTime())
    {
        this->mainView.zoom(0.5);
    }
   
    
    //inc the current editor mode
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
    {
        
        if (this->activeMode > 0)
        {
            this->activeMode--;
        }
        else
        {
            std::cout << "ERROR CODE EditorState:2 || updateinput || CHANGE MODE DOWN!" << "\n";
        }
    }
      
    //dec the current editor mode
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && this->getKeyTime())
       {
           if (this->activeMode < this->modes.size() - 1)
           {
               this->activeMode++;
           }
           else
           {
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
    
    for (auto &it : this-> buttons)
    {
        it.second->update(this->MousePosWindow);
    }
    
}







void EditorState::updateEditorInput(const float& dt)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime())
    {
        if (!this->paused)
            this->pause();

        else
            this->unpause();
    }
    
    
    
}


void EditorState::updateGUI(const float& dt)
{
    static char str0[128] = "New_Map.cfg";
    static char str1[128] = "New Area";
    static int switchTabs;
    static bool p_open = NULL;
    static bool save; 
    static bool save_as; 
    static bool view; 
    static bool file; 
    static bool edit; 
    static bool load; 
    //ImGui::ShowDemoWindow();

   
    ImGui::Begin("Map Editor", &p_open, ImGuiWindowFlags_MenuBar);
    //is there any way to set the window flags from within this loop? 
   //that would be pretty poggers, I think


  // if (ImGui::Button(view_is_local ? "Local###ViewMode" : "Global###ViewMode"))
    if (ImGui::BeginMenuBar()) {

        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Save", NULL, &save);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Save the current map");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            ImGui::MenuItem("Save As", NULL, &save_as);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Save the current map to a new file");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            ImGui::MenuItem("Open", NULL, &load);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Open a recently saved map file");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
             ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();

        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Zoom In") && this->getKeyTime())
            {
                this->mainView.zoom(0.5);
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Zoom In");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            if (ImGui::MenuItem("Reset View") && this->getKeyTime())
            {
               
                this->mainView.reset(this->view_default_reset);
                

            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Set the view back to it's default position");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }

            if (ImGui::MenuItem("Zoom In") && this->getKeyTime())
            {
                this->mainView.zoom(0.5);
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Zoom In");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
           
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
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
        if (ImGui::Button("Load Saved Map", sf::Vector2f(125.f, 25.f)))
        {
           // LOG(INFO) << "attempting to load tilemap data from " << "Data/TileMap/" + GUI::convertToString(str0, this->str_size);
            this->levels->loadLevel(this->curr_level, "Data/TileMap/" + GUI::convertToString(str0, this->str_size));

        }
        ImGui::SameLine(0.0, 8.f);
        ImGui::InputText("New File", str0, IM_ARRAYSIZE(str0));
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted("Leave default text to save to an existing file, or save to a new file");
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
        ImGui::SameLine();

        ImGui::Separator();

        // ImGui::ShowDemoWindow(); 
        // 
         //ImGui::SameLine(0.0, 2.0f);

 
        if (save) {
                
            if (this->levels->saveLevel(this->curr_level, GUI::convertToString(str0, this->str_size)))
            {

                      

            }
                
            
            
        } 

        if (save_as) 
        {
            if(ImGui::BeginChild("Save As", sf::Vector2f(this->state_data->gfxsettings->resolution.width / 4, this->state_data->gfxsettings->resolution.height / 4)))
            {
                ImGui::InputText("New File", str0, IM_ARRAYSIZE(str0));
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
                {
                    ImGui::BeginTooltip();
                    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                    ImGui::TextUnformatted("Leave default text to save to New_Map.cfg, or save to a new file");
                    ImGui::PopTextWrapPos();
                    ImGui::EndTooltip();
                } 
                
                ImGui::Text("Maps can be saved in one of two formats, json like objects, or raw data");
                if (ImGui::Button("Save", sf::Vector2f(125.f, 25.f))) 
                {
                
                    this->levels->saveLevel(this->curr_level, GUI::convertToString(str0, this->str_size));
                    save_as = false; 
                
                }
              

                ImGui::EndChild();

            }
        
        
        } 

        if (load) 
        {
            this->Tilemap->loadFromFile("Data/TileMap/test.dat", false);
            load = false;
        }
            if (ImGui::Button("Tiles", sf::Vector2f(50.f, 0.f))) {
                switchTabs = 0;

            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Enter the Default TileMap Editor");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            ImGui::SameLine(0.0, 2.0f);
            if (ImGui::Button("Enemies", sf::Vector2f(100.0f, 0.0f))) {
                switchTabs = 1;
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Place Enemy Spawner Tiles");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            ImGui::SameLine(0.0, 2.0f);
            if (ImGui::Button("Enviornmental Tiles", sf::Vector2f(150.0f, 0.0f))) {
                switchTabs = 2;
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Place objects / enviornment tiles");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            ImGui::SameLine(0.0, 2.0f);
            if (ImGui::Button("Level Manager", sf::Vector2f(150.0f, 0.0f))) {
                switchTabs = 3;
            }
            ImGui::SameLine(0.0, 2.0f);
            if (ImGui::Button("Shader Editor", sf::Vector2f(100.f, 0.0f)))
            {
                switchTabs = 4;
                std::cout << "switching to shader editor mode" << std::endl;
            }


        
           
          
       
        switch (switchTabs) {
        case 0:

            this->activeMode = 0;


            break;
        case 1:

            this->activeMode = 1;

            break;
        case 2:

            this->activeMode = 2;

            break;

        case 3:
            this->activeMode = 3;

            break;

        case 4:
            this->activeMode = 4;
            break;

        default:
            break;
        }

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
    target->draw(this->bg);     

    this->renderTexture.clear();

    this->renderTexture.setView(this->mainView);
    
    //Tilemap Camera (same as game camera)
    this->window->setView(this->mainView);
    target->draw(this->bg_interior);
    this->levels->render(this->renderTexture, this->mainView, this->MousePosGridI, &this->core_shader);
   // this->Tilemap->render(*target, this->mainView, this->MousePosGridI);

    this->renderTexture.setView(this->renderTexture.getDefaultView());
    //Buttons Camera
    this->window->setView(this->window->getDefaultView());
    this->renderTexture.display();
    target->draw(this->renderSprite);
    this->renderModes(*target);
    this->renderButtons(*target);
    
  
   

    if(this->paused)
       {
           this->window->setView(this->window->getDefaultView());
           this->pMenu->render(*target);
       }   

    if (this->buffering) 
    {
        this->window->setView(this->window->getDefaultView());
        target->draw(this->loading_sprite); 
    }
    
   
    
}



void EditorState::renderGUI(sf::RenderTarget &target)
{
    
   
   
}


void EditorState::renderButtons(sf::RenderTarget& target)
{
    for (auto &it : this->buttons)
       {
           it.second->render(target);
    
       }
}

void EditorState::updateModes(const float &dt)
{
    this->modes[this->activeMode]->update(dt);
    
}

void EditorState::renderModes(sf::RenderTarget &target)
{
     this->modes[this->activeMode]->render(target);
}



