
#
#include "EditorState.hpp"
#include "loading_icon.h"

EditorState::EditorState(StateData* state_data): State(state_data)
{
    this->initvariables();
    this->initshader(); 
    this->initeditorstatedata();
    this->initview();
    this->initFonts();
    this->initkeybinds();
    this->initpausemenu();
    this->initButtons();
    this->inittilemap();
    this->initlevels();
    this->initbg(); 
    this->initrendersprite();
    this->initGUI();
    this->initmodes();
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



//initalization functions
void EditorState::initvariables()
{
    this->cameraspeed = 200.f; 
    
}


//initalizer functions
void EditorState::initButtons()
{
    
}

void EditorState::inittilemap()
{
    this->Tilemap = new TileMap(this->gridsize, 100, 100, "Resources/Assets/Tiles/sheet.png");
    this->Tilemap->addGenerationTexture("Resources/Assets/Tiles/sheet.png"); 
}

void EditorState::initview()
{
    this->mainview.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.f, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f ));
    
    
    this->mainview.setCenter(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 2.f,
                             static_cast<float>(this->state_data->gfxsettings->resolution.height) / 2.f);
    sf::Vector2f Screen_Left(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.f, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f);
    sf::Vector2f Screen_Right(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 2.f,
        static_cast<float>(this->state_data->gfxsettings->resolution.height) / 2.f);

    this->view_default_reset = sf::FloatRect(Screen_Left.x, Screen_Left.y, Screen_Right.x, Screen_Right.y);
      
}


void EditorState::initpausemenu()
{
    
     const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    
    this->pMenu = new PauseMenu(this->state_data->gfxsettings->resolution, this->font);
    
    this->pMenu->addbutton("Editor_Pause_Quit_Button", GUI::calcCharSize(vm), "Quit", GUI::pixelpercentX(33.f, vm), GUI::pixelpercentY(15.f, vm), GUI::pixelpercentY(10.f, vm));
    this->pMenu->addbutton("Editor_Pause_Save_Button", GUI::calcCharSize(vm), "Save", GUI::pixelpercentX(33.f, vm), GUI::pixelpercentY(15.f, vm), GUI::pixelpercentY(38.2f, vm));
    this->pMenu->addbutton("Editor_Pause_Load_Button", GUI::calcCharSize(vm), "Load", GUI::pixelpercentX(33.f, vm), GUI::pixelpercentY(15.f, vm), GUI::pixelpercentY(61.8f, vm));
   
}

void EditorState::updatepausemenubuttons()
{
    
    //Quit: Back to Main
    if(this->pMenu->isButtonPressed("Editor_Pause_Quit_Button"))
    {
        this->endstate();
    }

    
    //Save the TileMap
    if(this->pMenu->isButtonPressed("Editor_Pause_Save_Button"))
    {
        //handle TileMap saving errors
        try
        {
           
            this->Tilemap->savetofile("Data/TileMap/text.dat");
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
            this->Tilemap->loadfromfile("Data/TileMap/text.dat");
        }
        
        catch (std::runtime_error& e)
        {
            std::cout << e.what();
        }

    }
        
}

void EditorState::updateshaders(const float& dt)
{
    this->core_shader.setUniform("lightPos", this->MousePosView);
}

void EditorState::updateImGui()
{ 
   

}



void EditorState::initkeybinds()
{
  
    std::ifstream ifs("Init/EditorState_Keys.ini", std::fstream::in);

         if (ifs.is_open())
         {
             std::string key = "";
             std::string key2 = "";
             //std::cout << "editorstate keybinds exist" << std::endl; 
             while (ifs >> key >> key2)
             {
                 this->keybinds[key] = this->supportedkeys->at(key2);
                // std::cout << key << key2 << std::endl; 
                
 
             }


         }

   
    
    if (!ifs.is_open()) 
    {
        //LOG(WARNING) << "Editor State Keybinds Do Not Exist";
    }
    ifs.close();
}

void EditorState::initmodes()
{
    //INIT LEVELS MUST ALWAYS, ALWAYS BE CALLED FIRST FOR THIS FUNCTION TO WORK!!!!!!!!!!!
    this->modes.push_back(new DefaultMode(this->state_data, this->levels->getCurrent(), &this->editorstatedata, this->levels));
    this->modes.push_back(new EnemyEditorMode(this->state_data, this->Tilemap, &this->editorstatedata, this->levels));
    this->modes.push_back(new EnviornmentalMode(this->state_data, this->Tilemap, &this->editorstatedata, this->levels));
    //this->modes.push_back(new LevelManagerMode(this->state_data, this->Tilemap, &this->editorstatedata, this->levels)); 
    this->modes.push_back(new ShaderEditorMode(this->state_data, this->levels->getCurrent(), &this->editorstatedata, this->levels));
    
    this->activeMode = EDITOR_MODES::DEFAULT_MODE;
}

void EditorState::initlevels()
{
    this->levels = new Levels(*this->state_data->gridsize); 
    this->levels->add_level("Map"); 
    this->curr_level = "Map";
    this->levels->set_current_level(this->curr_level); 

}

void EditorState::handlefonts()
{

    //LOG(INFO) << "attemping to handle exception";
    std::string custom_font_path = "";

    for (auto& p : std::filesystem::recursive_directory_iterator("Resources/Assets/Fonts"))
    {
        if (p.path().extension() == ".ttf") {
           
            custom_font_path = p.path().string();
            break;
        }
    }
    std::cout << custom_font_path << std::endl;
    this->font.loadFromFile(custom_font_path);
    std::cout << "Sucessfully loaded fonts";

}

void EditorState::initsidebar()
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



bool EditorState::initshader() 
{
  //  sf::VideoMode& vm = sf::VideoMode::get
    if (!this->core_shader.loadFromFile("Data/Shader/vertex_shader.vert", "Data/Shader/fragment_shader.frag"))
        return false;
    return true;
    sf::Vector2f resolution = sf::Vector2f(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height);
    this->core_shader.setUniform("resolution", resolution);
    
   /// this->core_shader.setUniform("LightPos",this->editorstatedata.mousePosView);
}

void EditorState::initrendersprite()
{
    if (!this->rendertexture.create(this->state_data->gfxsettings->resolution.width, this->state_data->gfxsettings->resolution.height))
    {
       // LOG(FATAL) << "failed to create rendertexture at " << this->state_data->gfxsettings->resolution.width << "x" << this->state_data->gfxsettings->resolution.height;
        throw std::runtime_error("unable to create rendertextrue GameState Line 78");

    }

    this->rendersprite.setTexture(this->rendertexture.getTexture());

    this->rendersprite.setTextureRect(
        sf::IntRect(
            0,
            0,
            this->state_data->gfxsettings->resolution.width,
            this->state_data->gfxsettings->resolution.height
        ));



}

void EditorState::initFonts() {
    
    if (!this->font.loadFromFile("Resources/Assets/Fonts/PressStart2P.ttf"))
    {
        
        throw std::runtime_error("ERROR unable to load default font file EditorState lin 233"); 
        
    }
    
}


void EditorState::initbackground()
{

    
    
    
}


void EditorState::initeditorstatedata()
{
    //this->editorstatedata.view = &this->view;
    this->editorstatedata.keybinds = &this->keybinds;
    this->editorstatedata.keytime = &this->keytime;
    this->editorstatedata.ketyimeMax = &this->keytime_MAX;

    this->editorstatedata.mouseposGridI = &this->MousePosGridI;
    this->editorstatedata.mousePosView = &this->MousePosView;
    this->editorstatedata.mousePosWindow = &this->MousePosWindow;
    this->editorstatedata.mousePosScreen= &this->MousePosScreen; 
    this->editorstatedata.mouseposGridF = &this->MousePosGridF; 
    this->editorstatedata.view = &this->mainview;
    this->editorstatedata.font = &this->font; 
    this->editorstatedata.selection_color = ImVec4(sf::Color::Transparent); 
    this->editorstatedata.shader = &this->core_shader; 
    
    
}

/*Update Functions*/

void EditorState::update(const float& dt) {
    
   
   
    this->updateMousePosition(&this->mainview);
    this->updateshaders(dt);
    this->updatekeytime(dt);
    this->updateEditorinput(dt);
    
   
   
   
    if (!this->paused) //Unpaused
    {
        this->updatebuttons();
            this->updateGUI(dt);
        
        this->updateInput(dt);
        this->updateModes(dt);
    }
    else //Paused
    {
        this->pMenu->update(this->MousePosScreen);
        this->updatepausemenubuttons();
    }
    
}


void EditorState::updateInput(const float& dt) {
    
    if (ImGui::GetIO().WantCaptureMouse)
        return;
    else



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
    {
        this->mainview.move(this->cameraspeed * dt, 0.f);
       // this->Tilemap->savetofile("text.slmp");
        //std::cout << "camera right" << std::endl;
      //  std::cout << "Map Saved" << std::endl;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
    {
        this->mainview.move(-this->cameraspeed * dt, 0.f);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
    {
        this->mainview.move(0.f, -this->cameraspeed * dt);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
    {
        this->mainview.move(0.f, this->cameraspeed * dt);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && this->getkeytime())
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
        this->mainview.zoom(1.01);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && this->getkeytime())
    {
        this->mainview.zoom(0.5);
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
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && this->getkeytime())
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



void EditorState::updatebuttons()
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

void EditorState::updateevents()
{







}





void EditorState::updateEditorinput(const float& dt)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getkeytime())
    {
        if (!this->paused)
            this->Pause_State();

        else
            this->Unpause_State();
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
    ImGui::ShowDemoWindow();

   
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
            if (ImGui::MenuItem("Zoom In") && this->getkeytime()) 
            {
                this->mainview.zoom(0.5);
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Zoom In");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            if (ImGui::MenuItem("Reset View") && this->getkeytime())
            {
               
                this->mainview.reset(this->view_default_reset);
                

            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted("Set the view back to it's default position");
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }

            if (ImGui::MenuItem("Zoom In") && this->getkeytime())
            {
                this->mainview.zoom(0.5);
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
            this->Tilemap->loadfromfile("Data/TileMap/New_Map.cfg", true);
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

    this->rendertexture.clear();

    this->rendertexture.setView(this->mainview);
    
    //Tilemap Camera (same as game camera)
    this->window->setView(this->mainview);
    target->draw(this->bg_interior); 
    this->levels->render(this->rendertexture, this->mainview, this->MousePosGridI, &this->core_shader); 
   // this->Tilemap->render(*target, this->mainview, this->MousePosGridI);

    this->rendertexture.setView(this->rendertexture.getDefaultView()); 
    //Buttons Camera
    this->window->setView(this->window->getDefaultView());
    this->rendertexture.display(); 
    target->draw(this->rendersprite);
    this->renderModes(*target);
    //this->renderbuttons(*target);
    
  
   

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


void EditorState::renderbuttons(sf::RenderTarget& target)
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


