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

        switch (random_number) {
        case 0:
            return Side::R;
        case 1:
            return Side ::L;
        }
    }

    MoveDirection getDirIfObstacle(MoveDirection ogDir, Side side) {

        // please be notice that the "Side's" R or L represent its facing
        // direction
        MoveDirection newdir;
        switch (ogDir) {
        case MoveDirection::RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN_RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP_RIGHT;
            }
        } break;

        case MoveDirection::LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::UP_LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN_LEFT;
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
            printf("Direction debug didn't move\n");
            break;
        }

            return newdir;
        }
    }

    void findPath(glm::vec2 destination) {
        // what if desintation is not walkable
        setDestinationCell(destination);
        Side whichSideToTouch = randomlyChooseSide();
        std::shared_ptr<MoveDirection> dirToTouch = nullptr;
        while (getCurrentCell() != getDestinationCell()) {

            if (m_Map
                    ->getTileByCellPosition(
                        glm::vec2(getNextCell().x, getNextCell().y))
                    ->getWalkable()) {
                // move current to next cell
                setCurrentCell(getNextCell());
                m_dirQue.push_back(getCurrentDir());
                setCurrentDir(getDirByRelativeCells(getCurrentCell(),
                                                    getDestinationCell()));

                // set next
                setNextCell(
                    getNextCellByCurrent(getCurrentDir(), getNextCell()));

                m_lineVector.push_back(
                    Line(MapUtil::CellCoordToGlobal(getCurrentCell()),
                         MapUtil::CellCoordToGlobal(getNextCell())));
                whichSideToTouch = randomlyChooseSide();
                // dirToTouch = nullptr;
            } else {
                if (dirToTouch == nullptr) {
                    dirToTouch = std::make_shared<MoveDirection>(
                        getDirIfObstacle(getDirByRelativeCells(getCurrentCell(),
                                                               getNextCell()),
                                         whichSideToTouch));
                } else {
                    dirToTouch = std::make_shared<MoveDirection>(
                        getDirIfObstacle(*dirToTouch, whichSideToTouch));
                }

                setCurrentDir(*dirToTouch);
                setNextCell(
                    getNextCellByCurrent(*dirToTouch, getCurrentCell()));
                // setCurrentCell(getNextCell());
                //  not walkable
                //  select one direction (left or right) using one of
                //  several heuristics advance in the said direction
                //  keeping your left/right hand touching the obstacle's
                //  wall when you can advance in a straight line towards
                //  the target again, do so

                // getNextCellObstacle(randomlyChooseSide(),
                // nextCellClear);
            }
        }
        /*
        while (getCurrentCell().x != getDestinationCell().x &&
               getCurrentCell().y != getDestinationCell().y) {
            // printf("(FindValidPathToDest)destination :
    {%.0f,%.0f}\n", getDestinationCell().x, getDestinationCell().y);
                   // printf(
                   "(FindValidPathToDest)finding : %d\n "
                   "(FindValidPathToDest)Cell "
                   "now "
                   ":{%.0f,%.0f}\n(FindValidPathToDest)Cell next : "
                   "{%.0f,%.0f}\n",
                       // count++, getCurrentCell().x,
    getCurrentCell().y,
                       // getNextCell().x, getNextCell().y);
                       setCurrentCell(getNextCell());
                   m_dirQue.push_back(getCurrentDir());
                   findNextCellDir();
                   UpdateNextCell();
                   m_lineVector.push_back(
                       Line(MapClass::CellCoordToGlobal(getCurrentCell()),
                            MapClass::CellCoordToGlobal(getNextCell())));

    }
*/
        // draw lines
        if (b_InitNewLine && getCurrentCell().x == getDestinationCell().x &&
            getCurrentCell().y == getDestinationCell().y) {
            b_InitNewLine = false;
            if (!m_lineVector.empty()) {
                m_grid.Start(m_lineVector);
            }
        }
        m_grid.SetActivate(true);
    }
    virtual void Update() override {
        m_grid.DrawUsingCamera(m_emptyTrans, defaultZIndex);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
