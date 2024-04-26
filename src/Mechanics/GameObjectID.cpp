//
// Created by 盧威任 on 3/13/24.
//
#include "Mechanics/GameObjectID.hpp"
std::unordered_map<unitType, unsigned int> OccupiedID::m_OccupiedID = {
    {unitType::NONE, 0},       {unitType::POWER_PLANT, 0},
    {unitType::BARRACKS, 0},   {unitType::ORE_REF, 0},
    {unitType::WAR_FACT, 0},   {unitType::ADV_POWER_PLANT, 0},
    {unitType::SANDBAGS, 0},   {unitType::PILLBOX, 0},
    {unitType::TURRET, 0},     {unitType::INFANTRY, 0},
    {unitType::TRUCK, 0},      {unitType::null, 0},
    {unitType::TILE_BEACH, 0}, {unitType::TILE_BRIDGE, 0},
    {unitType::TILE_CLEAR, 0}, {unitType::TILE_RIVER, 0},
    {unitType::TILE_ROAD, 0},  {unitType::TILE_ROUGH, 0},
    {unitType::TILE_WATER, 0}, {unitType::TILE_ROCK, 0},
    {unitType::TILE_TREE, 0},  {unitType::OVERLAY_GEMS, 0},
    {unitType::OVERLAY_ORE, 0}};

unsigned int OccupiedID::getNewestID(unitType type) {
    return 0;
    if (OccupiedID::m_OccupiedID.count(type) < 0) {
        OccupiedID::m_OccupiedID[type] = unsigned(0);
        return OccupiedID::m_OccupiedID[type];
    } else {
        return OccupiedID::m_OccupiedID[type]++;
    }
}
