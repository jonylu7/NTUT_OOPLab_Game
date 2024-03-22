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
    bool b_selectedNewTarget= false;
    bool b_justStarted = true;
public:
    Avatar():PathfindingUnit(){};
    ~Avatar()override{};

    virtual void Start(glm::vec2 target){ //target = Barrack's waypointLocation
        //setCurrentCell()  //CurrentCell = Structure's Location
        this->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
        SetVisible(true);
        m_grid.SetActivate(true);

        setCurrentCell(target);
        setNextCell(target);
        m_wayPointUnit.setCurrentCell(target);
        m_wayPointUnit.setNextCell(target);
        setNewTarget(getCurrentCell());

        setMovementSpeed(4);
    }
    virtual void aliveUpdate(){
        if(walkTowardNextCell()||b_justStarted){
            b_justStarted= false;
            setCurrentCell(MapClass::GlobalCoordToCellCoord(getCurrentLocation()));
            setCurrentDir(m_wayPointUnit.getFirstCellDir());
            UpdateNextCell();
            printf("(aliveUpdate) getting new dir\n");
        }
        m_wayPointUnit.Update();
        m_Transform.translation=getCurrentLocation();
        Draw();
        onSelect(true);
        printf("-----------------------------\n");
    }
    virtual void Update()override{
        switch(m_currentMode){
        case (UnitMode::DEAD):{
            SetVisible(false);
        }
        case (UnitMode::ALIVE):{
            aliveUpdate();
        }
        }
    }
    void setNewTarget(glm::vec2 target){
        setTargetCell(target.x,target.y);
        m_wayPointUnit.resetQueue();
        m_wayPointUnit.setCurrentCell(getNextCell());
        m_wayPointUnit.setNextCell(getNextCell());
        m_wayPointUnit.findPath(getTargetCell());
        //setCurrentDir(m_wayPointUnit.getFirstCellDir());
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
