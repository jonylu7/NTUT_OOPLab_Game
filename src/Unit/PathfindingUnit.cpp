//
// Created by nudle on 2024/3/15.
//
#include "Unit/PathfindingUnit.hpp"
glm::vec2 PathfindingUnit::getNextCellByCurrent(MoveDirection currentdir,
                                                glm::vec2 currentcell) {
    switch (currentdir) {
    case MoveDirection::RIGHT: {
        currentcell = {currentcell.x + 1, currentcell.y};
        break;
    }
    case MoveDirection::LEFT: {
        currentcell = {currentcell.x - 1, currentcell.y};
        break;
    }
    case MoveDirection::UP: {
        currentcell = {currentcell.x, currentcell.y + 1};
        break;
    }
    case MoveDirection::DOWN: {
        currentcell = {currentcell.x, currentcell.y - 1};
        break;
    }
    case MoveDirection::UP_RIGHT: {
        currentcell = {currentcell.x + 1, currentcell.y + 1};
        break;
    }
    case MoveDirection::DOWN_LEFT: {
        currentcell = {currentcell.x - 1, currentcell.y - 1};
        break;
    }
    case MoveDirection::DOWN_RIGHT: {
        currentcell = {currentcell.x + 1, currentcell.y - 1};
        break;
    }
    case MoveDirection::UP_LEFT: {
        currentcell = {currentcell.x - 1, currentcell.y + 1};
        break;
    }
    case MoveDirection::IDLE: {
        printf("Direction debug didn't move\n");
        break;
    }
    }
    return currentcell;
}
/*
bool PathfindingUnit::UpdateNextCell(int *times) {
    switch (direction) {
    case MoveDirection::RIGHT: {
        nextcell = {nextcell.x + 1, nextcell.y};
        break;
    }
    case MoveDirection::LEFT: {
        nextcell = {nextcell.x - 1, nextcell.y};
        break;
    }
    case MoveDirection::UP: {
        nextcell = {nextcell.x, nextcell.y + 1};
        break;
    }
    case MoveDirection::DOWN: {
        nextcell = {nextcell.x, nextcell.y - 1};
        break;
    }
    case MoveDirection::UP_RIGHT: {
        nextcell = {nextcell.x + 1, nextcell.y + 1};
        break;
    }
    case MoveDirection::DOWN_LEFT: {
        nextcell = {nextcell.x - 1, nextcell.y - 1};
        break;
    }
    case MoveDirection::DOWN_RIGHT: {
        nextcell = {nextcell.x + 1, nextcell.y - 1};
        break;
    }
    case MoveDirection::UP_LEFT: {
        nextcell = {nextcell.x - 1, nextcell.y + 1};
        break;
    }
    case MoveDirection::IDLE: {
        printf("Direction debug didn't move\n");
        break;
    }
    }
    if (false) { // not walkable
        times += 1;
        return true; // Dir.pop_back
    } else {
        return false;
    }
}
 */
PathfindingUnit::MoveDirection
PathfindingUnit::getDirByRelativeCells(glm::vec2 currentcell,
                                       glm::vec2 destinationcell) {
    MoveDirection direction;
    int destinationCellX = destinationcell.x;
    int destinationCellY = destinationcell.y;
    int currCellX = currentcell.x;
    int currCellY = currentcell.y;
    // printf("(findNextCellDir)Cell now :{%.d,%.d}\n(find)Cell destination : "
    //     "{%.d,%.d}\n",
    //   currCellX, currCellY, destinationCellX, destinationCellY);

    int xDiff = destinationCellX - currCellX;
    int yDiff = destinationCellY - currCellY;

    if (yDiff == 0) {
        if (xDiff > 0) {
            direction = MoveDirection::RIGHT;
        } else if (xDiff < 0) {
            direction = MoveDirection::LEFT;
        }
    } else if (xDiff == 0) {
        if (yDiff > 0) {
            direction = MoveDirection::UP;
        } else if (yDiff < 0) {
            direction = MoveDirection::DOWN;
        }
    } else if (xDiff == yDiff && xDiff == 0) {
        direction = MoveDirection::IDLE;
    } else {
        if (xDiff > 0 && yDiff > 0) {
            direction = MoveDirection::UP_RIGHT;
        } else if (xDiff > 0 && yDiff < 0) {
            direction = MoveDirection::DOWN_RIGHT;
        } else if (xDiff < 0 && yDiff > 0) {
            direction = MoveDirection::UP_LEFT;
        } else {
            direction = MoveDirection::DOWN_LEFT;
        }
    }

    return direction;
}
/*
void PathfindingUnit::findNextCellDir(MoveDirection lastDir, int times) {
    std::vector<MoveDirection> dictionary = {
        MoveDirection::UP,    MoveDirection::UP_RIGHT,
        MoveDirection::RIGHT, MoveDirection::DOWN_RIGHT,
        MoveDirection::DOWN,  MoveDirection::DOWN_LEFT,
        MoveDirection::LEFT,  MoveDirection::UP_LEFT};
    int index = 0;
    if (times != 0) {
        while (dictionary[index] != lastDir) {
            index++;
        }
        if (index + times > dictionary.size()) {
            times -= dictionary.size();
        }
        direction = dictionary[index + times];
        return;
    }
}
*/
bool PathfindingUnit::walkTowardNextCell() {
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
    if (moveDistance >= 48 * SPEED) {
        moveDistance = 0;
        return true;
    } else
        moveDistance += m_MovementSpeed;
    return false;
}
