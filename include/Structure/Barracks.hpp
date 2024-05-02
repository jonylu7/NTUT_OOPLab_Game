#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP
#include "Map/MapUtility.hpp"
#include "WayPointStructure.hpp"

class Barracks : public WayPointStructure {
public:
    Barracks(float electricPower = -20.F, float buildingTime = 15.F * CHEAT,
             float buildingCost = 300.F, float buildingHp = 800.F,
             HouseType house = HouseType::NONE)

        : WayPointStructure(electricPower, buildingTime, buildingCost,
                            buildingHp,
                            GameObjectID(UnitType::BARRACKS, house)){};
    void Start() override;
    void SetObjectLocation(glm::vec2 location) override {
        location = MapUtil::PositionStickToGrid(location);
        m_ObjectLocation = location;
        m_DrawLocation = {location.x + 1 * CELL_SIZE.x,
                          location.y + 1 * CELL_SIZE.y};
        m_Transform.translation = m_DrawLocation;
    }
};
#endif
