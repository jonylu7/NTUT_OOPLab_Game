//
// Created by 盧威任 on 3/13/24.
//
#include "GameObjectID.hpp"
std::unordered_map<unitType, unsigned int> OccupiedID::m_OccupiedID;

int OccupiedID::getNewestID(unitType type) {
    return 0;
    auto it = OccupiedID::m_OccupiedID.find(type);
    if (it != OccupiedID::m_OccupiedID.end()) {
        return OccupiedID::m_OccupiedID[type]++;
    } else {
        OccupiedID::m_OccupiedID[type] = 0;
    }
}
