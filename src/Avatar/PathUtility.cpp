//
// Created by 盧威任 on 4/12/24.
//
#include "Avatar/PathUtility.hpp"

MoveDirection PathUtility::findNewDirWhenNotTouchedByObstacle(
    Side side, glm::vec2 currentcell, MoveDirection currentdir) {
    MoveDirection newdir;
    switch (currentdir) {
    case MoveDirection::RIGHT:
        if (side == Side::R) {
            newdir = MoveDirection::DOWN_RIGHT;
        } else if (side == Side::L) {
            newdir = MoveDirection::UP_RIGHT;
        }
        break;

    case MoveDirection::LEFT:
        if (side == Side::R) {
            newdir = MoveDirection::UP_LEFT;
        } else if (side == Side::L) {
            newdir = MoveDirection::DOWN_LEFT;
        }
        break;

    case MoveDirection::UP:
        if (side == Side::R) {
            newdir = MoveDirection::UP_RIGHT;
        } else if (side == Side::L) {
            newdir = MoveDirection::UP_LEFT;
        }
        break;

    case MoveDirection::DOWN:
        if (side == Side::R) {
            newdir = MoveDirection::DOWN_LEFT;
        } else if (side == Side::L) {
            newdir = MoveDirection::DOWN_RIGHT;
        }
        break;

    case MoveDirection::UP_RIGHT:
        if (side == Side::R) {
            newdir = MoveDirection::RIGHT;
        } else if (side == Side::L) {
            newdir = MoveDirection::UP;
        }
        break;

    case MoveDirection::DOWN_LEFT:
        if (side == Side::R) {
            newdir = MoveDirection::LEFT;
        } else if (side == Side::L) {
            newdir = MoveDirection::DOWN;
        }
        break;

    case MoveDirection::DOWN_RIGHT:
        if (side == Side::R) {
            newdir = MoveDirection::DOWN;
        } else if (side == Side::L) {
            newdir = MoveDirection::RIGHT;
        }
        break;

    case MoveDirection::UP_LEFT:
        if (side == Side::R) {
            newdir = MoveDirection::UP;
        } else if (side == Side::L) {
            newdir = MoveDirection::LEFT;
        }
        break;

    case MoveDirection::IDLE:
        // printf("Direction debug didn't move\n");
        break;
    }
    return newdir;
}

MoveDirection PathUtility::getDirByRelativeCells(glm::vec2 currentcell,
                                                 glm::vec2 destinationcell) {
    MoveDirection direction;
    int destinationCellX = destinationcell.x;
    int destinationCellY = destinationcell.y;
    int currCellX = currentcell.x;
    int currCellY = currentcell.y;
    int xDiff = destinationCellX - currCellX;
    int yDiff = destinationCellY - currCellY;
    int xAbs = abs(xDiff);
    int yAbs = abs(yDiff);
    if (xAbs == 0 && yAbs == 0) {
        direction = MoveDirection::IDLE;
    } else if (xAbs == yAbs) {
        if (xDiff > 0 && yDiff > 0) {
            direction = MoveDirection::UP_RIGHT;
        } else if (xDiff > 0 && yDiff < 0) {
            direction = MoveDirection::DOWN_RIGHT;
        } else if (xDiff < 0 && yDiff > 0) {
            direction = MoveDirection::UP_LEFT;
        } else {
            direction = MoveDirection::DOWN_LEFT;
        }
    } else {
        if (xAbs > yAbs) {
            if (xDiff > 0) {
                direction = MoveDirection::RIGHT;
            } else if (xDiff < 0) {
                direction = MoveDirection::LEFT;
            } else {
                printf("(findNextCellDir)Error Wrong Dir!");
                direction = MoveDirection::IDLE;
            }
        } else {
            if (yDiff > 0) {
                direction = MoveDirection::UP;
            } else if (yDiff < 0) {
                direction = MoveDirection::DOWN;
            } else {
                printf("(findNextCellDir)Error Wrong Dir!");
                direction = MoveDirection::IDLE;
            }
        }
    }
    printf("-----\n(PathUtil)Cell now :{%.d,%.d}\n(PathUtil)Cell destination : "
           "{%.d,%.d}\n(PathUtil)Dir : %s\n-----\n",
           currCellX, currCellY, destinationCellX, destinationCellY,debug_dirToString(direction).c_str());
    return direction;
}
std::string PathUtility::debug_dirToString(MoveDirection dir){
    switch (dir) {
    case MoveDirection::UP:
        return "Up";
    case MoveDirection::UP_RIGHT:
        return "Up Right";
    case MoveDirection::UP_LEFT:
        return "Up Left";
    case MoveDirection::RIGHT:
        return "Right";
    case MoveDirection::LEFT:
        return "Left";
    case MoveDirection::DOWN_RIGHT:
        return "Down Right";
    case MoveDirection::DOWN_LEFT:
        return "Down Left";
    case MoveDirection::DOWN:
        return "Down";
    case MoveDirection::IDLE:
        return "Idle";
    default:
        return "Unknown";
    }
}

glm::vec2 PathUtility::getNextCellByCurrent(MoveDirection currentdir,
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
