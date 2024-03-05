#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP


#include "Structure.hpp"
#define DEFAULT_POWER 100.F
#define DEFAULT_TIME 15.F
#define DEFAULT_COST 300.F
#define DEFAULT_HP 400.F

class PowerPlants:public Structure{
public:
    PowerPlants(float electricPower=DEFAULT_POWER,float buildingTime=DEFAULT_TIME,
                float buildingCost=DEFAULT_COST,float buildingHp=DEFAULT_HP): Structure(electricPower, buildingTime, buildingCost, buildingHp){};
};

#endif
