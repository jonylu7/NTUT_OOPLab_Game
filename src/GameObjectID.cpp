//
// Created by 盧威任 on 3/13/24.
//
#include "GameObjectID.hpp"

std::unordered_map<unitType, int> m_OccupiedID;

void OccupiedID::InitID() {
    m_OccupiedID[unitType::INFANTRY] = 0;
    m_OccupiedID[unitType::INFANTRY] = 0;
}

int OccupiedID::getNewestID(unitType type) {
    m_OccupiedID[type] += 1;
    return m_OccupiedID[type];
}
