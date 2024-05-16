//
// Created by 盧威任 on 3/26/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MOVEABLESTRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MOVEABLESTRUCTURE_HPP
#include "Display/Grid.hpp"
#include "Display/Line.hpp"
#include "HighLight.h"
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
    WayPointStructure(
        float electricPower = -10.F, float buildingTime = 10.F,
        float buildingCost = 20.F, float buildingHp = 90.F,
        GameObjectID id = GameObjectID(UnitType::null, HouseType::NONE),
        std::shared_ptr<Health> health = std::make_shared<Health>())
        : Structure(electricPower, buildingTime, buildingCost, buildingHp, id,
                    health) {
        m_Transform.scale = {2.f, 2.f};
    };
    virtual ~WayPointStructure(){};

    virtual void whenSelected() override;
    virtual void SetAttachVisible(bool visible) override;
    virtual void attachmentUpdate() override;

    void Update() override {

        switch (*Structure::getHealth()->getLivingStatus()) {
        case LivingStatus::NOT_BORN_YET: {
            this->updateInvinsible();
            break;
        }
        case LivingStatus::ALIVE: {
            if (m_StructOrder == StructureOrderType::SELECTING_SITE) {
                this->updateMoveable();
            } else {
                this->updateFixed();
                whenSelected();
            }
            break;
        }
        }
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MOVEABLESTRUCTURE_HPP
