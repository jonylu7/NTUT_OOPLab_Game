//
// Created by 盧威任 on 4/12/24.
//

#include "FindValidPathToDest.hpp"

std::deque<MoveDirection> FindValidPathToDest::findPath(glm::vec2 currentcell, glm::vec2 destinationcell) {
    std::deque<MoveDirection> m_dirQue;
    if (m_Map->getTileByCellPosition(destinationcell)->getWalkable() ==
        false) {
        return m_dirQue;
    }

    Side whichSideToTouchObstacle = randomlyChooseSide();


    while (currentcell != destinationcell) {
        std::vector<MoveDirection> newDirque;
        bool arrived =
            findStraightPath(currentcell, destinationcell, &newDirque);
        for(auto i:newDirque){
            m_dirQue.push_back(i);
            currentcell= getNextCellByCurrent(i,currentcell);
        }
        //push newdirque into dirque and update current cell and current dir


        if (arrived) {
            break;
        }else{
            auto facingDir=getDirByRelativeCells(currentcell, destinationcell);
            //turn
            MoveDirection turndir;
            if(m_Map->getWalkable(getNextCellByCurrent(facingDir,currentcell))==false){
                turndir=findNewDirWhenCrash(whichSideToTouchObstacle,currentcell,facingDir);
            };


            std::vector<MoveDirection> movealong=moveAlongsideObstacle(whichSideToTouchObstacle,currentcell,turndir,destinationcell);

            for(auto i:movealong){
                m_dirQue.push_back(i);
                currentcell= getNextCellByCurrent(i,currentcell);
            }

        }
    }
}

