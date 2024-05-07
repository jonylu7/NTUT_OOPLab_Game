//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
#include "House.hpp"
#include <string>
#include <vector>

enum class UnitType {
    // buildings
    POWER_PLANT,     // 0
    BARRACKS,        // 1
    ORE_REF,         // 2
    WAR_FACT,        // 3
    ADV_POWER_PLANT, // 4

    // defense
    SANDBAGS, // 5
    PILLBOX,  // 6
    TURRET,   // 7
    // Troopers
    INFANTRY, // 8

    // Vehicles
    TRUCK, // 9
    // null
    null, // 10

    // tile
    TILE_BEACH,  // 11
    TILE_BRIDGE, // 12
    TILE_CLEAR,  // 13
    TILE_RIVER,  // 14
    TILE_ROAD,   // 15
    TILE_ROUGH,  // 16
    TILE_WATER,  // 17
    TILE_ROCK,   // 18
    TILE_TREE,   // 19

    // overlays
    OVERLAY_GEMS, // 20
    OVERLAY_ORE,  // 21

    // NONE
    NONE // 22
};

class GameObjectID : public House {
public:
    GameObjectID()
        : m_UnitType(UnitType::NONE) {
        m_Number = 0;
    }
    GameObjectID(UnitType type, HouseType house)
        : m_UnitType(type),
          House(house) {
        m_Number = 0;
    }
    ~GameObjectID() {}

    int getNewestID(UnitType type) { return m_OccupiedID[int(type)]++; }

    int getNumber() const { return m_Number; }
    UnitType getUnitType() const { return m_UnitType; }
    HouseType getHouseType() const {return m_House;}
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
    int m_Number = 0;
    static std::vector<int> m_OccupiedID;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
