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
        }
        return newdir;
    }

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

    void findPath(glm::vec2 destination) {
        // what if desintation is not walkable
        setDestinationCell(destination);
        Side whichSideToTouch = randomlyChooseSide();
        MoveDirection dirToTouch = MoveDirection::IDLE;
        setCurrentDir(
            getDirByRelativeCells(getCurrentCell(), getDestinationCell()));
        while (getCurrentCell() != getDestinationCell()) {

            if (m_Map
                    ->getTileByCellPosition(
                        getNextCellByCurrent(getCurrentDir(), getCurrentCell()))
                    ->getWalkable()) {
                m_dirQue.push_back(getCurrentDir());
                // move current to next cell
                // set next

                setCurrentCell(
                    getNextCellByCurrent(getCurrentDir(), getCurrentCell()));
                // 這裏會造成無限迴圈

                auto followingDir = getDirByRelativeCells(getCurrentCell(),
                                                          getDestinationCell());

                bool ifOpposite = checkFollowingDirOppositeWithCurrent(
                    getCurrentDir(), followingDir, getCurrentCell());
                // if not opposite, or walk along
                if (!ifOpposite) {
                    setCurrentDir(followingDir);
                }

            } else {
                dirToTouch = getDirIfObstacle(
                    getDirByRelativeCells(
                        getCurrentCell(),
                        getNextCellByCurrent(getCurrentDir(),
                                             getCurrentCell())),
                    whichSideToTouch);

                setCurrentDir(dirToTouch);
            }
        }
    }
    virtual void Update() override {
        m_grid.DrawUsingCamera(m_emptyTrans, defaultZIndex);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
