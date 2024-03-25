#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_ADVPowerPlants_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_ADVPowerPlants_HPP
#include "House.hpp"
#include "Structure.hpp"
class ADVPowerPlants : public Structure {
public:
    ADVPowerPlants(float electricPower = 200.F, float buildingTime = 25.F,
                   float buildingCost = 500.F, float buildingHp = 700.F,
                   HouseType house = HouseType::NONE)
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    GameObjectID(unitType::ADV_POWER_PLANT, house)) {
        SetDrawable(
            std::make_unique<Util::Image>("../assets/sprites/PowerPlants.png"));
    };
};

#endif
