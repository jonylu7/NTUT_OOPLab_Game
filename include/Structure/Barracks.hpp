#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP

#include "WayPointStructure.hpp"

class Barracks : public WayPointStructure {
public:
    Barracks(float electricPower = -20.F, float buildingTime = 1.F,
             float buildingCost = 300.F, float buildingHp = 800.F,
             HouseType house = HouseType::NONE)

        : WayPointStructure(electricPower, buildingTime, buildingCost,
                            buildingHp,
                            GameObjectID(unitType::BARRACKS, house)){};
    void Start() override;
};
#endif
