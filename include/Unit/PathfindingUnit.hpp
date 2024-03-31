//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
#include "Grid.hpp"
#include "Line.hpp"
#include "Map.hpp"

#include "Tile.hpp"
#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
#include "glm/glm.hpp"

#define SPEED 1

class PathfindingUnit : public Util::GameObject {
protected:
    enum class UnitMode { DEAD, ALIVE };
    enum class MoveDirection {
        UP,
        UP_RIGHT,
        UP_LEFT,
        RIGHT,
        LEFT,
        DOWN_RIGHT,
        DOWN_LEFT,
        DOWN,
        IDLE
    };

    Util::Transform m_emptyTrans;
    Line m_line;
    Grid m_grid;
    std::vector<Line> m_lineVector;
    float defaultZIndex = 15;
    UnitMode m_currentMode = UnitMode::ALIVE; // debug :DEAD
private:
    glm::vec2 m_destinationCell;
    // glm::vec2 m_nextCell;
    glm::vec2 m_currentCell;
    glm::vec2 m_currentLocation;

    MoveDirection m_currentDir = MoveDirection::IDLE;

    float m_MovementSpeed = 1.F;

    int moveDistance = 0;

public:
    PathfindingUnit() {
        m_Transform.scale = {0.1, 0.1};
        m_ZIndex = defaultZIndex;
    };
    virtual ~PathfindingUnit(){};

    //

    void setDestinationCell(int x, int y) {
        this->m_destinationCell = {glm::vec2(x, y)};
    }
    void setDestinationCell(glm::vec2 cell) { this->m_destinationCell = cell; }
    glm::vec2 getDestinationCell() { return m_destinationCell; }

    void setCurrentCell(glm::vec2 cell) {
        this->m_currentCell = glm::vec2(cell);
        // MapClass::CellCoordToGlobal(m_currentCell);
        glm::vec2 temp(
            int(this->m_currentCell.x * CELL_SIZE.x) + 0.5 * CELL_SIZE.x,
            int(this->m_currentCell.y * CELL_SIZE.y) + 0.5 * CELL_SIZE.y);
        // m_currentLocation={temp.x+CELL_SIZE.x/2,temp.y+CELL_SIZE.y/2};
        m_currentLocation = {temp.x, temp.y};
    }
    glm::vec2 getCurrentCell() { return m_currentCell; }

    // void setNextCell(glm::vec2 cell) { this->m_nextCell = glm::vec2(cell); }
    // glm::vec2 getNextCell() { return m_nextCell; }

    glm::vec2 getCurrentLocation() { return m_currentLocation; }

    void setMovementSpeed(int speed) { this->m_MovementSpeed = speed; }

    MoveDirection getCurrentDir() { return m_currentDir; }
    void setCurrentDir(MoveDirection direction) { m_currentDir = direction; }

    MoveDirection getDirByRelativeCells(glm::vec2 currentcell,
                                        glm::vec2 destinationcell);
    // void findNextCellDir(MoveDirection lastDir, int times);
    glm::vec2 getNextCellByCurrent(MoveDirection currentdir,
                                   glm::vec2 currentcell);
    // bool UpdateNextCell(int *times);

    bool walkTowardNextCell();

    virtual void Start() {}
    virtual void Update() {
        m_Transform.translation = getCurrentLocation();
        Draw();
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
