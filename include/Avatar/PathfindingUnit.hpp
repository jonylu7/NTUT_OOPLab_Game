//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
#include "Avatar/PathUtility.hpp"
#include "Display/Grid.hpp"
#include "Display/Line.hpp"
#include "Map/MapUtility.hpp"
#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
#include "glm/glm.hpp"

#define SPEED 1

class PathfindingUnit {
protected:
    std::deque<MoveDirection> m_MovePath;

    std::vector<Line> m_lineVector;
    float defaultZIndex = 15;
    glm::vec2 m_CurrentLocation;
    glm::vec2 m_DestinationCell;

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

    glm::vec2 getCurrentCell() {
        return MapUtil::GlobalCoordToCellCoord(getCurrentLocation());
    }
    glm::vec2 getCurrentLocation() { return m_CurrentLocation; }
    MoveDirection getCurrentDir() { return m_CurrentDir; }

    void moveToNextCell();
    void moveToCellCorner(AvatarStandingCorner corner);
    bool ifArrivedAtNextCell();

    void setMovePath(std::deque<MoveDirection> movepath) {
        m_MovePath = movepath;
        setNewDestinationIsSetted(false);
    }

    glm::vec2 getDestinationCell() { return m_DestinationCell; }
    bool ifNewDestionationIsSetted() { return b_NewDestinationIsSetted; }

    void setMovementSpeed(float speed) { m_MovementSpeed = speed; }

    void setNewDestinationIsSetted(bool value) {
        b_NewDestinationIsSetted = value;
    }

    void setDestinationCell(glm::vec2 destination) {
        m_DestinationCell = destination;
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
