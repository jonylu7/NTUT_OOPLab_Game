#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_WarFactory_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_WarFactory_HPP

#include "WayPointStructure.hpp"
class WarFactory : public WayPointStructure {

public:
    WarFactory(float electricPower = -30.F, float buildingTime = 100.F,
               float buildingCost = 2000.F, float buildingHp = 1000.F,
               HouseType house = HouseType::NONE)
        : WayPointStructure(electricPower, buildingTime, buildingCost,
                            buildingHp,
                            GameObjectID(unitType::WAR_FACT, house)){};
    void Start() override;
    void SetObjectLocation(glm::vec2 location) override{
        location = ChangeToCell(location);
        ObjectLocation = location;
        DrawLocation = {location.x + 0.5 * CELL_SIZE.x,
                        location.y + 1 * CELL_SIZE.y};
        m_Transform.translation = DrawLocation;
    }
};

#endif
