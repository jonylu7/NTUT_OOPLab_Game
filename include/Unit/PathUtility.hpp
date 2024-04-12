//
// Created by 盧威任 on 4/1/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PATHUTILITY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PATHUTILITY_HPP
#include "pch.hpp"
#include <iostream>
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
enum class Side { R, L };

class PathUtility {
public:
    static glm::vec2 getNextCellByCurrent(MoveDirection currentdir,
                                          glm::vec2 currentcell);

    static MoveDirection getDirByRelativeCells(glm::vec2 currentcell,
                                               glm::vec2 destinationcell);
    static MoveDirection
    findNewDirWhenNotTouchedByObstacle(Side side, glm::vec2 currentcell,
                                       MoveDirection currentdir);
    static bool isTouchedByObstacle(Side side, glm::vec2 currentcell,
                                    MoveDirection currentdir);
    static MoveDirection findNewDirWhenCrash(Side side, glm::vec2 currentcell,
                                             MoveDirection currentdir);
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PATHUTILITY_HPP
