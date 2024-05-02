//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
#include "House.hpp"
#include <string>
#include <unordered_map>

enum class UnitType {
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
    static std::unordered_map<int, unsigned int> m_OccupiedID;

public:
    static unsigned int getNewestID(UnitType type);
};

class GameObjectID : public House {
public:
    GameObjectID()
        : m_UnitType(UnitType::null),
          m_Number(0) {}
    GameObjectID(UnitType type, HouseType house)
        : m_UnitType(type),
          m_Number(OccupiedID::getNewestID(type)),
          House(house) {}
    ~GameObjectID() {}

    int getNumber() const { return m_Number; }
    UnitType getUnitType() const { return m_UnitType; }

    bool operator==(const GameObjectID &id) const {
        if (this->m_UnitType == id.m_UnitType &&
            this->m_Number == id.m_Number && this->m_House == id.m_House) {
            return true;
        } else {
            return false;
        }
    };

    GameObjectID &operator=(const GameObjectID &id) {
        this->m_Number = id.m_Number;
        this->m_UnitType = id.m_UnitType;
        this->m_House = id.m_House;
        return *this;
    }

private:
    UnitType m_UnitType;
    unsigned int m_Number;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
