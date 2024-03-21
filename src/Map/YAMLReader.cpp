//
// Created by 盧威任 on 3/18/24.
//
#include "Map/YAMLReader.hpp"
#include "Map/Tile.hpp"

std::shared_ptr<Util::Image> YAMLReader::convertYAMLTileToImage(int id,
                                                                int index) {
    std::string str = std::to_string(index); // Example string
    // Create an output string stream
    std::ostringstream oss;

    // Set the fill character to '0'
    oss << std::setfill('0');

    // Set the width to the desired length
    oss << std::setw(4);

    oss << str;

    // Get the formatted string
    std::string formattedStr = oss.str();

    auto tileSet =
        (*YAMLReader::m_mapTile)["Templates"]["Template@" + std::to_string(id)];

    std::string imageFileName = Dump(tileSet["Images"]);

    std::string convertedImageFileName =
        imageFileName.substr(0, imageFileName.size() - 4) + "-" + formattedStr +
        ".png";

    return std::make_shared<Util::Image>("../assets/sprites/temperate_sprite/" +
                                         convertedImageFileName);
}

std::shared_ptr<TileClass> YAMLReader::convertYAMLTileToTileClass(int id,
                                                                  int index) {

    auto tileSet =
        (*YAMLReader::m_mapTile)["Templates"]["Template@" + std::to_string(id)];

    std::string imageFileName = Dump(tileSet["Images"]);
    std::string terrainName = Dump(tileSet["Tiles"][std::to_string(index)]);

    std::shared_ptr<Util::Image> image = convertYAMLTileToImage(id, index);
    std::shared_ptr<TileClass> tile =
        std::move(TerrainConfig::GetConfig(terrainName));
    tile->setTileImage(image);

    return tile;
}

// variable
std::shared_ptr<YAML::Node> YAMLReader::m_mapTile =
    std::make_shared<YAML::Node>(YAML::LoadFile(PATH_TO_TEMPERAT_TILESET_YAML));
