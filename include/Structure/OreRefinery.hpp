#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_OreRefinery_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_OreRefinery_HPP
#include "Map/MapUtility.hpp"
#include "WayPointStructure.hpp"
class OreRefinery : public WayPointStructure {
public:
    OreRefinery(float electricPower = -30.F, float buildingTime = 100.F * CHEAT,
                float buildingCost = 2000.F, float buildingHp = 900.F,
                HouseType house = HouseType::MY)
        : WayPointStructure(electricPower, buildingTime, buildingCost,
                            buildingHp,
                            GameObjectID(UnitType::ORE_REF, house)){};
    OreRefinery(HouseType house)
        : WayPointStructure(-30.F, 100.F * CHEAT, 2000.F,900.F,
                            GameObjectID(UnitType::ORE_REF, house)){};
    void Start() override;
    void Start(glm::vec2 location)  override;
    void SetObjectLocation(glm::vec2 location) override {
        location = MapUtil::PositionStickToGrid(location);
        m_ObjectLocation = location;
        m_DrawLocation = {location.x + 1.5 * CELL_SIZE.x,
                          location.y + 1.5 * CELL_SIZE.y};
        m_Transform.translation = m_DrawLocation;
    }
};
#endif
