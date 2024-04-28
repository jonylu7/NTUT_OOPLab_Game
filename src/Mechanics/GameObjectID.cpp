//
// Created by 盧威任 on 3/13/24.
//
#include "Mechanics/GameObjectID.hpp"

std::unordered_map<int, unsigned int> OccupiedID::m_OccupiedID = {
    {int(unitType::NONE), 0},       {int(unitType::POWER_PLANT), 0},
    {int(unitType::BARRACKS), 0},   {int(unitType::ORE_REF), 0},
    {int(unitType::WAR_FACT), 0},   {int(unitType::ADV_POWER_PLANT), 0},
    {int(unitType::SANDBAGS), 0},   {int(unitType::PILLBOX), 0},
    {int(unitType::TURRET), 0},     {int(unitType::INFANTRY), 0},
    {int(unitType::TRUCK), 0},      {int(unitType::null), 0},
    {int(unitType::TILE_BEACH), 0}, {int(unitType::TILE_BRIDGE), 0},
    {int(unitType::TILE_CLEAR), 0}, {int(unitType::TILE_RIVER), 0},
    {int(unitType::TILE_ROAD), 0},  {int(unitType::TILE_ROUGH), 0},
    {int(unitType::TILE_WATER), 0}, {int(unitType::TILE_ROCK), 0},
    {int(unitType::TILE_TREE), 0},  {int(unitType::OVERLAY_GEMS), 0},
    {int(unitType::OVERLAY_ORE), 0}};

unsigned int OccupiedID::getNewestID(unitType type) {
    return 0;
    // 先copy進去
    return OccupiedID::m_OccupiedID[int(type)]++;
}
