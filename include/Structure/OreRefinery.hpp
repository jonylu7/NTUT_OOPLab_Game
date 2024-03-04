#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_OreRefinery_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_OreRefinery_HPP

#include "IWayPointStructure.hpp"
#include "Structure.hpp"
#define DEFAULT_POWER -30.F
#define DEFAULT_TIME 100.F
#define DEFAULT_COST 2000.F
#define DEFAULT_HP 900.F

class OreRefinery:public Structure,public IWayPointStructure{
public:
    OreRefinery(float electricPower=DEFAULT_POWER,float buildingTime=DEFAULT_TIME,
             float buildingCost=DEFAULT_COST,float buildingHp=DEFAULT_HP): Structure(electricPower, buildingTime, buildingCost, buildingHp){};
    virtual glm::vec2 GetStructureLocation()override{return this->GetObjectLocation();};
    void Start() override{this->SetWayPointLocation({this->GetObjectLocation().x+20,this->GetObjectLocation().y+20});};
};
#endif
