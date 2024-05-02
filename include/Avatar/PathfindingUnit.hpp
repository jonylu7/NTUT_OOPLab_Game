//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
#include "Avatar/PathUtility.hpp"
#include "Display/Grid.hpp"
#include "Display/Line.hpp"

#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
#include "glm/glm.hpp"

#define SPEED 1

class PathfindingUnit {
protected:
    std::deque<MoveDirection> m_MovePath;

    std::vector<Line> m_lineVector;
    float defaultZIndex = 15;
    glm::vec2 m_destinationCell;
    glm::vec2 m_NextCell;
    glm::vec2 m_CurrentCell;
    glm::vec2 m_CurrentLocation;

    MoveDirection m_CurrentDir = MoveDirection::IDLE;

    float m_MovementSpeed = 1.F;

    int m_MoveDistance = 0;

    bool b_NewDestinationIsSetted = false;

public:
    enum class AvatarStandingCorner {
        CENTER,
        UPPER_LEFT,
        UPPER_RIGHT,
        LOWER_LEFT,
        LOWER_RIGHT
    };

    PathfindingUnit(){};
    virtual ~PathfindingUnit(){};

    void setDestinationCell(int x, int y) {
        this->m_destinationCell = {glm::vec2(x, y)};
    }
    void setDestinationCell(glm::vec2 cell) { this->m_destinationCell = cell; }
    glm::vec2 getDestinationCell() { return m_destinationCell; }

    void setCurrentCell(glm::vec2 cell) {
        this->m_CurrentCell = glm::vec2(cell);
        glm::vec2 temp(
            int(this->m_CurrentCell.x * CELL_SIZE.x) + 0.5 * CELL_SIZE.x,
            int(this->m_CurrentCell.y * CELL_SIZE.y) + 0.5 * CELL_SIZE.y);
        m_CurrentLocation = {temp.x, temp.y};
    }
    glm::vec2 getCurrentCell() { return m_CurrentCell; }
    glm::vec2 getCurrentLocation() { return m_CurrentLocation; }
    MoveDirection getCurrentDir() { return m_CurrentDir; }
    glm::vec2 getNextCell() { return m_NextCell; }
    void setNextCell(glm::vec2 nextcell) { m_NextCell = nextcell; }

    void moveToNextCell();
    void moveToCellCorner(AvatarStandingCorner corner);
    bool arrivedAtNextCell();

    void setMovePath(std::deque<MoveDirection> movepath) {
        m_MovePath = movepath;
        setNewDestinationIsSetted(false);
    }

    bool ifNewDestionationIsSetted() { return b_NewDestinationIsSetted; }

    void setNewDestinationIsSetted(bool value) {
        b_NewDestinationIsSetted = value;
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
