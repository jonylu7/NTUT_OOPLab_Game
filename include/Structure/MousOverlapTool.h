//
// Created by nudle on 2024/3/5.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MOUSOVERLAPTOOL_H
#define PRACTICALTOOLSFORSIMPLEDESIGN_MOUSOVERLAPTOOL_H

#include "Map/Map.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Util/Input.hpp"
#include "glm/glm.hpp"
#include <vector>

class MousOverlapTool {
private:
public:
    MousOverlapTool(){};
    ~MousOverlapTool(){};

    static bool checkMous(glm::vec2 objPos /*,glm::vec2 objSize*/);
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MOUSOVERLAPTOOL_H
