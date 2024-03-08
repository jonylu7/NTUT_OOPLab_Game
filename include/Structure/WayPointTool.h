//
// Created by nudle on 2024/3/5.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTTOOL_H
#define PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTTOOL_H

#include <vector>
#include "glm/glm.hpp"
#include "Util/Input.hpp"
#include "Structure/IWayPointStructure.hpp"
class WayPointTool{
private:
public:
    WayPointTool(){};
    ~WayPointTool(){};

    bool checkMous(glm::vec2 objPos,glm::vec2 mousPos);
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINTTOOL_H
