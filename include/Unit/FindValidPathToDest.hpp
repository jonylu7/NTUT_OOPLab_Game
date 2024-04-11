//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
#include "Unit/PathfindingUnit.hpp"
#include <random>
class FindValidPathToDest : public PathfindingUnit {
private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::deque<MoveDirection> m_dirQue;
    bool b_InitNewLine = false;

public:
    enum class Side { R, L };
    FindValidPathToDest()
        : PathfindingUnit() {
        setMovementSpeed(48);
    };
    virtual ~FindValidPathToDest() override{};
    void Start(std::shared_ptr<MapClass> map) { m_Map = map; }
    MoveDirection getFirstCellDir() {
        if (!m_dirQue.empty()) {
            MoveDirection front = m_dirQue.front();
            m_dirQue.pop_front();
            return front;
        }

        return MoveDirection::IDLE;
    }

    void resetQueue() {
        b_InitNewLine = true;
        this->m_dirQue.clear();
        this->m_lineVector.clear();
    }
    Side randomlyChooseSide() {
        // Create a random number generator engine
        std::random_device rd;  // Obtain a random seed from the hardware
        std::mt19937 gen(rd()); // Initialize the Mersenne Twister
                                // pseudo-random number generator

        // Define a distribution (uniform distribution in this case)
        std::uniform_int_distribution<int> distribution(
            0, 1); // Uniform distribution between 1 and 6 (inclusive)

        // Generate a random number
        int random_number = distribution(gen); // Generate a random number using
                                               // the generator and distribution
        return Side::R;
        switch (random_number) {
        case 0:
            return Side::R;
        case 1:
            return Side ::L;
        }
    }

    MoveDirection findNewDirWhenCrash(Side side, glm::vec2 currentcell,
                                        MoveDirection currentdir) {

        // please be notice that the "Side's" R or L
        // represent its facing direction
        MoveDirection newdir = currentdir;
        while (m_Map
                   ->getTileByCellPosition(
                       getNextCellByCurrent(newdir, currentcell))
                   ->getWalkable() == false) {
            switch (newdir) {
            case MoveDirection::RIGHT: {
                if (side == Side::R) {
                    newdir = MoveDirection::UP_RIGHT;
                } else if (side == Side::L) {
                    newdir = MoveDirection::DOWN_RIGHT;
                }
            } break;

            case MoveDirection::LEFT: {
                if (side == Side::R) {
                    newdir = MoveDirection::DOWN_LEFT;
                } else if (side == Side::L) {
                    newdir = MoveDirection::UP_LEFT;
                }
                break;
            }
            case MoveDirection::UP: {
                if (side == Side::R) {
                    newdir = MoveDirection::UP_LEFT;
                } else if (side == Side::L) {
                    newdir = MoveDirection::UP_RIGHT;
                }
                break;
            }
            case MoveDirection::DOWN: {
                if (side == Side::R) {
                    newdir = MoveDirection::DOWN_RIGHT;
                } else if (side == Side::L) {
                    newdir = MoveDirection::DOWN_LEFT;
                }
                break;
            }
            case MoveDirection::UP_RIGHT: {
                if (side == Side::R) {
                    newdir = MoveDirection::RIGHT;
                } else if (side == Side::L) {
                    newdir = MoveDirection::UP;
                }
                break;
            }
            case MoveDirection::DOWN_LEFT: {
                if (side == Side::R) {
                    newdir = MoveDirection::LEFT;
                } else if (side == Side::L) {
                    newdir = MoveDirection::DOWN;
                }
                break;
            }
            case MoveDirection::DOWN_RIGHT: {
                if (side == Side::R) {
                    newdir = MoveDirection::RIGHT;
                } else if (side == Side::L) {
                    newdir = MoveDirection::DOWN;
                }
                break;
            }
            case MoveDirection::UP_LEFT: {
                if (side == Side::R) {
                    newdir = MoveDirection::LEFT;
                } else if (side == Side::L) {
                    newdir = MoveDirection::UP;
                }
                break;
            }
            case MoveDirection::IDLE: {
                // printf("Direction debug didn't move\n");
                break;
            }
            }
        }
        return newdir;
    }
/*
    bool checkFollowingDirOppositeWithCurrent(MoveDirection currentDir,
                                              MoveDirection followingDir,
                                              glm::vec2 currentcell) {
        auto firstStep = getNextCellByCurrent(currentDir, currentcell);
        auto nextStep = getNextCellByCurrent(followingDir, firstStep);

        if (currentcell == nextStep) {
            return true;
        } else {
            return false;
        }
    }

    */



    bool isTouchedByObstacle(Side side,glm::vec2 currentcell,MoveDirection currentdir){
        //abs
        std::shared_ptr<TileClass> upTile = m_Map->getTileByCellPosition(
            glm::vec2(currentcell.x, currentcell.y + 1));
        std::shared_ptr<TileClass> downTile = m_Map->getTileByCellPosition(
            glm::vec2(currentcell.x, currentcell.y - 1));
        std::shared_ptr<TileClass> rightTile = m_Map->getTileByCellPosition(
            glm::vec2(currentcell.x + 1, currentcell.y));
        std::shared_ptr<TileClass> leftTile = m_Map->getTileByCellPosition(
            glm::vec2(currentcell.x - 1, currentcell.y));

        std::shared_ptr<TileClass> upRightTile = m_Map->getTileByCellPosition(
            glm::vec2(currentcell.x + 1, currentcell.y + 1));
        std::shared_ptr<TileClass> downRightTile = m_Map->getTileByCellPosition(
            glm::vec2(currentcell.x + 1, currentcell.y - 1));
        std::shared_ptr<TileClass> upLeftTile = m_Map->getTileByCellPosition(
            glm::vec2(currentcell.x - 1, currentcell.y + 1));
        std::shared_ptr<TileClass> downLeftTile = m_Map->getTileByCellPosition(
            glm::vec2(currentcell.x - 1, currentcell.y - 1));


        std::shared_ptr<TileClass> checkedTile=std::make_shared<TileClass>();
        MoveDirection newdir;
        switch (currentdir) {
        case MoveDirection::RIGHT: {
            if (side == Side::R) {
               checkedTile=downRightTile;
            } else if (side == Side::L) {
                checkedTile=upRightTile;
            }
        } break;

        case MoveDirection::LEFT: {
            if (side == Side::R) {
                checkedTile=downLeftTile;
            } else if (side == Side::L) {
               checkedTile=upLeftTile;
            }
            break;
        }
        case MoveDirection::UP: {
            if (side == Side::R) {
               checkedTile=upRightTile;
            } else if (side == Side::L) {
              checkedTile=upLeftTile;
            }
            break;
        }
        case MoveDirection::DOWN: {
            if (side == Side::R) {
                checkedTile=downLeftTile;
            } else if (side == Side::L) {
               checkedTile=downRightTile;
            }
            break;
        }
        case MoveDirection::UP_RIGHT: {
            if (side == Side::R) {
                checkedTile=rightTile;
            } else if (side == Side::L) {
                checkedTile=upTile;
            }
            break;
        }
        case MoveDirection::DOWN_LEFT: {
            if (side == Side::R) {
                checkedTile=leftTile;
            } else if (side == Side::L) {
               checkedTile=downTile;
            }
            break;
        }
        case MoveDirection::DOWN_RIGHT: {
            if (side == Side::R) {
                checkedTile=downTile;
            } else if (side == Side::L) {
               checkedTile=rightTile;
            }
            break;
        }
        case MoveDirection::UP_LEFT: {
            if (side == Side::R) {
               checkedTile=upTile;
            } else if (side == Side::L) {
                checkedTile=leftTile;
            }
            break;
        }
        case MoveDirection::IDLE: {
            // printf("Direction debug didn't move\n");
            break;
        }

        }

        if(checkedTile->getWalkable()== true){
            return false;
        }else{
            return true;
        }



    }


    MoveDirection findNewDirWhenNotTouchedByObstacle(Side side, glm::vec2 currentcell,
                                       MoveDirection currentdir){

        MoveDirection newdir;
        switch (currentdir) {
        case MoveDirection::RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN_RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP_RIGHT;
            }
        } break;

        case MoveDirection::LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN_LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP_LEFT;
            }
            break;
        }
        case MoveDirection::UP: {
            if (side == Side::R) {
                newdir = MoveDirection::UP_RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP_LEFT;
            }
            break;
        }
        case MoveDirection::DOWN: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN_LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN_RIGHT;
            }
            break;
        }
        case MoveDirection::UP_RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP;
            }
            break;
        }
        case MoveDirection::DOWN_LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN;
            }
            break;
        }
        case MoveDirection::DOWN_RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN;
            } else if (side == Side::L) {
                newdir = MoveDirection::RIGHT;
            }
            break;
        }
        case MoveDirection::UP_LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::UP;
            } else if (side == Side::L) {
                newdir = MoveDirection::LEFT;
            }
            break;
        }
        case MoveDirection::IDLE: {
            // printf("Direction debug didn't move\n");
            break;
        }



    }}


    std::vector<MoveDirection> moveAlongsideObstacle(Side side, glm::vec2 currentcell,
                               MoveDirection currentdir,glm::vec2 destinationcell){

        //side
        //
        //return dirque
        //check
        std::vector<MoveDirection> path;
        while(!canResumeWalkingStraight(currentcell,destinationcell)){

            //if next is not touched by obstacle, turn
            if(!isTouchedByObstacle(side,currentcell,currentdir)){
                currentdir= findNewDirWhenNotTouchedByObstacle(side,currentcell,currentdir);
            }

            //if next to be obstacle, turn findNewDirWhenCrash
            //newcurrentdir=findNewDirWhenNotTouchedByObstacle(side,currentcell,newcurrentdir);

            //walk along
            path.push_back(currentdir);
            currentcell= getNextCellByCurrent(currentdir,currentcell);

            path.empty();

        }

        return path;

    }


    void findPath(glm::vec2 destinationcell) {
        if (m_Map->getTileByCellPosition(destinationcell)->getWalkable() ==
            false) {
            return;
        }


        glm::vec2 currentcell = getCurrentCell();
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
                    m_dirQue.push_back(turndir);
                    currentcell= getNextCellByCurrent(turndir,currentcell);
                };


                std::vector<MoveDirection> movealong=moveAlongsideObstacle(whichSideToTouchObstacle,currentcell,turndir,destinationcell);

                for(auto i:movealong){
                    m_dirQue.push_back(i);
                    currentcell= getNextCellByCurrent(i,currentcell);
                }

            }
        }
    }



    bool canResumeWalkingStraight(glm::vec2 currentcell, glm::vec2 destinationcell){
        std::vector<MoveDirection> path;
        auto arrived=findStraightPath(currentcell,destinationcell,&path);
        if(arrived || !path.empty()){
            return true;
        }
        return false;
    }

    bool findStraightPath(glm::vec2 currentcell, glm::vec2 destinationcell,
                          std::vector<MoveDirection> *path) {

        while (currentcell != destinationcell) {
            MoveDirection followingDir =
                getDirByRelativeCells(currentcell, destinationcell);

            if (m_Map->getWalkable(
                    getNextCellByCurrent(followingDir, currentcell))) {
                path->push_back(followingDir);
                currentcell = getNextCellByCurrent(followingDir, currentcell);
            } else {
                // if meet obstacle, stop in front of it, but unknown dir.
                return false;
            }
        }
        return true;
    }

    virtual void Update() override {
        m_grid.DrawUsingCamera(m_emptyTrans, defaultZIndex);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
