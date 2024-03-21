//
// Created by 盧威任 on 3/18/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TERRAINCONFIG_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TERRAINCONFIG_HPP
#include "Tile.hpp"
#include <unordered_map>
class TerrainConfig {
private:
    std::unordered_map<std::string, TileClass> m_config;

public:
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TERRAINCONFIG_HPP
