//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
#include "Unit/PathfindingUnit.hpp"


class WayPointUnit:public PathfindingUnit{
private:
    std::deque<MoveDirection> m_dirQue;
    std::deque<glm::vec2> m_pathQueue;
    int count=0;
public:
    WayPointUnit():PathfindingUnit(){setMovementSpeed(48);};
    virtual ~WayPointUnit()override{};


    glm::vec2 getFirstCell(){
        if(m_pathQueue.size()!=0){
            glm::vec2 front = m_pathQueue.front();
            m_pathQueue.pop_front();
            if(m_lineVector.size()!=0){
                m_lineVector.pop_front();
            }
            m_grid.queStart( m_lineVector);
            return front;
        }
        return {-1,-1};
    }
    MoveDirection getFirstCellDir(){
        if( m_dirQue.size()!=0){
            MoveDirection front = m_dirQue.front();
            m_dirQue.pop_front();
            return front;
        }
        return MoveDirection::IDLE;
    }

    void resetQueue(){
        this->m_pathQueue.clear();
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
            m_pathQueue.push_back(getCurrentCell());
            findNextCellDir();
            UpdateNextCell();
            m_lineVector.push_back(Line(MapClass::CellCoordToGlobal(getCurrentCell()),MapClass::CellCoordToGlobal(getNextCell())));
        }
        m_grid.SetActivate(true);
    }
    virtual void Update()override{
        m_grid.DrawUsingCamera(m_emptyTrans,defaultZIndex);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
