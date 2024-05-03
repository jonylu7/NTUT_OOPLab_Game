//
// Created by 盧威任 on 4/12/24.
//

//
// Created by 盧威任 on 4/1/24.
//
#include "Avatar/Moving.hpp"

void Moving::moveToNextCell() {
    switch (m_CurrentDir) {
    case MoveDirection::RIGHT: {
        m_CurrentLocation = {m_CurrentLocation.x + m_MovementSpeed,
                             m_CurrentLocation.y};

        break;
    }
    case MoveDirection::LEFT: {
        m_CurrentLocation = {m_CurrentLocation.x - m_MovementSpeed,
                             m_CurrentLocation.y};

        break;
    }
    case MoveDirection::UP: {
        m_CurrentLocation = {m_CurrentLocation.x,
                             m_CurrentLocation.y + m_MovementSpeed};

        break;
    }
    case MoveDirection::DOWN: {
        m_CurrentLocation = {m_CurrentLocation.x,
                             m_CurrentLocation.y - m_MovementSpeed};

        break;
    }
    case MoveDirection::UP_RIGHT: {
        m_CurrentLocation = {m_CurrentLocation.x + m_MovementSpeed / SPEED,
                             m_CurrentLocation.y + m_MovementSpeed / SPEED};

        break;
    }
    case MoveDirection::DOWN_LEFT: {
        m_CurrentLocation = {m_CurrentLocation.x - m_MovementSpeed / SPEED,
                             m_CurrentLocation.y - m_MovementSpeed / SPEED};

        break;
    }
    case MoveDirection::DOWN_RIGHT: {
        m_CurrentLocation = {m_CurrentLocation.x + m_MovementSpeed / SPEED,
                             m_CurrentLocation.y - m_MovementSpeed / SPEED};

        break;
    }
    case MoveDirection::UP_LEFT: {
        m_CurrentLocation = {m_CurrentLocation.x - m_MovementSpeed / SPEED,
                             m_CurrentLocation.y + m_MovementSpeed / SPEED};

        break;
    }
    }
}

bool Moving::ifArrivedAtNextCell() {
    // change this to check
    // previous cell
    // getCurrentCell() != previousCell()
    return false;
}
void Moving::moveToCellCorner(AvatarStandingCorner corner) {
    float quaterHeight = CELL_SIZE.y / 4;
    float quaterWidth = CELL_SIZE.x / 4;
    switch (corner) {
    case (AvatarStandingCorner::CENTER):
        break;
    case (AvatarStandingCorner::UPPER_LEFT):
        m_CurrentLocation = {m_CurrentLocation.x - quaterWidth,
                             m_CurrentLocation.y + quaterHeight};
        break;
    case (AvatarStandingCorner::UPPER_RIGHT):
        m_CurrentLocation = {m_CurrentLocation.x + quaterWidth,
                             m_CurrentLocation.y + quaterHeight};
        break;
    case (AvatarStandingCorner::LOWER_LEFT):
        m_CurrentLocation = {m_CurrentLocation.x - quaterWidth,
                             m_CurrentLocation.y - quaterHeight};
        break;
    case (AvatarStandingCorner::LOWER_RIGHT):
        m_CurrentLocation = {m_CurrentLocation.x + quaterWidth,
                             m_CurrentLocation.y - quaterHeight};
        break;
    }
}
