#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP

#include "Structure/IWayPointStructure.hpp"
#include "Structure.hpp"
#define DEFAULT_POWER -20.F
#define DEFAULT_TIME 15.F
#define DEFAULT_COST 300.F
#define DEFAULT_HP 800.F

class Barracks : public Structure,public IWayPointStructure{
public:
    Barracks(float electricPower=DEFAULT_POWER,float buildingTime=DEFAULT_POWER,
             float buildingCost=DEFAULT_POWER,float buildingHp=DEFAULT_POWER): Structure(electricPower, buildingTime, buildingCost, buildingHp){};
    virtual glm::vec2 GetStructureLocation()override{return this->GetObjectLocation();};
    void Start() override{this->SetWayPointLocation({this->GetObjectLocation().x+20,this->GetObjectLocation().y+20});};
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CAPYBARA_HPP
