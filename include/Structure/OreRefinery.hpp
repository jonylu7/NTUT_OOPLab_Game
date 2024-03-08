#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_OreRefinery_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_OreRefinery_HPP

#include "Structure\IWayPointStructure.hpp"
#include "Structure\Structure.hpp"
#include "Util/Image.hpp"
#include "Util/Keycode.hpp"
#include "Util/Input.hpp"
#include "WayPoint.hpp"
#include "HighLight.h"
#include "Line.hpp"
#include "Grid.hpp"

class OreRefinery:public Structure,public IWayPointStructure{
private:
    std::shared_ptr<WayPoint> m_wayPoint = std::make_shared<WayPoint>();
    HighLight m_HighLight;
    bool b_select= true;
    Grid m_Grid;
    Line m_Line;
    std::vector<Line> m_lineVector;
public:
    OreRefinery(float electricPower=-30.F,float buildingTime=100.F,
             float buildingCost=2000.F,float buildingHp=900.F):
          Structure(electricPower, buildingTime, buildingCost, buildingHp){};
    void Start() override;

    virtual void onSelected(bool selected)override;
    virtual void SetAttachVisible(bool visible)override;

    virtual void updateFixed()override;
    virtual void updateMoveable()override;
};
#endif
