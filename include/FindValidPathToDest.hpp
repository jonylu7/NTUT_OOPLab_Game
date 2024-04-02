//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP

#include "Map.hpp"
#include "Unit/PathUtility.hpp"

#include <random>
class FindValidPathToDest {
    enum class Side { R, L };

private:
    std::shared_ptr<MapClass> m_Map;

    glm::vec2 m_destinationCell;
    glm::vec2 m_nextCell;
    glm::vec2 m_currentCell;

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

        MoveDirection m_currentDir = MoveDirection::IDLE;

    protected:
        // set
        void setDestinationCell(glm::vec2 cell) {
            this->m_destinationCell = cell;
        }
        void setCurrentCell(glm::vec2 cell) {
            this->m_currentCell = glm::vec2(cell);
        }
        void setCurrentDir(MoveDirection direction) {
            m_currentDir = direction;
        }
        void setNextCell(glm::vec2 cell) {
            this->m_nextCell = glm::vec2(cell);
        }

        // get
        glm::vec2 getDestinationCell() {
            return m_destinationCell;
        }

        glm::vec2 getCurrentCell() {
            return m_currentCell;
        }
        MoveDirection getCurrentDir() {
            return m_currentDir;
        }
        glm::vec2 getNextCell() {
            return m_nextCell;
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

    public:
        FindValidPathToDest(){};
        ~FindValidPathToDest(){};

        Side randomlyChooseSide() {
            // Create a random number generator engine
            std::random_device rd;  // Obtain a random seed from the hardware
            std::mt19937 gen(rd()); // Initialize the Mersenne Twister
                                    // pseudo-random number generator

            // Define a distribution (uniform distribution in this case)
            std::uniform_int_distribution<int> distribution(
                0, 1); // Uniform distribution between 1 and 6 (inclusive)

            // Generate a random number
            int random_number =
                distribution(gen); // Generate a random number using
                                   // the generator and distribution

            switch (random_number) {
            case 0:
                return Side::R;
            case 1:
                return Side ::L;
            }
        }

        std::deque<MoveDirection> findPath(glm::vec2 currentcell,
                                           glm::vec2 destination) {
            // what if desintation is not walkable
            setCurrentCell(currentcell);
            setDestinationCell(destination);
            std::deque<MoveDirection> m_dirQue;

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
                    setCurrentDir(
                        PathUtility::PathUtility::getDirByRelativeCells(
                            getCurrentCell(), getDestinationCell()));

                    // set next
                    setNextCell(PathUtility::getNextCellByCurrent(
                        getCurrentDir(), getNextCell()));

                    whichSideToTouch = randomlyChooseSide();
                    // dirToTouch = nullptr;
                } else {
                    if (dirToTouch == nullptr) {
                        dirToTouch =
                            std::make_shared<MoveDirection>(getDirIfObstacle(
                                PathUtility::getDirByRelativeCells(
                                    getCurrentCell(), getNextCell()),
                                whichSideToTouch));
                    } else {
                        dirToTouch = std::make_shared<MoveDirection>(
                            getDirIfObstacle(*dirToTouch, whichSideToTouch));
                    }

                    setCurrentDir(*dirToTouch);
                    setNextCell(PathUtility::getNextCellByCurrent(
                        *dirToTouch, getCurrentCell()));
                }
            }
            return m_dirQue;
        }
    };
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
