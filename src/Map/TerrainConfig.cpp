//
// Created by 盧威任 on 3/18/24.
//
#include "Map/TerrainConfig.hpp"
std::unordered_map<std::string, std::shared_ptr<TileClass>>
    TerrainConfig::m_config = {
        {"Beach", std::make_shared<TileClass>(UnitType::TILE_BEACH, 0, 1, 1)},
        {"Bridge", std::make_shared<TileClass>(UnitType::TILE_BRIDGE, 0, 1, 1)},
        {"Clear", std::make_shared<TileClass>(UnitType::TILE_CLEAR, 1, 1, 1)},
        {"Gems", std::make_shared<TileClass>(UnitType::OVERLAY_GEMS, 0, 1, 1)},
        {"Ore", std::make_shared<TileClass>(UnitType::OVERLAY_ORE, 0, 1, 1)},
        {"River", std::make_shared<TileClass>(UnitType::TILE_RIVER, 0, 0, 0)},
        {"Road", std::make_shared<TileClass>(UnitType::TILE_ROAD, 1, 1, 1)},
        {"Rock", std::make_shared<TileClass>(UnitType::TILE_ROCK, 0, 1, 1)},
        {"Rough", std::make_shared<TileClass>(UnitType::TILE_ROUGH, 0, 1, 1)},
        {"Tree", std::make_shared<TileClass>(UnitType::TILE_TREE, 0, 0, 1)},
        {"Water", std::make_shared<TileClass>(UnitType::TILE_WATER, 0, 0, 0)}};
