#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_OreRefinery_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_OreRefinery_HPP
#include "WayPointStructure.hpp"
class OreRefinery : public WayPointStructure {
public:
    OreRefinery(float electricPower = -30.F, float buildingTime = 100.F*CHEAT,
                float buildingCost = 2000.F, float buildingHp = 900.F,
                HouseType house = HouseType::NONE)
        : WayPointStructure(electricPower, buildingTime, buildingCost,
                            buildingHp,
                            GameObjectID(unitType::ORE_REF, house)){};
    void Start() override;
    void SetObjectLocation(glm::vec2 location) override{
        location = PositionStickToGrid(location);
        ObjectLocation = location;
        DrawLocation = {location.x  +1.5* CELL_SIZE.x,
                        location.y +1.5 * CELL_SIZE.y};
        m_Transform.translation = DrawLocation;
    }
};
#endif
