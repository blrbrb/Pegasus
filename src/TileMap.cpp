//
//  TileMap.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#

#include "include/TileMap.hpp"

class ValueGet {
public:
    int data;
    ValueGet()
    {
        data = 0;
    }
};

void TileMap::clear()
{
    // symmetry orgasim
    if (!this->Map.empty()) {
        // LOG(INFO) << "Destroying Map Data...";
        for (int x = 0; x < this->Map.size(); x++) {
            for (int y = 0; y < this->Map[x].size(); y++) {
                for (int z = 0; z < this->Map[x][y].size(); z++) {
                    for (size_t k = 0; k < this->Map[x][y][z].size(); k++) {
                        delete this->Map[x][y][z][k];
                        this->Map[x][y][z][k] = NULL;
                    }
                    this->Map[x][y][z].clear();
                }
                this->Map[x][y].clear();
            }
            this->Map[x].clear();
        }
        this->Map.clear();

        // LOG(INFO) << "Map object cleared, current memory size (bytes)" << " " << this->Map.size();
    }
}

void TileMap::initobjecthandler()
{
    // this->objecthandler = new ObjectHandler(this->Objects, this->textures);
}

void TileMap::initgeometry()
{
    // this needs to be moved to DefaultMode.cpp

    this->geometry["CORNER_TOP_LEFT"] = sf::Vector2i(0, 48);
    this->geometry["GRASS_BORDER_TOP"] = sf::Vector2i(32, 48);
    this->geometry["CORNER_TOP_LEFT"] = sf::Vector2i(0, 72);
    this->geometry["GRASS_BORDER_BOTTOM"] = sf::Vector2i(0, 168);
    this->geometry["CORNER_BOTTOM_RIGHT"] = sf::Vector2i(128, 144);
    this->geometry["GRASS_BORDER_TOP_RIGHT"] = sf::Vector2i(96, 72);
    this->geometry["GRASS"] = sf::Vector2i(0, 0);
    this->geometry["DIRT"] = sf::Vector2i(32, 0);
    this->geometry["GRASS_ISLAND"] = sf::Vector2i(64, 96);
}


void TileMap::initvariables()
{
    this->initgeometry();
}

void TileMap::initloggingthread()
{
    // el::Helpers::setThreadName("%TileMap");
}

TileMap::TileMap(sf::Vector2f gridsize, int width, int height, std::string texture_file)
{

    /*!
      @brief   Default Constructor. Initalizes the tileMap as a 4d Vector of Tiles

      @param   float   gridSize    The gridSize for the TileMap

      @param   int     width       The width of the TileMap vector

      @param   int     height      The height of the TileMap vector

      @param   std::string     texture_file        The texturefile to load Tiles From

             */
    this->initvariables();

    this->grid_sizeF = gridsize;
    this->grid_sizeU = static_cast<sf::Vector2u>(gridsize);
    this->gridsizeI = static_cast<sf::Vector2i>(gridsize);
    this->lock_layer = false;
    this->MaxSizeWorldGrid.x = width;
    this->MaxSizeWorldGrid.y = height;
    this->layers = 1;
    this->texture_file = texture_file;
    this->MaxSizeWorld_F.x = static_cast<float>(width) * gridsize.x;
    this->MaxSizeWorld_F.y = static_cast<float>(height) * gridsize.y;

    // Tile Culling Vars

    this->ToX = 0;
    this->FromX = 0;
    this->ToY = 0;
    this->FromY = 0;
    this->layer = 0;

    this->Map.resize(this->MaxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

    for (int x = 0; x < this->MaxSizeWorldGrid.x; x++) {

        for (int y = 0; y < this->MaxSizeWorldGrid.y; y++) {
            this->Map[x].resize(this->MaxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

            for (int z = 0; z < this->layers; z++) {

                this->Map[x][y].resize(this->layers, std::vector<Tile*>());
            }
        }
    }

    this->tileTextureSheet.loadFromFile(texture_file);

    this->physicsrect.setSize(sf::Vector2f(grid_sizeF.x, grid_sizeF.y));
    this->physicsrect.setFillColor(sf::Color::Transparent);
    this->physicsrect.setOutlineColor(sf::Color::Red);
    this->physicsrect.setOutlineThickness(1.f);
}



TileMap::TileMap(const std::string map_file)
{

    this->ToX = 0;
    this->FromX = 0;
    this->ToY = 0;
    this->FromY = 0;
    this->layer = 0;

    // this->init_object_textures();
    this->loadFromFile(map_file);
}

// Default Overload, if no other args are provided to the constructor use a randomly generated sequence of map tiles.
TileMap::TileMap()
{
}

TileMap::~TileMap()
{

    this->clear();
}

// Functions
void TileMap::render(sf::RenderTarget& target, const sf::View& view, const sf::Vector2i& gridposition, const bool render_collision, sf::Shader* shader, const sf::Vector2f PlayerPosition)
{

    /*!
         @brief   Default render

         @param   sf::RenderTarget&     target       The intended render target

         @param   const sf::Vector2i&     gridposition     The gridposition.

         @param   const bool     render_collision        The boolean value that determines wether or not to render tiles with their respective
                                                         collision boxes
         @param   sf::Shader*      shader      Optional shader to use in the render

         @param   const sf::Vector2f       PlayerPosition      Supply this value only if a shader is intended to be rendered onto the tileMap.

                 */

    this->layer = 0;

    this->FromX = gridposition.x - 10;

    if (this->FromX < 0)
        this->FromX = 0;
    else if (this->FromX > this->MaxSizeWorldGrid.x)
        this->FromX = this->MaxSizeWorldGrid.x;

    this->ToX = gridposition.x + 10;

    if (this->ToX < 0)
        this->ToX = 0;
    else if (this->ToX > this->MaxSizeWorldGrid.x)
        this->ToX = this->MaxSizeWorldGrid.x;

    this->FromY = gridposition.y - 10;

    if (this->FromY < 0)
        this->FromY = 0;
    else if (this->FromY > this->MaxSizeWorldGrid.x)
        this->FromY = this->MaxSizeWorldGrid.x;

    this->ToY = gridposition.y + 10;

    if (this->ToY < 0)
        this->ToY = 0;
    else if (this->ToY > this->MaxSizeWorldGrid.y)

        this->ToY = this->MaxSizeWorldGrid.y;

    for (int x = this->FromX; x < this->ToX; x++) {
        for (int y = this->FromY; y < this->ToY; y++) {
            for (size_t k = 0; k < this->Map[x][y][this->layer].size(); k++) {

                // render w/ shader applied

                if (this->Map[x][y][this->layer][k]->gettype() == TileTypes::OBJECT) {
                    this->renderdefered.push(this->Map[x][y][this->layer][k]);
                } else {
                    if (shader)
                        this->Map[x][y][this->layer][k]->render(target, shader, PlayerPosition);
                    else
                        this->Map[x][y][this->layer][k]->render(target);
                }

                // render the collision box
                if (render_collision) {
                    if (this->Map[x][y][this->layer][k]->getCollision()) {
                        this->physicsrect.setPosition(this->Map[x][y][this->layer][k]->getPosition());
                        target.draw(this->physicsrect);
                    }
                }

                if (this->Map[x][y][this->layer][k]->gettype() == TileTypes::SPAWNER) {
                    this->physicsrect.setPosition(this->Map[x][y][this->layer][k]->getPosition());
                    this->physicsrect.setFillColor(sf::Color(50, 20, 10, 100));
                    this->physicsrect.setFillColor(sf::Color::Red);
                    this->physicsrect.setOutlineThickness(1.f);
                    target.draw(this->physicsrect);
                }
            }
        }
    }
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool& collision, const short& type)
{
    std::cout << "regular function called" << std::endl;
    /*!
     @brief  Add a tile to the TileMap

     @param   const int   x   The X-value (relative to the Tilemap vector) to place a tile on. e.g. TileMap[x]

     @param   const int   y   The Y-value (relative to the Tilemap vector) to place a tile on. e.g. TileMap[x][y]

     @param   const int   z   The Z-value (relative to the Tilemap vector) to place a tile on e.g. TileMap[x][y][z]

     @param   const sf::IntRect   texture_rect    The texture rectangle from the TileSheet texture to paste.

     @param   const bool&   collision   The boolean value that controlls wether or not a placed tile will have collision.

     @param   const short&   type    The enumerator value representing the type of tile placed.

     @return void


       */

    if (x < this->MaxSizeWorldGrid.x && x >= 0
        && y < this->MaxSizeWorldGrid.y && y >= 0
        && z < this->layers && z >= 0) {
        /*if okay to add tile*/
        // and if the type of tile is NORMAL add normal til

        this->Map[x][y][z].push_back(new NormalTile(type, x, y, this->grid_sizeF, this->tileTextureSheet, texture_rect, collision));

    } // this->Map[x][y][z](new NormalTile(type, x, y, this->grid_sizeF, this->tileTextureSheet, texture_rect, collision));
}

void TileMap::addObject(const short type, const int x, const int y)
{
    /// this->objecthandler->Place_Object(type, x, y, this->Map[x][y]);
}




void TileMap::RemoveTile(const int x, const int y, const int z, const int type)
{

    if (x < this->MaxSizeWorldGrid.x && x >= 0 && y < this->MaxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0) {
        if (!this->Map[x][y][z].empty()) {

            if (this->Map[x][y][z].back()->gettype() == type) {

                delete this->Map[x][y][z][this->Map[x][y][z].size() - 1];
                this->Map[x][y][z].pop_back();
                std::cout << "Spawner Removed" << std::endl;

            } else {

                delete this->Map[x][y][z][this->Map[x][y][z].size() - 1];
                this->Map[x][y][z].pop_back();
                std::cout << "TIle Removed" << std::endl;
            }
        }
    }
}

const sf::Texture* TileMap::getTileSheet() const
{
    return &this->tileTextureSheet;
}

bool TileMap::saveToFile(const std::string& filename, bool json)
{
    // assert(json);
    //std::cout << json << std::endl;
    /*!
      @brief  Saves a vector of tiles as a string of integers to a document.

      @param   const std::string filename   the name of the file to create and save to.

      @discussion
            Maxsize of the Vector:
            Size of the tile grid:
            texture rect value of the tiles at position x, y, z:
            collision value of the tiles at position x, y, z:
            type of the tiles at position x, y, z:

      @return void
        */
    // int string_size1 = this->texture_file.length();
    // std::cout << string_size1 << std::endl;

    if (json) {

        // pt.put("Map.Config.MaxSizeWorldGrid.x", this->MaxSizeWorldGrid.x);
        // pt.put("Map.Config.MaxSizeWorldGrid.y", this->MaxSizeWorldGrid.y);
        // pt.put("Map.Config.GridsizeI.x", this->gridsizeI.x);
        // pt.put("Map.Config.GridsizeI.y", this->gridsizeI.y);
        // pt.put("Map.Config.layers", this->layers);
        // pt.put("Map.Config.level_type", this->level_type);
        // pt.put("Map.Config.level_index", this->level_index);
        // pt.put("Map.Config.texture", this->texture_file);

        /// I hate white people.
        // boost::property_tree::ptree tiles_node;
        int index = 0;
        // This is a four dimensional tilemap vector...
        // please just make it easier on yourself. there is no other way to do this

        // for (int x = 0; x < this->MaxSizeWorldGrid.x; x++) {

        // for (int y = 0; y < this->MaxSizeWorldGrid.y; y++) {

        // for (int z = 0; z < this->layers; z++) {

        //   if (!this->Map[x][y][z].empty()) {

        //  for (size_t k = 0; k < this->Map[x][y][z].size(); k++) {

        //   index++;

        //  tiles_node.put(std::to_string(index) + ".x", x);
        // tiles_node.put(std::to_string(index) + ".y", y);
        // tiles_node.put(std::to_string(index) + ".z", z);

        // tiles_node.put(std::to_string(index) + ".xFloat", this->Map[x][y][z][k]->getPosition().x);
        // tiles_node.put(std::to_string(index) + ".yFloat", this->Map[x][y][z][k]->getPosition().y);

        // tiles_node.put(std::to_string(index) + ".texture_rect.position.y",
        //     this->Map[x][y][z][k]->getTextureRect().position.y);
        // tiles_node.put(std::to_string(index) + ".texture_rect.size.x",
        //     this->Map[x][y][z][k]->getTextureRect().size.x);
        // tiles_node.put(std::to_string(index) + ".texture_rect.size.y",
        //    this->Map[x][y][z][k]->getTextureRect().size.y);
        // tiles_node.put(std::to_string(index) + ".type", this->Map[x][y][z][k]->gettype());
        // tiles_node.put(std::to_string(index) + ".collision", this->Map[x][y][z][k]->getCollision());
        // tiles_node.put(std::to_string(index) + ".texture_rect.position.x",
        // this->Map[x][y][z][k]->getTextureRect().position.x);

        // std::cout << "Object Type: " <<  this->Map[x][y][z][k]->gettype() << std::endl;

        // if (this->Map[x][y][z][k]->gettype() == TileTypes::OBJECT) {

        // tiles_node.put(std::to_string(index) + ".object_type",
        //  this->Map[x][y][z][k]->getObjectType());

        // }

        // else if (this->Map[x][y][z][k]->gettype() == TileTypes::SPAWNER) {

        // downcasting required to access data members in EnemySpawner
        // EnemySpawner* enemy_spawner = (EnemySpawner*)this->Map[x][y][z][k];

        // if (enemy_spawner) {

        //   tiles_node.put(std::to_string(index) + ".enemy_amount", enemy_spawner->getEnemyAmount());
        //   tiles_node.put(std::to_string(index) + ".enemy_type", enemy_spawner->getEnemyType());
        //   tiles_node.put(std::to_string(index) + ".timer", enemy_spawner->getTime());
        //   tiles_node.put(std::to_string(index) + ".maxDistance", enemy_spawner->getMaxDistance());
        // }
        // }
        // }
        //}
        //}
        //}
        //}

        // this->pt.put_child("tiles", tiles_node);

        // boost::property_tree::json_parser::write_json("Data/TileMap/" + filename, this->pt);
        // return true;
    } else {

        std::ofstream out(filename);

        // this->randomGeneration();
       // out.open(filename, std::ios::out);

        if (out.is_open()) {
            // DONT CHANGE THIS SHIT

            std::cout << std::hex << this->MaxSizeWorldGrid.x << " " << this->MaxSizeWorldGrid.y << "\n"
            << this->gridsizeI.x << " " << this->gridsizeI.y << "\n"
            << this->layers << "\n"
            << this->texture_file << "\n";

            out << std::hex << this->MaxSizeWorldGrid.x << " " << this->MaxSizeWorldGrid.y << "\n"
                << this->gridsizeI.x << " " << this->gridsizeI.y << "\n"
                << this->layers << "\n"
                << this->texture_file << "\n";

            for (int x = 0; x < this->MaxSizeWorldGrid.x; x++) {

                for (int y = 0; y < this->MaxSizeWorldGrid.y; y++) {

                    for (int z = 0; z < this->layers; z++) {

                        if (!this->Map[x][y][z].empty()) {
                            for (size_t k = 0; k < this->Map[x][y][z].size(); k++) {

                                out << x << " " << y << " " << z << " " << this->Map[x][y][z][k]->asString() << " ";
                            }
                        }
                    }
                }
            }

        }

        else {
             std::cerr << "Error: [TileMap::savetoFile() 468] " << std::strerror(errno) << std::endl;
            // LOG(FATAL) << "Throwing runtime exception on line 647...";
            //throw std::runtime_error("ERROR CODE TILEMAP:392 || TILEMAP::SAVETOFILE || COULD NOT SAVE");
             out.close();
            return false;
        }

        out.close();

        return true;
    }
    // Create a catch handler wherever this function is called, since the scope of the throw statement
    // makes it so that it's destroyed immediatley after the function has returned a value.
}

const std::vector<int> TileMap::getLayer(const int& layer) const{

    std::vector<int> tiledata;
for (int x = 0; x < this->MaxSizeWorldGrid.x; x++)
{
 for (int y = 0; y < this->MaxSizeWorldGrid.y; y++)
 {
   if(!this->Map[x][y][layer].empty())
   {
       for (size_t k = 0; k < this->Map[x][y][layer].size(); k++) {

           tiledata.push_back(this->Map[x][y][layer][k]->getTextureRect().position.x);
       }
   }
 }
}

return tiledata;
}

bool TileMap::exportTMX(const std::string& filename)
{
    tinyxml2::XMLDocument doc;

    // 1. Add XML Declaration
    doc.NewDeclaration(nullptr);

    // 2. Create Root Map Node
    tinyxml2::XMLElement* mapNode = doc.NewElement("map");
    mapNode->SetAttribute("version", "1.10");
    mapNode->SetAttribute("tiledversion", "1.10.2");
    mapNode->SetAttribute("orientation", "orthogonal");
    mapNode->SetAttribute("renderorder", "right-down");
    mapNode->SetAttribute("width", this->MaxSizeWorldGrid.x);
    mapNode->SetAttribute("height", this->MaxSizeWorldGrid.y);
    mapNode->SetAttribute("tilewidth", 32);
    mapNode->SetAttribute("tileheight", 24);
    mapNode->SetAttribute("infinite", 0);
    doc.InsertEndChild(mapNode);

    // 3. Create Embedded Tileset Node
    tinyxml2::XMLElement* tilesetNode = doc.NewElement("tileset");
    tilesetNode->SetAttribute("firstgid", 1);
    tilesetNode->SetAttribute("name", "main");
    tilesetNode->SetAttribute("tilewidth", 32);
    tilesetNode->SetAttribute("tileheight", 24);

    tinyxml2::XMLElement* imageNode = doc.NewElement("image");
    imageNode->SetAttribute("source", "Resources/Assets/Tiles/sheet.png");
    // Note: You can optionally add image width/height source properties here if known
    tilesetNode->InsertEndChild(imageNode);

    mapNode->InsertEndChild(tilesetNode);

    // Safety Check: Ensure the map has at least one valid X column to read layer counts
    if (this->Map.empty() || this->Map[0].empty() || this->Map[0][0].empty()) {
        std::cerr << "Map container is empty or unallocated." << std::endl;
        return false;
    }

    // Determine total layers dynamically based on your 4th dimension size

    // 3. Export Layer-by-Layer (Tiled expects outer structural chunks per layer)
    for (size_t layerIndex = 0; layerIndex < this->layers; ++layerIndex) {
        tinyxml2::XMLElement* layerNode = doc.NewElement("layer");
        layerNode->SetAttribute("id", static_cast<int>(layerIndex + 1));
        layerNode->SetAttribute("name", ("Layer " + std::to_string(layerIndex)).c_str());
        layerNode->SetAttribute("width", this->MaxSizeWorldGrid.x);
        layerNode->SetAttribute("height", this->MaxSizeWorldGrid.y);

        tinyxml2::XMLElement* dataNode = doc.NewElement("data");
        dataNode->SetAttribute("encoding", "csv");

        std::stringstream csvStream;


        // Tiled writes CSV rows from top to bottom (Y), then left to right (X)
        for (int y = 0; y < this->MaxSizeWorldGrid.y; ++y) {
            for (int x = 0; x < this->MaxSizeWorldGrid.x; ++x) {
                  int gid =0;
                if(!this->Map[x][y][layerIndex].empty()){
                    for(int k = 0; k < this->Map[x][y][layerIndex].size(); k++){

                        Tile* tile = this->Map[x][y][layerIndex][k];
                        if (tile) {

                            gid = tile->getGid();
                        }}
                }


                csvStream << gid;

                // Format comma tracking safely
                if (!(y == this->MaxSizeWorldGrid.x - 1 && x == this->MaxSizeWorldGrid.x - 1)) {
                    csvStream << ",";
                    if (x == this->MaxSizeWorldGrid.x - 1) {
                        csvStream << "\n";
                    }
                }
            }
        }

        dataNode->SetText(csvStream.str().c_str());
        layerNode->InsertEndChild(dataNode);
        mapNode->InsertEndChild(layerNode);
    }

    return doc.SaveFile(filename.c_str()) == tinyxml2::XML_SUCCESS;

}

bool TileMap::importTMX(const std::string& filename)
{

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to open TMX file: " << filename << std::endl;
        return false;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("map");
    if (!root) return false;

    tinyxml2::XMLElement* tilesetElem = root->FirstChildElement("tileset");
    if (!tilesetElem) {
        std::cerr << "TMX Missing <tileset> element." << std::endl;
        return "";
    }

    tinyxml2::XMLElement* texture = tilesetElem->FirstChildElement("image");
    if (!texture) {
        std::cerr << "TMX <tileset> is missing <image> attribute" << std::endl;
        return "";
    }

    const char* sourceAttr = texture->Attribute("source");
    if (!sourceAttr) {
        std::cerr << "TMX <tileset><image> is missing an image source attribute, unable to find tileset texture " << std::endl;
    }


    // 1. Read Map Attributes
    this->Map.resize(this->MaxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
    this->grid_sizeF.x = static_cast<float>(root->IntAttribute("tilewidth"));
    this->grid_sizeF.y = static_cast<float>(root->IntAttribute("tileheight"));
    this->gridsizeI = sf::Vector2i(root->IntAttribute("tilewidth"),root->IntAttribute("tileheight"));
    this->MaxSizeWorldGrid.x = root->IntAttribute("width");
    this->MaxSizeWorldGrid.y = root->IntAttribute("height");
    this->MaxSizeWorld_F.x = static_cast<float>(root->IntAttribute("width")) * this->grid_sizeF.x;
    this->MaxSizeWorld_F.y = static_cast<float>(root->IntAttribute("height")) * this->grid_sizeF.y;

    if(!this->tileTextureSheet.loadFromFile((std::filesystem::weakly_canonical(sourceAttr).string())))
    {
        std::cerr << "unable to load tmx tileset texture" << std::endl;
    };

    int layerCount = 0;
    for (tinyxml2::XMLElement* e = root->FirstChildElement("layer"); e != nullptr; e = e->NextSiblingElement("layer")) {
        std::cout << "found layer!" << std::endl;
        layerCount++;
    }
    this->layers = layerCount;
    this->clear();
   // this->Map.resize(layerCount);
    this->Map.resize(this->MaxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

    for (int x = 0; x < this->MaxSizeWorldGrid.x; x++) {

        for (int y = 0; y < this->MaxSizeWorldGrid.y; y++) {
            this->Map[x].resize(this->MaxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

            for (int z = 0; z < this->layers; z++) {

                this->Map[x][y].resize(this->layers, std::vector<Tile*>());
            }
        }
    }


    // load layers in
    int currentLayerIndex = 0;
    tinyxml2::XMLElement* layerNode = root->FirstChildElement("layer");
    while(layerNode){

        tinyxml2::XMLElement* dataNode = layerNode->FirstChildElement("data");
        if (!dataNode){
            std::cout << "no data node" << std::endl;
            return false;
        }

        std::string encoding = dataNode->Attribute("encoding") ? dataNode->Attribute("encoding") : "csv";
        if (encoding != "csv") {
            std::cerr << "Error: This parser only supports TMX files saved with CSV formatting." << std::endl;
            return false;
        }

        const char* csvText = dataNode->GetText();
        /// std::cout << csvText << std::endl;
        if (csvText) {
            std::cout << "there is csv text" << std::endl;
            std::stringstream ss(csvText);
            std::string item;
            int tileCounter = 0;

            while(std::getline(ss,item,',')){
                item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());
                if (item.empty()) continue;
                int x = tileCounter % this->MaxSizeWorldGrid.x;
                int y = tileCounter / this->MaxSizeWorldGrid.x;
                std::cout << "item" << std::endl;

                int gid = std::stoi(item);
                std::cout << "adding tile " << gid << std::endl;
                if (gid != 0) {
                    // Create your tile instance (or fetch it from a tileset resource manager)
                    //Tile* newTile = new Tile(gid);
                    sf::IntRect tilerect = this->calcTileRect(gid, this->gridsizeI);

                    // Push into Map[x][y][layer][tiledata]
                    this->Map[x][y][0].push_back(new NormalTile(TileTypes::NORMAL,static_cast<float>(x), static_cast<float>(y),this->grid_sizeF,this->tileTextureSheet,tilerect));
                }
                tileCounter++;
        }

    }
      currentLayerIndex++;
      layerNode = layerNode->NextSiblingElement("layer");
    }

     return true;
}
sf::IntRect TileMap::calcTileRect(const int& gid, sf::Vector2i tileSize)
{
    sf::IntRect rect;
    if (gid <= 0) {
        rect.position.x =  0;
        rect.position.y = 0;
        rect.size.x = tileSize.x;
        rect.size.y = tileSize.y;
        return rect;
    }
    int columns = static_cast<int>(this->tileTextureSheet.getSize().x) / static_cast<int>(tileSize.x);
    //int rows = static_cast<int>(this->rect.getTexture().getSize().y) / static_cast<int>(tileSize.y);
    int column = gid % columns;
    int row = gid / columns;

    //int cellX = this->rect.getTextureRect().position.x / tileSize.x;
    //int cellY = this->rect.getTextureRect().position.y / tileSize.y;

    //int gridIndex = (cellY * columns) + cellX;
    rect.position.x =  (column * tileSize.x);
    rect.position.y =  (row * tileSize.y);
    rect.size.x = tileSize.x;
    rect.size.y = tileSize.y;
    return rect;
}
bool TileMap::loadFromFile(const std::string filename, bool json)
{

    if (json) {
        // this->grid_sizeF.x = this->pt.get<float>("Map.Config.GridsizeI.x");
        //
        //
        // this->grid_sizeF.y = this->pt.get<float>("Map.Config.GridsizeI.y");

        // boost::property_tree::json_parser::read_json(filename, this->pt);
        // this->gridsizeI = sf::Vector2i(this->pt.get<int>("Map.Config.GridsizeI.x"), this->pt.get<int>("Map.Config.GridsizeI.y"));
        // this->grid_sizeF.x = static_cast<float>(this->gridsizeI.x);
        // this->grid_sizeF.y = static_cast<float>(this->gridsizeI.y);
        // this->MaxSizeWorldGrid.x = this->pt.get<int>("Map.Config.MaxSizeWorldGrid.x");
        // this->MaxSizeWorldGrid.y = this->pt.get<int>("Map.Config.MaxSizeWorldGrid.y");
        // this->MaxSizeWorld_F.x = static_cast<float>(this->MaxSizeWorldGrid.x * gridsizeI.x);
        // this->MaxSizeWorld_F.y = static_cast<float>(this->MaxSizeWorldGrid.y * gridsizeI.y);
        // this->layers = this->pt.get<short>("Map.Config.layers");
        // this->level_index = this->pt.get<short>("Map.Config.level_index");
        // this->level_index = level_type;
        // this->texture_file = this->pt.get<std::string>("Map.Config.texture");

        // std::cout << gridsizeI.x << " " << gridsizeI.y << " current gridsie"

        this->clear();

        this->Map.resize(this->MaxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

        for (int x = 0; x < this->MaxSizeWorldGrid.x; x++) {

            for (int y = 0; y < this->MaxSizeWorldGrid.y; y++) {
                this->Map[x].resize(this->MaxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

                for (int z = 0; z < this->layers; z++) {
                    this->Map[x][y].resize(this->layers, std::vector<Tile*>());
                }
            }
        }

        int total = 0;
        // for (boost::property_tree::ptree::value_type& tile : pt.get_child("tiles")) {

        //  total++;
        // std::cout << "Tile NO:" << tile.first << std::endl;
        // std::cout << "Tile data " <<  tile.second.data()<< std::endl;
        // std::cout << "position x " << tile.second.get<int>("x") << std::endl;
        // std::cout << "position y " << tile.second.get<int>("y") << std::endl;
        // std::cout << "position z " << tile.second.get<int>("z") << std::endl;

        // if the tile is an object tile (2), call the object tile constructor
        //  if (tile.second.get<unsigned>("type") == TileTypes::OBJECT) {
        //     this->Map[tile.second.get<int>("x")][tile.second.get<int>("y")][tile.second.get<int>("z")].push_back(new ObjectTile(tile.second.get<int>("x"), tile.second.get<int>("y"), this->grid_sizeF, this->tileTextureSheet, sf::IntRect(tile.second.get<unsigned>("texture_rect.position.x"), tile.second.get<unsigned>("texture_rect.position.y"), this->gridsizeI.x, this->gridsizeI.y), tile.second.get<short>("object_type")));
        // }
        // if the tile is an enemy spawner tile (3), call the enemy spawner tile constructor
        // if (tile.second.get<unsigned>("type") == TileTypes::SPAWNER) {
        //     this->Map[tile.second.get<int>("x")][tile.second.get<int>("y")][tile.second.get<int>("z")].push_back(new EnemySpawner(tile.second.get<int>("x"), tile.second.get<int>("y"), this->grid_sizeF, this->tileTextureSheet, //sf::IntRect(tile.second.get<unsigned>("texture_rect.position.x"), tile.second.get<unsigned>("texture_rect.position.y"), this->gridsizeI.x, this->gridsizeI.y), tile.second.get<int>("enemy_type"), tile.second.get<int>("enemy_amount"), tile.second.get<sf::Int32>("timer"), tile.second.get<float>("maxDistance")));

        // }

        // else
        // std::cout << "pushing back new normal tile at postion " << tile.second.get<int>("x") << tile.second.get<int>("y") << tile.second.get<int>("z") << std::endl;
        // this->Map[tile.second.get<int>("x")][tile.second.get<int>("y")][tile.second.get<int>("z")].push_back(new NormalTile(TileTypes::NORMAL, tile.second.get<int>("x"), tile.second.get<int>("y"), this->grid_sizeF, this-//>tileTextureSheet, sf::IntRect(tile.second.get<unsigned>("texture_rect.position.x"), tile.second.get<unsigned>("texture_rect.position.y"), this->gridsizeI.x, this->gridsizeI.y), tile.second.get<bool>("collision")));
        //}
        // std::cout << "total tiles: " << total << std::endl;

        // if (!this->tileTextureSheet.loadFromFile(texture_file)) {
        //  LOG(WARNING) << "Unable to read data from texture file '" << texture_file << "'";
        //  LOG(FATAL) << "Throwing runtime exception on line 761...";

        // throw std::runtime_error("ERROR CODE TILEMAP:458 || LOADFROMFILE || Reason: UNABLE_TO_OPEN_FILE");
        //}

        // return true;
    } else {
        std::ifstream in;

        in.open(filename, std::ios::in);

        if (in.is_open())

        {
            sf::Vector2i size;
            // int gridSize = 0;
            sf::Vector2i gridsize;
            // unsigned gridsize_x;
            // unsigned gridsize_y;
            int layers = 0;
            std::string texture_file = "";
            int x = 0;
            int y = 0;
            int z = 0;
            int textureX = 0;
            int textureY = 0;
            bool collision = false;
            int type = 0;
            int level_type;
            int index;

            // Basic Variables
            // std::cout << gridSize.x << " " << gridSize.y << std::endl;
            in >> std::hex >> size.x >> size.y >> gridsize.x >> gridsize.y >> layers  >> texture_file;
            // std::cout << gridSize.x << " " << gridSize.y << std::endl;
            std::cout << size.x << size.y << std::endl;

            // Tiles

            this->grid_sizeF.x = static_cast<float>(gridsize.x);
            this->grid_sizeF.y = static_cast<float>(gridsize.y);
            this->gridsizeI = sf::Vector2i(gridsize.x, gridsize.y);
            this->MaxSizeWorldGrid.x = size.x;
            this->MaxSizeWorldGrid.y = size.y;
            this->MaxSizeWorld_F.x = static_cast<float>(size.x) * gridsize.x;
            this->MaxSizeWorld_F.y = static_cast<float>(size.y) * gridsize.y;
            this->layers = layers;
            this->texture_file = texture_file;

            this->clear();

            this->Map.resize(this->MaxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

            for (int x = 0; x < this->MaxSizeWorldGrid.x; x++) {

                for (int y = 0; y < this->MaxSizeWorldGrid.y; y++) {
                    this->Map[x].resize(this->MaxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

                    for (int z = 0; z < this->layers; z++) {
                        this->Map[x][y].resize(this->layers, std::vector<Tile*>());

                    } // sf::Vector2f();
                }
            }

            if (!this->tileTextureSheet.loadFromFile(texture_file)) {
                // LOG(WARNING) << "Unable to read data from texture file '" << texture_file << "'";
                // LOG(FATAL) << "Throwing runtime exception on line  858...";

                throw std::runtime_error("ERROR CODE TILEMAP:458 || LOADFROMFILE || Reason: UNABLE_TO_FIND_TEXTURE");
            }

            while (in >> std::hex >> x >> y >> z >> type) {
                // std::cout << "reading the x position... it's " << x << std::endl;
                // std::cout << "reading the y position it's  " << y << std::endl;
                // std::cout << "reading the layer... it's " << z << std::endl;
                // std::cout << "\n";

                if (type == 2) {

                    float obX = 0.f;
                    float obY = 0.f;
                    short ObjectType = 0;

                    in >> std::hex >> textureX >> textureY >> ObjectType >> obX >> obY;

                    //  std::cout << "reading the object tile position X: it's  " << obX << "position Y:  " << obY << " " << std::endl;
                    // std::cout << "reading the object tile object type it's " << ObjectType << std::endl;
                    // std::cout << "reading the Object texutre rect X it's  " << textureX << "& " << textureY << "\n";
                    this->Map[x][y][z].push_back(new ObjectTile(obX, obY, this->grid_sizeF, this->object_textures["LANTERN"], sf::IntRect(sf::Vector2i(textureX, textureY), sf::Vector2i(this->gridsizeI.x, this->gridsizeI.y)), ObjectType));

                }
                // very important for all of these to be ELSE IF statements, otherwise garbage happens.

                // This is the snippet called for most of the tiles usually, all normal tiles will default to this else statement
                else {
                     std::cout << "Texture X: " << textureY << std::endl;
                     std::cout << "Texture Y" << textureX << std::endl;
                     std::cout << "reading the layer... it's " << z << std::endl;
                    in >> std::hex >> textureX >> textureY >> collision;
                     std::cout << "the grid size in normal tiles  " << grid_sizeF.x << " " << grid_sizeF.y << std::endl;
                     std::cout << "the position for norm tile " << x << " " << y << std::endl;

                    this->Map[x][y][z].push_back(new NormalTile(TileTypes::NORMAL, x, y, grid_sizeF, this->tileTextureSheet, sf::IntRect(sf::Vector2i(static_cast<int>(textureX), static_cast<int>(textureY)), sf::Vector2i(this->gridsizeI.x, this->gridsizeI.y)), collision));
                }
            }

            return true;
        } else {
            std::cout << "ERROR CODE TILEMAP:3 || LOADFROMFILE || UNABLE TO READ TILEMAP DATA" << std::endl;
            in.close();
             return false;
            //throw std::runtime_error("ERROR CODE TILEMAP:3 || LOADFROMFILE || UNABLE TO READ TILEMAPDATA");

        }

        in.close();
    }
    return false;
}



void TileMap::update(Entity* entity, const float& dt)
{
    // this->randomGeneration();
    // this->objecthandler->update(dt);
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
    /*!
     @breif   Get the number of tiles placed on one grid position.

     @param   const int   x   The X-value (relative to the Tilemap vector) to place a tile on. e.g. TileMap[x]

     @param   const int   y   The Y-value (relative to the Tilemap vector) to place a tile on. e.g. TileMap[x][y]

     @param   const int   z   The Z-value (relative to the Tilemap vector) to place a tile on e.g. TileMap[x][y][z]

     @return  const int   The Number Of tiles Placed on a grid.

     @return  unsigned    Outside of the Tilemap bounds if the return value from this function is negative.
    */

    if (x >= 0 && x < static_cast<int>(this->Map.size())) {
        if (y >= 0 && y < static_cast<int>(this->Map[x].size())) {
            if (layer >= 0 && layer < static_cast<int>(this->Map[x][y].size())) {
                return static_cast<int>(this->Map[x][y][layer].size());
            }
        }
    }
    // Error or Zero tiles
    return -1;
}

void TileMap::DefferedRender(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f PlayerPosition)
{

    /*!   @brief Renders certian elements of the tilemap behind the main view.

         @param  sf::RenderTarget& target   The intended render target.

         @return void    */

    while (!this->renderdefered.empty()) {
        if (shader) {
            this->renderdefered.top()->render(target, shader, PlayerPosition);
            this->renderdefered.pop();
        }

        else {
            this->renderdefered.top()->render(target);
            this->renderdefered.pop();
        }
    }
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
    /**
                    @brief Acessor that returns the maximum size of the Tilemap as a vector of two integers. (width x height)
                    @return sf::Vector2i     The maximum size of the tilemap as a vector of two integers
                    @see TileMap::getMaxSize()

     */
    return this->MaxSizeWorldGrid;
}

const sf::Vector2f TileMap::getMaxSize() const
{ /**
   @brief Acessor that returnts the maximum size of the TIlemap as a vector of two floating points
   @return sf::Vector2f the maximum size of the tilemap as a vector of two floaing points
    @see Tilemap::getMaxSizeGrid()
   */
    // LOG(INFO) << "Max Tilemap world size " << this->MaxSizeWorld_F.x;
    return this->MaxSizeWorld_F;
}

const sf::Vector2f TileMap::get_objectTile()
{
    if (!this->Map.empty()) {
        for (int x = 0; x < this->Map.size(); x++) {
            for (int y = 0; y < this->Map[x].size(); y++) {
                for (int z = 0; z < this->Map[x][y].size(); z++) {
                    for (size_t k = 0; k < this->Map[x][y][z].size(); k++) {
                        ObjectTile* ob = dynamic_cast<ObjectTile*>(this->Map[x][y][this->layer][k]);
                        if (ob) {
                            return sf::Vector2f(ob->getGlobalBounds().size.x / 2.f, ob->getGlobalBounds().size.y / 2.f);
                        }
                    }
                }
            }
        }
    }
}



const bool TileMap::TileEmpty(const int x, const int y, const int z) const
{

    if (x >= 0 && x < this->MaxSizeWorldGrid.x && y >= 0 && y < this->MaxSizeWorldGrid.y && z >= 0 && z < this->layers) {

        return this->Map[x][y][z].empty();

    }

    else if (x < 0 || y < 0 || z < 0) {
        return false;
    }

    else if (!x || !y || !z) {
        throw std::invalid_argument("Invalid Argument: Tile does not exist");
    }
}

const bool TileMap::checktype(const int x, const int y, const int z, const int type) const
{

    return this->Map[x][y][this->layer].back()->gettype() == type;
}



void TileMap::addTile(const int x, const int y, const int z, float obX, float obY, const short type)
{
    std::cout << "Object Tile Function called " << std::endl;
    if (x < this->MaxSizeWorldGrid.x && x >= 0
        && y < this->MaxSizeWorldGrid.y && y >= 0
        && z < this->layers && z >= 0) {

        this->Map[x][y][z].push_back(new ObjectTile(obX, obY, this->grid_sizeF, this->object_textures["LANTERN"], sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(9, 16)), type));
    }
}

void TileMap::updateWorldBoundsCollision(Entity* entity, const float& dt)
{
    // World Bounds
    if (entity->getPosition().x < 0.f) {
        entity->setPosition(0.f, entity->getPosition().y);
        entity->stopVelocityX();
        std::cout << "Hitting Upper world bound" << std::endl;
    } else if (entity->getPosition().x + entity->getGlobalBounds().size.x > this->MaxSizeWorld_F.x) {
        entity->setPosition(this->MaxSizeWorld_F.x - entity->getGlobalBounds().size.x, entity->getPosition().y);
        entity->stopVelocityX();
        std::cout << "Hitting Upper left world bound" << std::endl;
    }
    if (entity->getPosition().y < 0.f) {
        entity->setPosition(entity->getPosition().x, 0.f);
        entity->stopVelocityY();
        std::cout << "hitting left world bound" << std::endl;
    } else if (entity->getPosition().y + entity->getGlobalBounds().size.y > this->MaxSizeWorld_F.y) {
        entity->setPosition(entity->getPosition().x, this->MaxSizeWorld_F.y - entity->getGlobalBounds().size.y);
        entity->stopVelocityY();
        std::cout << "hitting right world boundary" << std::endl;
    }
}

void TileMap::updateTiles(Entity* entity, const float& dt)
{
    this->layer = 0;

    this->FromX = entity->getGridPosition(this->gridsizeI.x).x - 2;

    if (this->FromX < 0)
        this->FromX = 0;
    else if (this->FromX > this->MaxSizeWorldGrid.x)
        this->FromX = this->MaxSizeWorldGrid.x;

    this->ToX = entity->getGridPosition(this->gridsizeI.x).x + 27;

    if (this->ToX < 0)
        this->ToX = 0;
    else if (this->ToX > this->MaxSizeWorldGrid.x)
        this->ToX = this->MaxSizeWorldGrid.x;

    this->FromY = entity->getGridPosition(this->gridsizeI.y).y - 27;

    if (this->FromY < 0)
        this->FromY = 0;
    else if (this->FromY > this->MaxSizeWorldGrid.x)
        this->FromY = this->MaxSizeWorldGrid.x;

    this->ToY = entity->getGridPosition(this->gridsizeI.y).y + 27;

    if (this->ToY < 0)
        this->ToY = 0;
    else if (this->ToY > this->MaxSizeWorldGrid.x)
        this->ToY = this->MaxSizeWorldGrid.x;

    for (int x = this->FromX; x < this->ToX; x++) {
        for (int y = this->FromY; y < this->ToY; y++) {
            for (size_t k = 0; k < this->Map[x][y][this->layer].size(); k++) {

                this->Map[x][y][this->layer][k]->update(dt);

                if (this->Map[x][y][this->layer][k]->gettype() == TileTypes::SPAWNER) {
                    //TileYouWant* t = dynamic_cast<TileClass*>(this->Map[x][y][this->layer][k]);
                    //
                        }
                    }
                }
            }
}



void TileMap::updateTileCollision(Entity* entity, const float& dt)
{

    // Tile Culling
    // Check for Texturerect angular wall collisons,
    /// reduce and rediret sprite vel on impact?
    // if(this->fromX.tan(90) this->GridPosition(this->gridsizeI).x -27;

    this->layer = 0;

    this->FromX = entity->getGridPosition(this->gridsizeI.x).x - 27;

    if (this->FromX < 0)
        this->FromX = 0;
    else if (this->FromX > this->MaxSizeWorldGrid.x)
        this->FromX = this->MaxSizeWorldGrid.x;

    this->ToX = entity->getGridPosition(this->gridsizeI.x).x + 27;

    if (this->ToX < 0)
        this->ToX = 0;
    else if (this->ToX > this->MaxSizeWorldGrid.x)
        this->ToX = this->MaxSizeWorldGrid.x;

    this->FromY = entity->getGridPosition(this->gridsizeI.y).y - 27;

    if (this->FromY < 0)
        this->FromY = 0;
    else if (this->FromY > this->MaxSizeWorldGrid.x)
        this->FromY = this->MaxSizeWorldGrid.x;

    this->ToY = entity->getGridPosition(this->gridsizeI.y).y + 27;

    if (this->ToY < 0)
        this->ToY = 0;
    else if (this->ToY > this->MaxSizeWorldGrid.x)
        this->ToY = this->MaxSizeWorldGrid.x;

    // Fix Collision with Objects
    // Get Objects to Fucking render finally

    for (int x = this->FromX; x < this->ToX; x++) {
        for (int y = this->FromY; y < this->ToY; y++) {
            for (size_t k = 0; k < this->Map[x][y][this->layer].size(); k++) {

                sf::FloatRect playerBounds = entity->getGlobalBounds();
                sf::FloatRect wallBounds = sf::FloatRect();
                if (this->Map[x][y][this->layer][k]) {
                    wallBounds = this->Map[x][y][this->layer][k]->getGlobalBounds();
                } else {
                    wallBounds = this->Map[x][y][this->layer][k]->getGlobalBounds();
                }

                sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

                if (this->Map[x][y][this->layer][k]->getCollision() && this->Map[x][y][this->layer][k]->intersects(nextPositionBounds)) {
                    // Bottom collision
                    if (playerBounds.position.y < wallBounds.position.y
                        && playerBounds.position.y + playerBounds.size.y < wallBounds.position.y + wallBounds.size.y
                        && playerBounds.position.x < wallBounds.position.x + wallBounds.size.x
                        && playerBounds.position.x + playerBounds.size.x > wallBounds.position.x) {
                        entity->stopVelocityY();
                        entity->setPosition(playerBounds.position.x, wallBounds.position.y - playerBounds.size.y);

                    }

                    // Top collision
                    else if (playerBounds.position.y > wallBounds.position.y
                        && playerBounds.position.y + playerBounds.size.y > wallBounds.position.y + wallBounds.size.y
                        && playerBounds.position.x < wallBounds.position.x + wallBounds.size.x
                        && playerBounds.position.x + playerBounds.size.x > wallBounds.position.x) {
                        entity->stopVelocityY();
                        entity->setPosition(playerBounds.position.x, wallBounds.position.y + wallBounds.size.y);
                    }

                    // Right collision
                    if (playerBounds.position.x < wallBounds.position.x
                        && playerBounds.position.x + playerBounds.size.x < wallBounds.position.x + wallBounds.size.x
                        && playerBounds.position.y < wallBounds.position.y + wallBounds.size.y
                        && playerBounds.position.y + playerBounds.size.y > wallBounds.position.y) {
                        entity->stopVelocityX();
                        entity->setPosition(wallBounds.position.x - playerBounds.size.x, playerBounds.position.y);

                    }

                    // Left collision
                    else if (playerBounds.position.x > wallBounds.position.x
                        && playerBounds.position.x + playerBounds.size.x > wallBounds.position.x + wallBounds.size.x
                        && playerBounds.position.y < wallBounds.position.y + wallBounds.size.y
                        && playerBounds.position.y + playerBounds.size.y > wallBounds.position.y) {
                        entity->stopVelocityX();
                        entity->setPosition(wallBounds.position.x + wallBounds.size.x, playerBounds.position.y);
                    }
                }
            }
        }
    }
}



