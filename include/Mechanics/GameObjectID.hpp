//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
#include "House.hpp"
#include <string>
#include <unordered_map>

enum class unitType {
    // buildings
    POWER_PLANT,
    BARRACKS,
    ORE_REF,
    WAR_FACT,
    ADV_POWER_PLANT,

    // defense
    SANDBAGS,
    PILLBOX,
    TURRET,
    // Troopers
    INFANTRY,

    // Vehicles
    TRUCK,
    // null
    null,

    // tile
    TILE_BEACH,
    TILE_BRIDGE,
    TILE_CLEAR,
    TILE_RIVER,
    TILE_ROAD,
    TILE_ROUGH,
    TILE_WATER,
    TILE_ROCK,
    TILE_TREE,

    // overlays
    OVERLAY_GEMS,
    OVERLAY_ORE,

    // NONE
    NONE
};

class OccupiedID {
private:
    static std::unordered_map<unitType, unsigned int> m_OccupiedID;

public:
    static unsigned int getNewestID(unitType type);
};

class GameObjectID {
public:
    GameObjectID()
        : m_unitType(unitType::null),
          m_number(0) {}
    GameObjectID(unitType type, HouseType house)
        : m_unitType(type),
          m_number(OccupiedID::getNewestID(type)),
          m_house(house) {}
    ~GameObjectID() {}

    int getNumber() const { return m_number; }
    unitType getUnitType() const { return m_unitType; }

    bool operator==(const GameObjectID &id) const {
        if (this->m_unitType == id.m_unitType &&
            this->m_number == id.m_number && this->m_house == id.m_house) {
            return true;
        } else {
            return false;
        }
    };

    GameObjectID &operator=(const GameObjectID &id) {
        this->m_number = id.m_number;
        this->m_unitType = id.m_unitType;
        this->m_house = id.m_house;
        return *this;
    }

private:
    unitType m_unitType;
    unsigned int m_number;
    HouseType m_house;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
