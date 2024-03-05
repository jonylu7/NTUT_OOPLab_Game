#include "Structure.hpp"

#define DEFAULT_POWER 100.F
#define DEFAULT_TIME 100.F
#define DEFAULT_COST 100.F
#define DEFAULT_HP 1000.F

class Building:public Structure{
public:
    Building(float electricPower=DEFAULT_POWER,float buildingTime=DEFAULT_TIME,
             float buildingCost=DEFAULT_COST,float buildingHp=DEFAULT_HP): Structure(electricPower, buildingTime, buildingCost, buildingHp){};
};