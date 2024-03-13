//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
#include <string>
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
    null
};

class OccupiedID {
private:
    static std::unordered_map<unitType, unsigned int> m_OccupiedID;

public:
    static int getNewestID(unitType type);
    static void removeID(unitType type, int id){};
    static void InitID();
};

class GameObjectID {
public:
    GameObjectID()
        : m_unitType(unitType::null),
          number(0) {}
    GameObjectID(unitType type)
        : m_unitType(type),
          number(OccupiedID::getNewestID(type)) {}
    ~GameObjectID() {}

    void generateID(unitType type) { m_unitType = type; }
    int getNumber() { return number; }
    unitType getUnitType() { return m_unitType; }

    bool operator==(const GameObjectID &id) const {
        if (this->m_unitType == id.m_unitType && this->number == id.number) {
            return true;
        } else {
            return false;
        }
    };

    GameObjectID &operator=(const GameObjectID &id) {
        this->number = id.number;
        this->m_unitType = id.m_unitType;
        return *this;
    }

private:
    unitType m_unitType;
    unsigned int number;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTID_HPP
