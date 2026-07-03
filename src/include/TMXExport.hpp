#ifndef TMXExport_hpp
#define TMXExport_hpp
#include "tinyxml2.h"

#include <string>
#include <vector>

class TMXExport {
public:
    TMXExport(unsigned int mapWidth, unsigned int mapHeight, unsigned int tileWidth, unsigned int tileHeight);

    void setTileset(const std::string& name, const std::string& source, unsigned int firstGid, unsigned int tileCount, unsigned int columns);
    void addLayer(const std::string& name, const std::vector<int>& tileData);
    bool saveToFile(const std::string& filename) const;

private:
    unsigned int m_mapWidth;
    unsigned int m_mapHeight;
    unsigned int m_tileWidth;
    unsigned int m_tileHeight;

    struct Tileset {
        std::string name;
        std::string source;
        unsigned int firstGid = 1;
        unsigned int tileCount = 0;
        unsigned int columns = 0;

    } m_tileset;

    struct Layer {
        std::string name;
        std::vector<int> data;
    };
    std::vector<Layer> m_layers;
};
#endif
