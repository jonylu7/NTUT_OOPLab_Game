//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
#include "PathfindingUnit.hpp"

class WayPointUnit:public PathfindingUnit{
private:
    std::vector<glm::vec2> m_pathQueue;
    int count=0;
public:
    WayPointUnit():PathfindingUnit(){};
    virtual ~WayPointUnit()override{};


    glm::vec2 getFirstCell(){return m_pathQueue.front();}

    void resetQueue(){this->m_pathQueue.clear();}
    void findPath(){
        resetQueue();
        while(getCurrentCell()!=getTargetCell()&&count<=300){
            count++;
            findNextCellDir();
            NextCell();
            m_pathQueue.push_back(getCurrentCell());
            m_lineVector.push_back(Line(MapClass::CellCoordToGlobal(getCurrentCell()),MapClass::CellCoordToGlobal(getNextCell())));
        }
        m_grid.SetActivate(true);
    }
    virtual void Update()override{
        m_grid.Start(m_lineVector);
        m_grid.Draw(m_emptyTrans,defaultZIndex);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTUNIT_HPP
