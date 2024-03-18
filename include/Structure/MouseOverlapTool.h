//
// Created by nudle on 2024/3/5.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MOUSEOVERLAPTOOL_H
#define PRACTICALTOOLSFORSIMPLEDESIGN_MOUSEOVERLAPTOOL_H

#include <vector>
#include "glm/glm.hpp"
#include "Util/Input.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Map.hpp"

class MouseOverlapTool {
private:
public:
    MouseOverlapTool(){};
    ~MouseOverlapTool(){};

    static bool ifObjectClicked(glm::vec2 objPos/*,glm::vec2 objSize*/);
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MOUSEOVERLAPTOOL_H
