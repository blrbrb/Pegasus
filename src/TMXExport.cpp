#include "include/TMXExport.hpp"
#include <sstream>

TMXExport::TMXExport(unsigned int mapWidth, unsigned int mapHeight, unsigned int tileWidth, unsigned int tileHeight)
    : m_mapWidth(mapWidth)
    , m_mapHeight(mapHeight)
    , m_tileWidth(tileWidth)
    , m_tileHeight(tileHeight)
{
}

void TMXExport::setTileset(const std::string& name, const std::string& source, unsigned int firstGid, unsigned int tileCount, unsigned int columns)
{
    this->m_tileset = { name, source, firstGid, tileCount, columns };
}

void TMXExport::addLayer(const std::string& name, const std::vector<int>& tileData)
{
    m_layers.push_back({ name, tileData });
}

bool TMXExport::saveToFile(const std::string& filename) const
{
    tinyxml2::XMLDocument doc;

    // Add standard XML declaration
    tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertFirstChild(decl);

    // Create root <map> element
    tinyxml2::XMLElement* mapNode = doc.NewElement("map");
    mapNode->SetAttribute("version", "1.10");
    mapNode->SetAttribute("tiledversion", "1.10.2");
    mapNode->SetAttribute("orientation", "orthogonal");
    mapNode->SetAttribute("renderorder", "right-down");
    mapNode->SetAttribute("width", m_mapWidth);
    mapNode->SetAttribute("height", m_mapHeight);
    mapNode->SetAttribute("tilewidth", m_tileWidth);
    mapNode->SetAttribute("tileheight", m_tileHeight);
    mapNode->SetAttribute("infinite", 0);
    mapNode->SetAttribute("nextlayerid", static_cast<int>(m_layers.size() + 1));
    mapNode->SetAttribute("nextobjectid", 1);
    doc.InsertEndChild(mapNode);

    // Create <tileset> element if valid
    if (!m_tileset.source.empty()) {
        tinyxml2::XMLElement* tilesetNode = doc.NewElement("tileset");
        tilesetNode->SetAttribute("firstgid", m_tileset.firstGid);
        tilesetNode->SetAttribute("name", m_tileset.name.c_str());
        tilesetNode->SetAttribute("tilewidth", m_tileWidth);
        tilesetNode->SetAttribute("tileheight", m_tileHeight);
        tilesetNode->SetAttribute("tilecount", m_tileset.tileCount);
        tilesetNode->SetAttribute("columns", m_tileset.columns);

        // Create inner <image> element
        tinyxml2::XMLElement* imageNode = doc.NewElement("image");
        imageNode->SetAttribute("source", m_tileset.source.c_str());
        imageNode->SetAttribute("width", m_tileset.columns * m_tileWidth);
        imageNode->SetAttribute("height", (m_tileset.tileCount / m_tileset.columns) * m_tileHeight);

        tilesetNode->InsertEndChild(imageNode);
        mapNode->InsertEndChild(tilesetNode);
    }

    // Process and add <layer> elements
    for (size_t i = 0; i < m_layers.size(); ++i) {
        const auto& layer = m_layers[i];

        tinyxml2::XMLElement* layerNode = doc.NewElement("layer");
        layerNode->SetAttribute("id", static_cast<int>(i + 1));
        layerNode->SetAttribute("name", layer.name.c_str());
        layerNode->SetAttribute("width", m_mapWidth);
        layerNode->SetAttribute("height", m_mapHeight);

        tinyxml2::XMLElement* dataNode = doc.NewElement("data");
        dataNode->SetAttribute("encoding", "csv");

        // Format map array data block to highly readable CSV text
        std::stringstream csvData;
        csvData << "\n"; // Clean line breaks matching native Tiled exports
        for (size_t t = 0; t < layer.data.size(); ++t) {
            csvData << layer.data[t];
            if (t < layer.data.size() - 1) {
                csvData << ",";
                if ((t + 1) % m_mapWidth == 0) {
                    csvData << "\n";
                }
            }
        }
        csvData << "\n";

        tinyxml2::XMLText* textData = doc.NewText(csvData.str().c_str());
        dataNode->InsertEndChild(textData);
        layerNode->InsertEndChild(dataNode);
        mapNode->InsertEndChild(layerNode);
    }

    // Save out via TinyXML-2's file writer
    return (doc.SaveFile(filename.c_str()) == tinyxml2::XML_SUCCESS);
}
