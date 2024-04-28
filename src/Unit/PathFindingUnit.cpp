//
// Created by 盧威任 on 4/12/24.
//

//
// Created by 盧威任 on 4/1/24.
//
#include "Unit/PathfindingUnit.hpp"

void PathfindingUnit::walkTowardNextCell() {
    switch (m_currentDir) {
    case MoveDirection::RIGHT: {
        m_currentLocation = {m_currentLocation.x + m_MovementSpeed,
                             m_currentLocation.y};

        break;
    }
    case MoveDirection::LEFT: {
        m_currentLocation = {m_currentLocation.x - m_MovementSpeed,
                             m_currentLocation.y};

        break;
    }
    case MoveDirection::UP: {
        m_currentLocation = {m_currentLocation.x,
                             m_currentLocation.y + m_MovementSpeed};

        break;
    }
    case MoveDirection::DOWN: {
        m_currentLocation = {m_currentLocation.x,
                             m_currentLocation.y - m_MovementSpeed};

        break;
    }
    case MoveDirection::UP_RIGHT: {
        m_currentLocation = {m_currentLocation.x + m_MovementSpeed / SPEED,
                             m_currentLocation.y + m_MovementSpeed / SPEED};

        break;
    }
    case MoveDirection::DOWN_LEFT: {
        m_currentLocation = {m_currentLocation.x - m_MovementSpeed / SPEED,
                             m_currentLocation.y - m_MovementSpeed / SPEED};

        break;
    }
    case MoveDirection::DOWN_RIGHT: {
        m_currentLocation = {m_currentLocation.x + m_MovementSpeed / SPEED,
                             m_currentLocation.y - m_MovementSpeed / SPEED};

        break;
    }
    case MoveDirection::UP_LEFT: {
        m_currentLocation = {m_currentLocation.x - m_MovementSpeed / SPEED,
                             m_currentLocation.y + m_MovementSpeed / SPEED};

        break;
    }
    }
}

bool PathfindingUnit::arrivedAtNextCell() {
    if (m_moveDistance >= 48 * SPEED) {
        m_moveDistance = 0;
        return true;
    } else
        m_moveDistance += m_MovementSpeed;
    return false;
}
