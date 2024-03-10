//
// Created by nudle on 2024/3/5.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MOUSOVERLAPTOOL_H
#define PRACTICALTOOLSFORSIMPLEDESIGN_MOUSOVERLAPTOOL_H

#include <vector>
#include "glm/glm.hpp"
#include "Util/Input.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Map.hpp"

class MousOverlapTool {
private:
public:
    MousOverlapTool(){};
    ~MousOverlapTool(){};

    static bool checkMous(glm::vec2 objPos/*,glm::vec2 objSize*/);
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MOUSOVERLAPTOOL_H
