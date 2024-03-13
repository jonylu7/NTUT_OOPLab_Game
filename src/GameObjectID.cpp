//
// Created by 盧威任 on 3/13/24.
//
#include "GameObjectID.hpp"
std::unordered_map<unitType, unsigned int> OccupiedID::m_OccupiedID;
void OccupiedID::InitID() {
    OccupiedID::m_OccupiedID[unitType::INFANTRY] = 0;
    OccupiedID::m_OccupiedID[unitType::POWER_PLANT] = 0;
    OccupiedID::m_OccupiedID[unitType::BARRACKS] = 0;
    OccupiedID::m_OccupiedID[unitType::ORE_REF] = 0;
    OccupiedID::m_OccupiedID[unitType::WAR_FACT] = 0;
    OccupiedID::m_OccupiedID[unitType::ADV_POWER_PLANT] = 0;

    // defense
    OccupiedID::m_OccupiedID[unitType::SANDBAGS] = 0;
    OccupiedID::m_OccupiedID[unitType::PILLBOX] = 0;
    OccupiedID::m_OccupiedID[unitType::TURRET] = 0;
    // Troopers
    OccupiedID::m_OccupiedID[unitType::INFANTRY] = 0;

    // Vehicles
    OccupiedID::m_OccupiedID[unitType::TRUCK] = 0;
}

int OccupiedID::getNewestID(unitType type) {
    OccupiedID::m_OccupiedID[type] += 1;
    return OccupiedID::m_OccupiedID[type];
}
