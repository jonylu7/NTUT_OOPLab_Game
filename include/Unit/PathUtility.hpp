//
// Created by 盧威任 on 4/1/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PATHUTILITY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PATHUTILITY_HPP
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

class PathUtility {
public:
    static glm::vec2 getNextCellByCurrent(MoveDirection currentdir,
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

    static MoveDirection getDirByRelativeCells(glm::vec2 currentcell,
                                               glm::vec2 destinationcell) {
        MoveDirection direction;
        int destinationCellX = destinationcell.x;
        int destinationCellY = destinationcell.y;
        int currCellX = currentcell.x;
        int currCellY = currentcell.y;
        printf("(findNextCellDir)Cell now :{%.d,%.d}\n(find)Cell destination : "
               "{%.d,%.d}\n",
               currCellX, currCellY, destinationCellX, destinationCellY);
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
        return direction;
    }
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PATHUTILITY_HPP
