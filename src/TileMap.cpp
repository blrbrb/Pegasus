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
    ValueGet() {
        data = 0;
    }
};

void TileMap::clear()
{
    //symmetry orgasim
    if(!this->Map.empty())
    {
        //LOG(INFO) << "Destroying Map Data..."; 
        for (int x=0; x < this->Map.size(); x++ )
             {
                 for (int y=0; y < this->Map[x].size(); y++ )
                 {
                     for (int z=0; z < this->Map[x][y].size(); z++ )
                     {
                         for (size_t k=0; k < this->Map[x][y][z].size(); k++)
                         {
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
        
        //LOG(INFO) << "Map object cleared, current memory size (bytes)" << " " << this->Map.size();
    }
}

void TileMap::initobjecthandler()
{ 
    //this->objecthandler = new ObjectHandler(this->Objects, this->textures);
}

void TileMap::initgeometry()
{ 

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

void TileMap::init_object_textures()
{
    std::cout << "the stupid fucking texture is being initalized " << std::endl;
    if (!this->object_textures["LANTERN"].loadFromFile("Resources/Assets/Entity/Objects/lantern.png"))
    {
        //LOG(FATAL) << "Unable to load object texture" << std::endl;

    }

}

void TileMap::initvariables()
{
    this->level_type = Level_Types::OVERWORLD; 
    this->level_index = 0;
    this->initgeometry(); 
    this->init_object_textures();
}

void TileMap::initloggingthread()
{
    //el::Helpers::setThreadName("%TileMap");
}







TileMap::TileMap(sf::Vector2f gridsize, int width, int height, std::string texture_file){
    
    
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

    //Tile Culling Vars
    
    this->ToX = 0;
    this->FromX = 0;
    this->ToY = 0;
    this->FromY = 0;
    this->layer = 0;

    this->Map.resize(this->MaxSizeWorldGrid.x, std::vector< std::vector< std::vector <Tile*> > > ());
    
    for (int x = 0; x < this->MaxSizeWorldGrid.x; x++ )
    {
        
        for (int y = 0; y < this->MaxSizeWorldGrid.y; y++ )
        {
            this->Map[x].resize(this->MaxSizeWorldGrid.y,std::vector< std::vector <Tile*> >());
  
            for (int z = 0; z < this->layers; z++ )
            {
                
                this->Map[x][y].resize(this->layers, std::vector<Tile*>());
                
            }
            
        }
    
    }
    
    this->tileTextureSheet.loadFromFile(texture_file);
    
         this->physicsrect.setSize(sf::Vector2f(grid_sizeF.x,grid_sizeF.y));
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

      this->init_object_textures();
    this->loadFromFile(map_file);
     
      
     
      
} 



//Default Overload, if no other args are provided to the constructor use a randomly generated sequence of map tiles.
TileMap::TileMap() 
{ 
    

}


TileMap::~TileMap()
{
   
    this->clear();
   
}

        
//Functions
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




    for (int x = this->FromX; x < this->ToX; x++)
    {
        for (int y = this->FromY; y < this->ToY; y++)
        {
            for (size_t k = 0; k < this->Map[x][y][this->layer].size(); k++)
            {
                

                    //render w/ shader applied
                    if (shader)
                    {
                        if (this->Map[x][y][this->layer][k]->gettype() == TileTypes::OBJECT)
                        {
                            this->renderdefered.push(this->Map[x][y][this->layer][k]);



                        }
                       
                        target.mapCoordsToPixel(this->Map[x][y][this->layer][k]->getPosition(), view);
                        this->Map[x][y][this->layer][k]->render(target, shader, PlayerPosition);
                        //std::string tile_info = this->Map[x][y][this->layer][k].tile->asString(); 
                       // std::cout << tile_info << std::endl;
                        //this->renderObjects(target);

                    }
                    else
                    {

                        if (this->Map[x][y][this->layer][k]->gettype() == TileTypes::OBJECT)
                        {
                            this->renderdefered.push(this->Map[x][y][this->layer][k]);



                        }

                        target.mapCoordsToPixel(this->Map[x][y][this->layer][k]->getPosition(), view);
                        this->Map[x][y][this->layer][k]->render(target);

                        //this->renderObjects(target);

                    }


                    //render the collision box
                    if (render_collision)
                    {
                        if (this->Map[x][y][this->layer][k]->getCollision())
                        {
                            this->physicsrect.setPosition(this->Map[x][y][this->layer][k]->getPosition());
                            target.draw(this->physicsrect);
                        }

                    }



                    if (this->Map[x][y][this->layer][k]->gettype() == TileTypes::SPAWNER)
                    {
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
    
    if ( x < this->MaxSizeWorldGrid.x && x >= 0
        && y < this->MaxSizeWorldGrid.y && y >= 0
        && z < this->layers && z >= 0 )
    {
             /*if okay to add tile*/
            //and if the type of tile is NORMAL add normal til
       
      
            this->Map[x][y][z].push_back(new NormalTile(type, x, y, this->grid_sizeF, this->tileTextureSheet, texture_rect, collision));
        
    }        //this->Map[x][y][z](new NormalTile(type, x, y, this->grid_sizeF, this->tileTextureSheet, texture_rect, collision));
    
    
}
    


void TileMap::addObject(const short type, const int x, const int y)
{
   /// this->objecthandler->Place_Object(type, x, y, this->Map[x][y]);
}

void TileMap::setLevelIndex(int index)
{
    this->level_index = index;
}

void TileMap::setType(short level_type)
{
    this->level_type = level_type;
}




void TileMap::RemoveTile(const int x, const int y, const int z, const int type)
{
    
    if ( x < this->MaxSizeWorldGrid.x && x >= 0 && y < this->MaxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0 )
       {
           if (!this->Map[x][y][z].empty())
           {
               
               if (this->Map[x][y][z].back()->gettype() == type)
               {
    
                   delete this->Map[x][y][z][this->Map[x][y][z].size() - 1];
                   this->Map[x][y][z].pop_back();
                   std::cout << "Spawner Removed" << std::endl;
                   
               }
               else
               {
                   
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




bool TileMap::saveToFile(const std::string filename, bool json)
{
    //assert(json); 
    std::cout << json << std::endl;
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
        //int string_size1 = this->texture_file.length(); 
        //std::cout << string_size1 << std::endl; 

    if (json) 
    {
        
         
        pt.put("Map.Config.MaxSizeWorldGrid.x", this->MaxSizeWorldGrid.x);
        pt.put("Map.Config.MaxSizeWorldGrid.y", this->MaxSizeWorldGrid.y);
        pt.put("Map.Config.GridsizeI.x", this->gridsizeI.x); 
        pt.put("Map.Config.GridsizeI.y", this->gridsizeI.y); 
        pt.put("Map.Config.layers", this->layers); 
        pt.put("Map.Config.level_type", this->level_type);
        pt.put("Map.Config.level_index", this->level_index);
        pt.put("Map.Config.texture", this->texture_file); 
       
        /// I hate white people. 
        boost::property_tree::ptree tiles_node; 
        int index = 0;
        //This is a four dimensional tilemap vector...
        //please just make it easier on yourself. there is no other way to do this 
       

        for (int x = 0; x < this->MaxSizeWorldGrid.x; x++)
        {


            for (int y = 0; y < this->MaxSizeWorldGrid.y; y++)
            {

                for (int z = 0; z < this->layers; z++)
                {


                    if (!this->Map[x][y][z].empty())
                    {
                        
                        for (size_t k = 0; k < this->Map[x][y][z].size(); k++)
                        {
                         
                            
                            index++;

                        
                         tiles_node.put(std::to_string(index) + ".x", x);
                         tiles_node.put(std::to_string(index) + ".y", y);
                         tiles_node.put(std::to_string(index) + ".z", z);
                       
                         tiles_node.put(std::to_string(index) + ".xFloat", this->Map[x][y][z][k]->getPosition().x);
                         tiles_node.put(std::to_string(index) + ".yFloat", this->Map[x][y][z][k]->getPosition().y);

                         tiles_node.put(std::to_string(index) + ".texture_rect.top",
                                        this->Map[x][y][z][k]->getTextureRect().top);
                         tiles_node.put(std::to_string(index) + ".texture_rect.width",
                                        this->Map[x][y][z][k]->getTextureRect().width);
                         tiles_node.put(std::to_string(index) + ".texture_rect.height",
                                        this->Map[x][y][z][k]->getTextureRect().height);
                         tiles_node.put(std::to_string(index) + ".type", this->Map[x][y][z][k]->gettype());
                         tiles_node.put(std::to_string(index) + ".collision", this->Map[x][y][z][k]->getCollision());
                         tiles_node.put(std::to_string(index) + ".texture_rect.left",
                                        this->Map[x][y][z][k]->getTextureRect().left);
                          

                          //std::cout << "Object Type: " <<  this->Map[x][y][z][k]->gettype() << std::endl;

                          
                          if (this->Map[x][y][z][k]->gettype() == TileTypes::OBJECT)
                          {
                             
                              tiles_node.put(std::to_string(index) + ".object_type",
                                             this->Map[x][y][z][k]->getObjectType());
                             
                          }

                          else if (this->Map[x][y][z][k]->gettype() == TileTypes::SPAWNER)
                          { 
                          
                              //downcasting required to access data members in EnemySpawner
                              EnemySpawner*  enemy_spawner= (EnemySpawner*)this->Map[x][y][z][k];
                             
                              if (enemy_spawner)
                              { 
                                
                                  tiles_node.put(std::to_string(index) + ".enemy_amount", enemy_spawner->getEnemyAmount());
                                  tiles_node.put(std::to_string(index) + ".enemy_type", enemy_spawner->getEnemyType());
                                  tiles_node.put(std::to_string(index) + ".timer", enemy_spawner->getTime());
                                  tiles_node.put(std::to_string(index) + ".maxDistance", enemy_spawner->getMaxDistance());

                              }
                              
                          }
                          
                          

                        
                         

                                                     
                        
                        }



                    }

                }

            }

        }

                        
                       
                    

       
       

        this->pt.put_child("tiles", tiles_node);

            boost::property_tree::json_parser::write_json("Data/TileMap/"+filename, this->pt);
        return true;
    }
    else {






        std::fstream out;

        // this->randomGeneration();
        out.open(filename, std::ios::out);

        if (out.is_open())
        {
            //DONT CHANGE THIS SHIT 

            out << std::hex << this->MaxSizeWorldGrid.x << " " << this->MaxSizeWorldGrid.y << "\n"
                << this->gridsizeI.x << " " << this->gridsizeI.y << "\n"
                << this->layers << "\n"
                << this->level_index << "\n"
                << this->level_type << "\n"
                << this->texture_file << "\n";





            for (int x = 0; x < this->MaxSizeWorldGrid.x; x++)
            {


                for (int y = 0; y < this->MaxSizeWorldGrid.y; y++)
                {

                    for (int z = 0; z < this->layers; z++)
                    {


                        if (!this->Map[x][y][z].empty())
                        {
                            for (size_t k = 0; k < this->Map[x][y][z].size(); k++)
                            {

                                out << x << " " << y << " " << z << " " << this->Map[x][y][z][k]->asString() << " ";
                                 



                            }



                        }

                    }

                }

            }

        }

        else
        {
            std::cout << "ERROR CODE TILEMAP:392 || TILEMAP::SAVETOFILE || COULD NOT SAVE" << std::endl;
            //LOG(WARNING) << "Unable to save raw data to tilemap file";
            //LOG(FATAL) << "Throwing runtime exception on line 647...";
            throw std::runtime_error("ERROR CODE TILEMAP:392 || TILEMAP::SAVETOFILE || COULD NOT SAVE");

            return false;

        }


        out.close();










        return true;
    }
    //Create a catch handler wherever this function is called, since the scope of the throw statement 
    //makes it so that it's destroyed immediatley after the function has returned a value. 


}




bool TileMap::loadFromFile(const std::string filename, bool json)
{
   
    if (json)
    {
       // this->grid_sizeF.x = this->pt.get<float>("Map.Config.GridsizeI.x");
       // 
       // 
       // this->grid_sizeF.y = this->pt.get<float>("Map.Config.GridsizeI.y");
      
        boost::property_tree::json_parser::read_json(filename, this->pt);
        this->gridsizeI = sf::Vector2i(this->pt.get<int>("Map.Config.GridsizeI.x"), this->pt.get<int>("Map.Config.GridsizeI.y"));
        this->grid_sizeF.x = static_cast<float>(this->gridsizeI.x);
        this->grid_sizeF.y = static_cast<float>(this->gridsizeI.y);
        this->MaxSizeWorldGrid.x = this->pt.get<int>("Map.Config.MaxSizeWorldGrid.x");
        this->MaxSizeWorldGrid.y = this->pt.get<int>("Map.Config.MaxSizeWorldGrid.y");
        this->MaxSizeWorld_F.x = static_cast<float>(this->MaxSizeWorldGrid.x * gridsizeI.x);
        this->MaxSizeWorld_F.y = static_cast<float>(this->MaxSizeWorldGrid.y * gridsizeI.y);
        this->layers = this->pt.get<short>("Map.Config.layers");
        this->level_index = this->pt.get<short>("Map.Config.level_index");
        this->level_index = level_type;
        this->texture_file = this->pt.get<std::string>("Map.Config.texture"); 
      

       // std::cout << gridsizeI.x << " " << gridsizeI.y << " current gridsie"


        this->clear();

        this->Map.resize(this->MaxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());


        for (int x = 0; x < this->MaxSizeWorldGrid.x; x++)
        {

            for (int y = 0; y < this->MaxSizeWorldGrid.y; y++)
            {
                this->Map[x].resize(this->MaxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

                for (int z = 0; z < this->layers; z++)
                {
                    this->Map[x][y].resize(this->layers, std::vector<Tile*>());

                }  

            }

        }

        int total = 0;
        for (boost::property_tree::ptree::value_type& tile : pt.get_child("tiles"))
        {
           
            total++;
            // std::cout << "Tile NO:" << tile.first << std::endl;
            //std::cout << "Tile data " <<  tile.second.data()<< std::endl;
            // std::cout << "position x " << tile.second.get<int>("x") << std::endl;    
            // std::cout << "position y " << tile.second.get<int>("y") << std::endl;
             //std::cout << "position z " << tile.second.get<int>("z") << std::endl;
            
             //if the tile is an object tile (2), call the object tile constructor 
            if(tile.second.get<unsigned>("type") == TileTypes::OBJECT)
            {
                this->Map[tile.second.get<int>("x")][tile.second.get<int>("y")][tile.second.get<int>("z")].push_back(new ObjectTile(tile.second.get<int>("x"), tile.second.get<int>("y"), this->grid_sizeF, this->tileTextureSheet, sf::IntRect(tile.second.get<unsigned>("texture_rect.left"), tile.second.get<unsigned>("texture_rect.top"), this->gridsizeI.x, this->gridsizeI.y), tile.second.get<short>("object_type")));

            }
            //if the tile is an enemy spawner tile (3), call the enemy spawner tile constructor 
            if (tile.second.get<unsigned>("type") == TileTypes::SPAWNER)
            {
                this->Map[tile.second.get<int>("x")][tile.second.get<int>("y")][tile.second.get<int>("z")].push_back(new EnemySpawner(tile.second.get<int>("x"), tile.second.get<int>("y"), this->grid_sizeF, this->tileTextureSheet, sf::IntRect(tile.second.get<unsigned>("texture_rect.left"), tile.second.get<unsigned>("texture_rect.top"), this->gridsizeI.x, this->gridsizeI.y), tile.second.get<int>("enemy_type"), tile.second.get<int>("enemy_amount"), tile.second.get<sf::Int32>("timer"), tile.second.get<float>("maxDistance")));

            }


            else
           // std::cout << "pushing back new normal tile at postion " << tile.second.get<int>("x") << tile.second.get<int>("y") << tile.second.get<int>("z") << std::endl; 
             this->Map[tile.second.get<int>("x")][tile.second.get<int>("y")][tile.second.get<int>("z")].push_back(new NormalTile(TileTypes::NORMAL, tile.second.get<int>("x"), tile.second.get<int>("y"), this->grid_sizeF, this->tileTextureSheet, sf::IntRect(tile.second.get<unsigned>("texture_rect.left"), tile.second.get<unsigned>("texture_rect.top"), this->gridsizeI.x, this->gridsizeI.y), tile.second.get<bool>("collision")));
 
        }
       // std::cout << "total tiles: " << total << std::endl;

        if (!this->tileTextureSheet.loadFromFile(texture_file))
        {
           // LOG(WARNING) << "Unable to read data from texture file '" << texture_file << "'";
            //LOG(FATAL) << "Throwing runtime exception on line 761...";

            throw std::runtime_error("ERROR CODE TILEMAP:458 || LOADFROMFILE || Reason: UNABLE_TO_OPEN_FILE");
        }


       



        return true; 
    }
    else {
        std::ifstream in;

        in.open(filename, std::ios::in);

        if (in.is_open())

        {
            sf::Vector2i size;
            //int gridSize = 0;
            sf::Vector2i gridsize;
            //unsigned gridsize_x; 
              //unsigned gridsize_y; 
            int layers = 0;
            int texture_file_buffer;
            const char* texture_file_temp;
            std::string texture_file = "";
            int x = 0;
            int y = 0;
            int z = 0;
            int textureX = 0;
            int textureY = 0;
            int objects_iterator = 0;
            float x1 = 0.f;
            float y1 = 0.f;
            bool collision = false;
            int  type = 0;
            int level_type;
            int index;



            //Basic Variables
            //std::cout << gridSize.x << " " << gridSize.y << std::endl;
            in >> std::hex >> size.x >> size.y >> gridsize.x >> gridsize.y >> layers >> index >> level_type >> texture_file;
            //std::cout << gridSize.x << " " << gridSize.y << std::endl;
            std::cout << size.x << size.y << std::endl;

            //Tiles 

            this->grid_sizeF.x = static_cast<float>(gridsize.x);
            this->grid_sizeF.y = static_cast<float>(gridsize.y);
            this->gridsizeI = sf::Vector2i(gridsize.x, gridsize.y);
            this->MaxSizeWorldGrid.x = size.x;
            this->MaxSizeWorldGrid.y = size.y;
            this->MaxSizeWorld_F.x = static_cast<float>(size.x) * gridsize.x;
            this->MaxSizeWorld_F.y = static_cast<float>(size.y) * gridsize.y;
            this->layers = layers;
            this->level_index = index;
            this->level_index = level_type;
            this->texture_file = texture_file;





            this->clear();

            this->Map.resize(this->MaxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());






            for (int x = 0; x < this->MaxSizeWorldGrid.x; x++)
            {

                for (int y = 0; y < this->MaxSizeWorldGrid.y; y++)
                {
                    this->Map[x].resize(this->MaxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

                    for (int z = 0; z < this->layers; z++)
                    {
                        this->Map[x][y].resize(this->layers, std::vector<Tile*>());

                    }   //sf::Vector2f(); 

                }

            }

            if (!this->tileTextureSheet.loadFromFile(texture_file))
            {
                //LOG(WARNING) << "Unable to read data from texture file '" << texture_file << "'";
                //LOG(FATAL) << "Throwing runtime exception on line  858...";

                throw std::runtime_error("ERROR CODE TILEMAP:458 || LOADFROMFILE || Reason: UNABLE_TO_OPEN_FILE");
            }

            while (in >> std::hex >> x >> y >> z >> type)
            {
                //std::cout << "reading the x position... it's " << x << std::endl;
                //std::cout << "reading the y position it's  " << y << std::endl;
                //std::cout << "reading the layer... it's " << z << std::endl;
                //std::cout << "\n";

                if (type == 2)
                {

                    float obX = 0.f;
                    float obY = 0.f;
                    short ObjectType = 0;



                    in >> std::hex >> textureX >> textureY >> ObjectType >> obX >> obY;

                    //  std::cout << "reading the object tile position X: it's  " << obX << "position Y:  " << obY << " " << std::endl;
                     // std::cout << "reading the object tile object type it's " << ObjectType << std::endl;
                     // std::cout << "reading the Object texutre rect X it's  " << textureX << "& " << textureY << "\n";
                    this->Map[x][y][z].push_back(new ObjectTile(obX, obY, this->grid_sizeF, this->object_textures["LANTERN"], sf::IntRect(textureX, textureY, this->gridsizeI.x, this->gridsizeI.y), ObjectType));

                }
                //very important for all of these to be ELSE IF statements, otherwise garbage happens.
                else if (type == TileTypes::SPAWNER)
                {

                    int enemy_type = 0;
                    int enemyAmount = 0;
                    int enemyTimer = 0;
                    int enemyMaxDistance = 0;   

                    in >> std::hex >> textureX >> textureY >> enemy_type >> enemyAmount >> enemyTimer >> enemyMaxDistance;
                    //  std::cout << "reading the spawner tile position X: it's  " << x << "position Y:  " << y << " " << std::endl;
                     /// std::cout << "reading the spawner tile layer, it's  " << z << std::endl;
                    //  std::cout << "reading the spawner tile ememy amount, it's  " << enemyAmount << std::endl;
                     // std::cout << "reading the spawner tile enemy_type, it's  " << enemy_type << std::endl;
                    //  std::cout << "reading the spawner tile enemyTimer, it's  " << enemyTimer << std::endl;
                    //  std::cout << "reading the spawner texutre rect it's  " << textureX << "& " << textureY << "\n";

                    this->Map[x][y][z].push_back(new EnemySpawner(x, y, this->grid_sizeF, this->tileTextureSheet,
                        sf::IntRect(textureX, textureY, this->gridsizeI.x, this->gridsizeI.y), enemy_type,
                        enemyAmount, enemyTimer, enemyMaxDistance));
                }

                //This is the snippet called for most of the tiles usually, all normal tiles will default to this else statement
                else
                {
                    //std::cout << "Texture X: " << textureY << std::endl;
                    //std::cout << "Texture Y" << textureX << std::endl;
                   // std::cout << "reading the layer... it's " << z << std::endl;
                    in >> std::hex >> textureX >> textureY >> collision;
                    //std::cout << "the grid size in normal tiles  " << grid_sizeF.x << " " << grid_sizeF.y << std::endl;
                    //std::cout << "the position for norm tile " << x << " " << y << std::endl; 

                    this->Map[x][y][z].push_back(new NormalTile(TileTypes::NORMAL, x, y, grid_sizeF, this->tileTextureSheet, sf::IntRect(static_cast<int>(textureX), static_cast<int>(textureY), this->gridsizeI.x, this->gridsizeI.y), collision));

                }



            }


            return true;
        }
        else
        {
            std::cout << "ERROR CODE TILEMAP:3 || LOADFROMFILE || COULD NOT LOAD" << std::endl;

            throw std::runtime_error("ERROR CODE TILEMAP:3 || LOADFROMFILE || COULD NOT LOAD");

            return false;
        }

        in.close();
    }
}

void TileMap::addGenerationTexture(const std::string texture_filename)
{ 
    if (!this->tilegenerationSheet.loadFromFile(texture_filename)) 
    {
       // LOG(WARNING) << "unable to load procedural generation tile textures" << std::endl;

    }
}







void TileMap::update(Entity *entity, const float& dt)
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
  
   
    if (x >= 0 && x < static_cast<int>(this->Map.size()))
    {
        if(y >=0 && y < static_cast<int>(this->Map[x].size()))
        {
            if(layer >= 0 && layer < static_cast<int>(this->Map[x][y].size()))
            {
                return static_cast<int>(this->Map[x][y][layer].size());
            }

        }
        
    }
    //Error or Zero tiles
    return -1;
}


void TileMap::DefferedRender(sf::RenderTarget &target, sf::Shader* shader, const sf::Vector2f PlayerPosition)
{
    
   /*!   @brief Renders certian elements of the tilemap behind the main view.
    
        @param  sf::RenderTarget& target   The intended render target.

        @return void    */
    
    while(!this->renderdefered.empty())
    {
        if (shader)
        {
            this->renderdefered.top()->render(target, shader, PlayerPosition);
            this->renderdefered.pop();
        }
        
        
        else {
            this->renderdefered.top()->render(target);
            this->renderdefered.pop(); }
    }
}

const sf::Vector2i &TileMap::getMaxSizeGrid() const
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
    if (!this->Map.empty())
    {
        for (int x = 0; x < this->Map.size(); x++)
        {
            for (int y = 0; y < this->Map[x].size(); y++)
            {
                for (int z = 0; z < this->Map[x][y].size(); z++)
                {
                    for (size_t k = 0; k < this->Map[x][y][z].size(); k++)
                    {
                        ObjectTile* ob = dynamic_cast<ObjectTile*>(this->Map[x][y][this->layer][k]); 
                        if(ob) 
                        {
                            return sf::Vector2f(ob->getGlobalBounds().width / 2.f, ob->getGlobalBounds().height / 2.f);
                        }
                          
                        
                        
                    }
                   
                }
               
            }
           
        }
        

       
    }
}

const sf::Texture* TileMap::getGenerationSheet() const
{
    return &this->tilegenerationSheet; 
}

const std::string TileMap::getLevelType() const
{
    switch (this->level_type) 
    {
    case 0: 
        return "OverWorld"; 
        break;

    case 1: 
        return "Dungeon";
    
    default: 
        return "Default"; 
        break;
    
    }
}

 int TileMap::getLevelIndex() 
{
    return this->level_index; 
}

const bool TileMap::TileEmpty(const int x, const int y, const int z) const
{
    
        if (x >= 0 && x < this->MaxSizeWorldGrid.x &&
            y >= 0 && y < this->MaxSizeWorldGrid.y &&
            z >= 0 && z < this->layers)
        {
            
                return this->Map[x][y][z].empty();
           
        }
    
        else if(x < 0 || y < 0 || z < 0)
        {
            return false;
        }
    
        else if (!x || !y || !z)
        {
            throw std::invalid_argument("Invalid Argument: Tile does not exist");
        }
    
}



const bool TileMap::checktype(const int x, const int y, const int z, const int type) const
{
        
    return this->Map[x][y][this->layer].back()->gettype() == type;
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const int enemytype, const int enemyamount, const int timeToSpawn, const int MaxDistance)
{
    std::cout << x << " " << y << " " << z << std::endl;
    if ( x < this->MaxSizeWorldGrid.x && x >= 0
        && y < this->MaxSizeWorldGrid.y && y >= 0
        && z < this->layers && z >= 0 )
    {
            /*if okay to add ENEMY SPAWNER tile*/

            this->Map[x][y][z].push_back(new EnemySpawner(x, y, this->grid_sizeF, this->tileTextureSheet, texture_rect, enemytype, enemyamount, timeToSpawn, MaxDistance));
    }
        
}

void TileMap::addTile(const int x, const int y, const int z, float obX, float obY, const short type)
{
    std::cout << "Object Tile Function called " << std::endl; 
    if (x < this->MaxSizeWorldGrid.x && x >= 0
        && y < this->MaxSizeWorldGrid.y && y >= 0
        && z < this->layers && z >= 0)
    {
        
        this->Map[x][y][z].push_back(new ObjectTile(obX, obY, this->grid_sizeF, this->object_textures["LANTERN"], sf::IntRect(0, 0, 9, 16), type));
      
    }
}


void TileMap::updateWorldBoundsCollision(Entity *entity, const float &dt)
{
    //World Bounds
    if(entity->getPosition().x < 0.f )
    {
        entity->setPosition(0.f, entity->getPosition().y);
        entity->stopVelocityX(); 
        std::cout << "Hitting Upper world bound" << std::endl; 
    }
    else if (entity->getPosition().x + entity->getGlobalBounds().width > this->MaxSizeWorld_F.x)
    {
        entity->setPosition(this->MaxSizeWorld_F.x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->stopVelocityX(); 
        std::cout << "Hitting Upper left world bound" << std::endl; 
    }
    if (entity->getPosition().y < 0.f)
    {
        entity->setPosition(entity->getPosition().x, 0.f);
        entity->stopVelocityY(); 
        std::cout << "hitting left world bound" << std::endl; 
    }
    else if (entity->getPosition().y + entity->getGlobalBounds().height > this->MaxSizeWorld_F.y)
    {
        entity->setPosition(entity->getPosition().x, this->MaxSizeWorld_F.y - entity->getGlobalBounds().height);
        entity->stopVelocityY(); 
        std::cout << "hitting right world boundary" << std::endl;
    }
    
}

void TileMap::updateTiles(Entity *entity, const float &dt, EnemySystem& enemysystem)
{
    this->layer = 0;
    
    this->FromX = entity->getGridPosition(this->gridsizeI.x).x -2;
    
        if(this->FromX < 0)
            this->FromX = 0;
        else if (this->FromX > this->MaxSizeWorldGrid.x)
            this->FromX = this->MaxSizeWorldGrid.x;
    
    this->ToX = entity->getGridPosition(this->gridsizeI.x).x + 27;
    
        if(this->ToX < 0)
                   this->ToX = 0;
               else if (this->ToX > this->MaxSizeWorldGrid.x)
                   this->ToX = this->MaxSizeWorldGrid.x;
       
    this->FromY = entity->getGridPosition(this->gridsizeI.y).y -27;
    
        if(this->FromY < 0)
                   this->FromY = 0;
               else if (this->FromY > this->MaxSizeWorldGrid.x)
                   this->FromY = this->MaxSizeWorldGrid.x;
       
    this->ToY = entity->getGridPosition(this->gridsizeI.y).y + 27;
    
        if(this->ToY < 0)
                   this->ToY = 0;
               else if (this->ToY > this->MaxSizeWorldGrid.x)
                   this->ToY = this->MaxSizeWorldGrid.x;
       
    
    
    for (int x= this->FromX; x < this->ToX; x++ )
    {
        for (int y= this->FromY; y < this->ToY; y++ )
        {
            for (size_t k=0; k < this->Map[x][y][this->layer].size(); k++)
            { 
               
               this->Map[x][y][this->layer][k]->update(dt);
            
                if (this->Map[x][y][this->layer][k]->gettype() == TileTypes::SPAWNER)
                {
                    EnemySpawner* es = dynamic_cast<EnemySpawner*>(this->Map[x][y][this->layer][k]);
                    if (es)
                    {
                        if(!es->getSpawned() && es->getEnemyCounter() < es->getEnemyAmount())
                        {
                            try
                            {
                            enemysystem.SpawnEnemy(BLRB, x*this->grid_sizeF.x, y*this->grid_sizeF.y, *es);
                            es->SetSpawned(true);
                            }
                            
                            catch(std::invalid_argument& e)
                            {
                                std::cerr << e.what();
                            }
                            
                            
                        

                        }
                    }
                }
               
                
            }
        }
    }
            
    
    
}

void TileMap::updateTileCollision(Entity *entity, const float &dt)
{
    
    //Tile Culling
    //Check for Texturerect angular wall collisons, 
    ///reduce and rediret sprite vel on impact? 
    //if(this->fromX.tan(90) this->GridPosition(this->gridsizeI).x -27; 
          
    
    this->layer = 0;
    
    this->FromX = entity->getGridPosition(this->gridsizeI.x).x -27;
    
        if(this->FromX < 0)
            this->FromX = 0;
        else if (this->FromX > this->MaxSizeWorldGrid.x)
            this->FromX = this->MaxSizeWorldGrid.x;
    
    this->ToX = entity->getGridPosition(this->gridsizeI.x).x + 27;
    
        if(this->ToX < 0)
                   this->ToX = 0;
               else if (this->ToX > this->MaxSizeWorldGrid.x)
                   this->ToX = this->MaxSizeWorldGrid.x;
       
    this->FromY=entity->getGridPosition(this->gridsizeI.y).y -27;
    
        if(this->FromY < 0)
                   this->FromY = 0;
               else if (this->FromY > this->MaxSizeWorldGrid.x)
                   this->FromY = this->MaxSizeWorldGrid.x;
       
    this->ToY = entity->getGridPosition(this->gridsizeI.y).y + 27;
    
        if(this->ToY < 0)
                   this->ToY = 0;
               else if (this->ToY > this->MaxSizeWorldGrid.x)
                   this->ToY = this->MaxSizeWorldGrid.x;
       
    //Fix Collision with Objects 
    //Get Objects to Fucking render finally 
    
    for (int x= this->FromX; x < this->ToX; x++ )
    {
        for (int y= this->FromY; y < this->ToY; y++ )
        {
            for (size_t k=0; k < this->Map[x][y][this->layer].size(); k++)
            {
              
           sf::FloatRect playerBounds = entity->getGlobalBounds();  
           sf::FloatRect wallBounds = sf::FloatRect(); 
           if (this->Map[x][y][this->layer][k])
           {
            wallBounds = this->Map[x][y][this->layer][k]->getGlobalBounds();
           }
           else 
           {
               wallBounds = this->Map[x][y][this->layer][k]->getGlobalBounds();
           }
           
           sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

           if (this->Map[x][y][this->layer][k]->getCollision() &&
               this->Map[x][y][this->layer][k]->intersects(nextPositionBounds)
               )
           {
               //Bottom collision
               if (playerBounds.top < wallBounds.top
                   && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                   && playerBounds.left < wallBounds.left + wallBounds.width
                   && playerBounds.left + playerBounds.width > wallBounds.left
                   )
               {
                   entity->stopVelocityY();
                   entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                   
               }

               //Top collision
               else if (playerBounds.top > wallBounds.top
                   && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                   && playerBounds.left < wallBounds.left + wallBounds.width
                   && playerBounds.left + playerBounds.width > wallBounds.left
                   )
               {
                   entity->stopVelocityY();
                   entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                  
               }

               //Right collision
               if (playerBounds.left < wallBounds.left
                   && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                   && playerBounds.top < wallBounds.top + wallBounds.height
                   && playerBounds.top + playerBounds.height > wallBounds.top
                   )
               {
                   entity->stopVelocityX();
                   entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                   
               }

               //Left collision
               else if (playerBounds.left > wallBounds.left
                   && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                   && playerBounds.top < wallBounds.top + wallBounds.height
                   && playerBounds.top + playerBounds.height > wallBounds.top
                   )
               {
                   entity->stopVelocityX();
                   entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                   
               }
            
                
               }
            }
        }
       
    }

    
}

void TileMap::randomGeneration()
{ 

   
    
        for (int x = 0; x < this->Map.size(); x++)
        {
            for (int y = 0; y < this->Map[x].size(); y++)
            {
                for (int z = 0; z < this->Map[x][y].size(); z++)
                {
                    this->Map[x][y][z].push_back(this->genTile(x, y, z));
                  
                    for (size_t k = 0; k < this->Map[x][y][z].size(); k++)
                    {
                        //replace this call to delete, with a call to a function to randomly generate tile values 
                     
                        
                    }
                    break; 
                  
                }
               
            }
           
        }
      

        //std::cout << "Map Local Memory Size: " << " " << this->Map.size();
    

        return; 


}

Tile* TileMap::genTile(int x, int y, int z)
{
    short type = 5; 
  //  std::cout << "type: " << type << std::endl; 

    int textureX = (rand() % (this->gridsizeI.x * 32)) / 6;
    int textureY = (rand() % (this->gridsizeI.y * 24)) / 6;
   // std::cout << "Texture X: " << textureX << std::endl; 
   // std::cout << "Texture Y: " << textureY << std::endl; 
   
  
    
 

  //  std::cout << this->tileTextureSheet.getMaximumSize() << "max texture size" << std::endl; 
    //find a way to pass the texutre selector text rectangle into this fucntion. 
    //std::cout << TileTypes::NORMAL << std::endl;
    switch (type) 
    {
    case TileTypes::NORMAL:
       // std::cout << "now generating a normal tile" << std::endl;     
        
        return new NormalTile(TileTypes::NORMAL,x, y, this->grid_sizeF, this->tileTextureSheet, sf::IntRect(static_cast<int>(textureX), static_cast<int>(textureY), this->gridsizeI.x, this->gridsizeI.y));
        break; 
    
    } 

    return nullptr; 
}





