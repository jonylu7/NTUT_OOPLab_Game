#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP

#include "Structure.hpp"
class PowerPlants : public Structure {
public:
    PowerPlants(float electricPower = 100.F, float buildingTime = 15.F,
                float buildingCost = 300.F, float buildingHp = 400.F)
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    unitType::POWER_PLANT) {
        SetDrawable(
            std::make_unique<Util::Image>("../assets/sprites/PowerPlants.png"));
    };
};

#endif
