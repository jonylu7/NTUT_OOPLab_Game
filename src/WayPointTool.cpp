//
// Created by nudle on 2024/3/5.
//

#include "WayPointTool.h"
#define SIZE 20

bool WayPointTool::checkMous(glm::vec2 objPos, glm::vec2 mousPos) {
    return (mousPos.x<objPos.x+SIZE) && (mousPos.x>objPos.x-SIZE) && (mousPos.y>objPos.y-SIZE) && (mousPos.y<objPos.y-SIZE);
}
