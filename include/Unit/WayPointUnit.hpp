//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
#include "Unit/PathfindingUnit.hpp"


class WayPointUnit:public PathfindingUnit{
private:
    std::vector<glm::vec2> m_pathQueue;
    int count=0;
public:
    WayPointUnit():PathfindingUnit(){setMovementSpeed(48);};
    virtual ~WayPointUnit()override{};


    glm::vec2 getFirstCell(){return m_pathQueue.front();}

    void resetQueue(){this->m_pathQueue.clear();}
    void findPath(int x,int y){
        setTargetCell(x,y);
        while(getCurrentCell()!=getTargetCell()&&count<=50){
            printf("target : {%.0f,%.0f}\n",getTargetCell().x,getTargetCell().y);
            printf("finding : %d\n Cell now :{%.0f,%.0f}\n,Cell next : {%.0f,%.0f}\n",count++,getCurrentCell().x,getCurrentCell().y,getNextCell().x,getNextCell().y);

            findNextCellDir();  //find Direction only
            NextCell();     //set current=next then use dir to find next

            m_pathQueue.push_back(getCurrentCell());
            m_lineVector.push_back(Line(MapClass::CellCoordToGlobal(getCurrentCell()),MapClass::CellCoordToGlobal(getNextCell())));
        }
        m_grid.SetActivate(true);
    }
    virtual void Update()override{
        m_grid.Start( m_lineVector);
        m_grid.DrawUsingCamera(m_emptyTrans,defaultZIndex);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
