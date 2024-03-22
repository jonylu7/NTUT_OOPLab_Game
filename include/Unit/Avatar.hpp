//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "Unit/PathfindingUnit.hpp"
#include "Unit/WayPointUnit.hpp"

class Avatar:public PathfindingUnit{
private:
    WayPointUnit m_wayPointUnit;
    long count=0;
    bool b_selectedNewTarget;
public:
    void Start(glm::vec2 target){ //target = Barrack's waypointLocation
        //setCurrentCell()  //CurrentCell = Structure's Location
        this->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
        setTargetCell(target.x,target.y);
        SetVisible(true);
        m_grid.SetActivate(true);

        m_wayPointUnit.setCurrentCell(getCurrentCell());
        m_wayPointUnit.setNextCell(getCurrentCell());
        m_wayPointUnit.SetVisible(true);
        m_wayPointUnit.findPath(getTargetCell().x,getTargetCell().y);

        setMovementSpeed(4);
        setNextCell(m_wayPointUnit.getFirstCell());
        setCurrentDir(m_wayPointUnit.getFirstCellDir());
    }
    virtual void Update()override{
        m_wayPointUnit.findPath(getTargetCell().x,getTargetCell().y);
        if(Walk()){
            glm::vec2 nextCell = m_wayPointUnit.getFirstCell();
            if(nextCell.x!=-1&&nextCell.y!=-1) {
                setCurrentCell(getNextCell()); // reset object location
                setNextCell(nextCell);
                m_wayPointUnit.setCurrentCell(getCurrentCell());
                setCurrentDir(m_wayPointUnit.getFirstCellDir());
            }
        }else{//m_grid.Start({Line(getCurrentLocation(),MapClass::CellCoordToGlobal(getNextCell()))});
        }
        m_grid.DrawUsingCamera(m_emptyTrans,defaultZIndex);
        m_wayPointUnit.Update();
        m_Transform.translation=getCurrentLocation();
        Draw();
        onSelect(true);
    }
    void setNewTarget(glm::vec2 target){
        setTargetCell(target.x,target.y);
        m_wayPointUnit.resetQueue();
        m_wayPointUnit.setCurrentCell(getNextCell());
        m_wayPointUnit.setNextCell(getNextCell());
        m_wayPointUnit.findPath(getTargetCell().x,getTargetCell().y);
    }
    void onSelect(bool selected){
        if (b_selectedNewTarget) {
            this->setNewTarget(
                MapClass::GlobalCoordToCellCoord(MapClass::ScreenToGlobalCoord(Util::Input::GetCursorPosition())));
            b_selectedNewTarget = false;
        }
        if (selected) {
            if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_RB)) {
                b_selectedNewTarget = true;
            }
        }
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
