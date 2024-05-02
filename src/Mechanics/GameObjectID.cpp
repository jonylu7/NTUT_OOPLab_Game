//
// Created by 盧威任 on 3/13/24.
//
#include "Mechanics/GameObjectID.hpp"

std::unordered_map<int, unsigned int> OccupiedID::m_OccupiedID = {
    {int(UnitType::NONE), 0},       {int(UnitType::POWER_PLANT), 0},
    {int(UnitType::BARRACKS), 0},   {int(UnitType::ORE_REF), 0},
    {int(UnitType::WAR_FACT), 0},   {int(UnitType::ADV_POWER_PLANT), 0},
    {int(UnitType::SANDBAGS), 0},   {int(UnitType::PILLBOX), 0},
    {int(UnitType::TURRET), 0},     {int(UnitType::INFANTRY), 0},
    {int(UnitType::TRUCK), 0},      {int(UnitType::null), 0},
    {int(UnitType::TILE_BEACH), 0}, {int(UnitType::TILE_BRIDGE), 0},
    {int(UnitType::TILE_CLEAR), 0}, {int(UnitType::TILE_RIVER), 0},
    {int(UnitType::TILE_ROAD), 0},  {int(UnitType::TILE_ROUGH), 0},
    {int(UnitType::TILE_WATER), 0}, {int(UnitType::TILE_ROCK), 0},
    {int(UnitType::TILE_TREE), 0},  {int(UnitType::OVERLAY_GEMS), 0},
    {int(UnitType::OVERLAY_ORE), 0}};

unsigned int OccupiedID::getNewestID(UnitType type) {
    return 0;
    // 先copy進去
    return OccupiedID::m_OccupiedID[int(type)]++;
}
