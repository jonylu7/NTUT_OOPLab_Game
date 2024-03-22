//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "Unit/PathfindingUnit.hpp"
#include "Unit/WayPointUnit.hpp"

class Dummy:public PathfindingUnit{
private:
    WayPointUnit m_wayPointUnit;
    long count=0;
public:
    virtual void Start()override{
        this->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
        m_Transform.scale={0.2,0.2};
        setCurrentCell({5,5});
        //setCurrentLocation(MapClass::CellCoordToGlobal(getCurrentCell()));
        SetVisible(true);
        m_grid.SetActivate(true);

        //m_wayPointUnit.setCurrentLocation(getCurrentLocation());
        m_wayPointUnit.setCurrentCell(getCurrentCell());
        m_wayPointUnit.SetVisible(true);

        //setTargetCell({20,20});
        //m_wayPointUnit.setTargetCell(getTargetCell());
        //m_wayPointUnit.findPath(getTargetCell());
    }
    virtual void Update()override{
        Walk();
        m_grid.Start({Line(getCurrentLocation(),MapClass::CellCoordToGlobal(m_wayPointUnit.getFirstCell()))});
        m_grid.Draw(m_emptyTrans,defaultZIndex);
        m_wayPointUnit.Update();
        m_Transform.translation=getCurrentLocation();

    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
