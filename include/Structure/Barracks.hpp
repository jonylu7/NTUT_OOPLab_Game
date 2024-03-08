#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP

#include "Structure\IWayPointStructure.hpp"
#include "Structure\Structure.hpp"
#include "Util/Image.hpp"
#include "Util/Keycode.hpp"
#include "Util/Input.hpp"
#include "WayPoint.hpp"
#include "HighLight.h"
#include "Line.hpp"
#include "Grid.hpp"

class Barracks : public Structure,public IWayPointStructure{
private:
    std::shared_ptr<WayPoint> m_wayPoint = std::make_shared<WayPoint>();
    HighLight m_HighLight;
    bool b_select= true;
    Grid m_Grid;
    Line m_Line;
    std::vector<Line> m_lineVector;
public:
    Barracks(float electricPower=-20.F,float buildingTime= 15.F,
             float buildingCost=300.F,float buildingHp=800.F):
          Structure(electricPower, buildingTime, buildingCost, buildingHp){};
    void Start()override;

    virtual void onSelected(bool selected)override;
    virtual void SetAttachVisible(bool visible)override;

    virtual void updateFixed()override;
    virtual void updateMoveable()override;
};

#endif
