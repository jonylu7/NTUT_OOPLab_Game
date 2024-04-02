//
// Created by 盧威任 on 3/17/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP
#include "TerrainConfig.hpp"
#include "Tile.hpp"
#include "Util/Image.hpp"
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>
class YAMLReader {
public:
    static std::string convertYAMLTileToImagePath(int id, int index);

    static std::shared_ptr<TileClass> convertYAMLTileToTileClass(int id,
                                                                 int index);

private:
    static std::shared_ptr<YAML::Node> m_mapTile;
    TerrainConfig config;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP
