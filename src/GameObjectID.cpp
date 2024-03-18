//
// Created by 盧威任 on 3/13/24.
//
#include "GameObjectID.hpp"
std::unordered_map<unitType, unsigned int> OccupiedID::m_OccupiedID;

void OccupiedID::InitID() {}

int OccupiedID::getNewestID(unitType type) {
    auto it = OccupiedID::m_OccupiedID.find(type);
    if (it != OccupiedID::m_OccupiedID.end()) {
        return OccupiedID::m_OccupiedID[type]++;
    } else {
        OccupiedID::m_OccupiedID[type] = 0;
    }
}
