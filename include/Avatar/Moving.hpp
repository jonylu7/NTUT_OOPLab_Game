//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MOVING_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MOVING_HPP
#include "Avatar/PathUtility.hpp"
#include "Display/Grid.hpp"
#include "Display/Line.hpp"
#include "Map/MapUtility.hpp"
#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
#include "glm/glm.hpp"

#define SPEED 1

class Moving {
protected:
    std::deque<MoveDirection> m_MovePath;

    std::vector<Line> m_lineVector;
    glm::vec2 m_CurrentLocation;

    MoveDirection m_CurrentDir = MoveDirection::IDLE;

    float m_MovementSpeed = 1.F;
    glm::vec2 m_PrevCell;

public:
    enum class AvatarStandingCorner {
        CENTER,
        UPPER_LEFT,
        UPPER_RIGHT,
        LOWER_LEFT,
        LOWER_RIGHT
    };

    Moving(){};
    ~Moving(){};

    glm::vec2 getCurrentCell() {
        return MapUtil::GlobalCoordToCellCoord(getCurrentLocation());
    }
    glm::vec2 getCurrentLocation() { return m_CurrentLocation; }
    void setCurrentLocation(glm::vec2 location) {
        m_CurrentLocation = location;
    }
    MoveDirection getCurrentDir() { return m_CurrentDir; }
    void setCurrentDir(MoveDirection dir) { m_CurrentDir = dir; }

    void moveUpdate() {
        if (ifArrivedAtNextCell()) {
            m_MovePath.pop_front();
            m_PrevCell = getCurrentCell();
            if (!m_MovePath.empty()) {
                setCurrentDir(m_MovePath.front());
            } else {
                finishedmovingUpdate();
            }
        }
        moveToNextCell();
    }

    void finishedmovingUpdate() {
        moveToCellCorner(AvatarStandingCorner::CENTER);
        setCurrentDir(MoveDirection::IDLE);
    }

    void moveToNextCell();
    void moveToCellCorner(AvatarStandingCorner corner);
    bool ifArrivedAtNextCell();

    void setMovePath(std::deque<MoveDirection> movepath) {
        if (movepath.empty()) {
            m_MovePath = {MoveDirection::IDLE};
            m_CurrentDir = MoveDirection::IDLE;
        } else {
            m_MovePath = movepath;
            m_CurrentDir = m_MovePath.front();
        }
        m_PrevCell = getCurrentCell();
    }

    bool ifMovePathEmpty() {
        if (m_MovePath.empty()) {
            return true;
        } else {
            return false;
        }
    }

    void setMovementSpeed(float speed) { m_MovementSpeed = speed; }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MOVING_HPP
