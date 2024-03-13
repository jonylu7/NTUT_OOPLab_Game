#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP

#include "Grid.hpp"
#include "HighLight.h"
#include "Line.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Structure/MousOverlapTool.h"
#include "Structure/Structure.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "WayPoint.hpp"

class Barracks : public Structure, public IWayPointStructure {
private:
    std::shared_ptr<WayPoint> m_wayPoint = std::make_shared<WayPoint>();
    HighLight m_HighLight;
    Grid m_Grid;
    Line m_Line;
    std::vector<Line> m_lineVector;

public:
    Barracks(float electricPower = -20.F, float buildingTime = 15.F,
             float buildingCost = 300.F, float buildingHp = 800.F)
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    unitType::BARRACKS){};
    void Start() override;

    virtual void onSelected(bool selected) override;
    virtual void SetAttachVisible(bool visible) override;

    virtual void updateMoveable() override;
    virtual void attachmentUpdate() override;
};

#endif
