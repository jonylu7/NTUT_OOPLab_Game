//
// Created by 盧威任 on 3/18/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TERRAINCONFIG_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TERRAINCONFIG_HPP
#include "Tile.hpp"
#include <unordered_map>
class TerrainConfig {
private:
    static std::unordered_map<std::string, std::shared_ptr<TileClass>> m_config;

public:
    static std::shared_ptr<TileClass> GetConfig(std::string tilename) {
        return TerrainConfig::m_config[tilename];
    };
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TERRAINCONFIG_HPP
