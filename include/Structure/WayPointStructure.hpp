//
// Created by 盧威任 on 3/26/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MOVEABLESTRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MOVEABLESTRUCTURE_HPP
#include "Grid.hpp"
#include "HighLight.h"
#include "Line.hpp"
#include "Map/MapUtility.hpp"
#include "Structure/IWayPoint.hpp"
#include "Structure/Structure.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "WayPoint.hpp"

class WayPointStructure : public Structure, public IWayPointStructure {
protected:
    std::shared_ptr<WayPoint> m_wayPoint = std::make_shared<WayPoint>();
    HighLight m_HighLight;
    Grid m_Grid;
    Line m_Line;
    std::vector<Line> m_lineVector;

public:
    WayPointStructure(float electricPower = -10.F, float buildingTime = 10.F,
                      float buildingCost = 20.F, float buildingHp = 90.F,
                      GameObjectID id = GameObjectID(unitType::null,
                                                     HouseType::NONE))
        : Structure(electricPower, buildingTime, buildingCost, buildingHp, id) {
        m_Transform.scale = {2.f, 2.f};
    };
    virtual ~WayPointStructure(){};

    virtual void whenSelected() override;
    virtual void SetAttachVisible(bool visible) override;
    virtual void attachmentUpdate() override;

    void Update() override {

        switch (m_CurrentState) {
        case updateMode::Invisidable: {
            this->updateInvinsible();
            break;
        }
        case updateMode::Fixed: {
            this->updateFixed();
            whenSelected();
            break;
        }
        case updateMode::Moveable: {
            this->updateMoveable();
            break;
        }
        }
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MOVEABLESTRUCTURE_HPP
