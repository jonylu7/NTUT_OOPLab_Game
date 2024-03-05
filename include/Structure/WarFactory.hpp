#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_WarFactory_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_WarFactory_HPP

#include "IWayPointStructure.hpp"
#include "Structure.hpp"
#define DEFAULT_POWER -30.F
#define DEFAULT_TIME 100.F
#define DEFAULT_COST 2000.F
#define DEFAULT_HP 1000.F

class WarFactory : public Structure,public IWayPointStructure{
public:
    WarFactory(float electricPower=DEFAULT_POWER,float buildingTime=DEFAULT_POWER,
               float buildingCost=DEFAULT_POWER,float buildingHp=DEFAULT_POWER): Structure(electricPower, buildingTime, buildingCost, buildingHp){};
    virtual glm::vec2 GetStructureLocation()override{return this->GetObjectLocation();};
    void Start() override{this->SetWayPointLocation({this->GetObjectLocation().x+20,this->GetObjectLocation().y+20});};
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CAPYBARA_HPP
