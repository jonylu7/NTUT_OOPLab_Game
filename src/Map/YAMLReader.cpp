//
// Created by 盧威任 on 3/18/24.
//
#include "Map/YAMLReader.hpp"

void YAMLReader::Init(const std::string mapfilepath) {
    YAMLReader::m_mapTileFilePath = mapfilepath;
    // Parse the YAML file
    YAMLReader::m_mapTile =
        std::make_shared<YAML::Node>(YAML::LoadFile(mapfilepath));

    if (YAMLReader::m_mapTile->IsNull()) {
        LOG_DEBUG("Error reading YAML file!");
    }
}

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

std::string YAMLReader::m_mapTileFilePath;
// Definition of static member
// variable
std::shared_ptr<YAML::Node> YAMLReader::m_mapTile =
    std::make_shared<YAML::Node>(YAML::LoadFile("../assets/map/temperat.yaml"));
