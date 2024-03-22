//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
#include "Unit/PathfindingUnit.hpp"


class WayPointUnit:public PathfindingUnit{
private:
    std::deque<MoveDirection> m_dirQue;
    int count=0;
    bool b_InitNewLine= false;
public:
    WayPointUnit():PathfindingUnit(){setMovementSpeed(48);};
    virtual ~WayPointUnit()override{};

    MoveDirection getFirstCellDir(){
        if( !m_dirQue.empty()){
            MoveDirection front = m_dirQue.front();
            m_dirQue.pop_front();
            return front;
        }

        return MoveDirection::IDLE;
    }

    void resetQueue(){
        b_InitNewLine= true;
        this->m_dirQue.clear();
        this->m_lineVector.clear();
    }
    void findPath(glm::vec2 target){
        setTargetCell(target);
        while(getCurrentCell().x!=getTargetCell().x&&getCurrentCell().y!=getTargetCell().y){
            printf("(WayPointUnit)target : {%.0f,%.0f}\n",getTargetCell().x,getTargetCell().y);
            printf("(WayPointUnit)finding : %d\n (WayPointUnit)Cell now :{%.0f,%.0f}\n(WayPointUnit)Cell next : {%.0f,%.0f}\n",count++,getCurrentCell().x,getCurrentCell().y,getNextCell().x,getNextCell().y);
            setCurrentCell(getNextCell());
            m_dirQue.push_back(getCurrentDir());
            findNextCellDir();
            UpdateNextCell();
            m_lineVector.push_back(Line(MapClass::CellCoordToGlobal(getCurrentCell()),MapClass::CellCoordToGlobal(getNextCell())));
        }
        if(b_InitNewLine && getCurrentCell().x==getTargetCell().x && getCurrentCell().y==getTargetCell().y){
            b_InitNewLine= false;
            if(!m_lineVector.empty()){
                m_grid.Start(m_lineVector);
            }
        }
        m_grid.SetActivate(true);
    }
    virtual void Update()override{
        m_grid.DrawUsingCamera(m_emptyTrans,defaultZIndex);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
