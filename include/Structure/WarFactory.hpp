#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_WarFactory_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_WarFactory_HPP

#include "Grid.hpp"
#include "HighLight.h"
#include "Line.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Structure/Structure.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "WayPoint.hpp"

class WarFactory : public Structure, public IWayPointStructure {
public:
    WarFactory(float electricPower = -30.F, float buildingTime = 100.F,
               float buildingCost = 2000.F, float buildingHp = 1000.F)
        : Structure(electricPower, buildingTime, buildingCost, buildingHp){};
    void Start() override;

    virtual void onSelected(bool selected) override;
    virtual void SetAttachVisible(bool visible) override;

    virtual void updateFixed() override;
    virtual void updateMoveable() override;

private:
    std::shared_ptr<WayPoint> m_wayPoint = std::make_shared<WayPoint>();
    HighLight m_HighLight;
    bool b_select = true;
    Grid m_Grid;
    Line m_Line;
    std::vector<Line> m_lineVector;
};

#endif
