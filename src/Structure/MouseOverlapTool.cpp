//
// Created by nudle on 2024/3/5.
//

#include "Structure/MouseOverlapTool.h"

bool MouseOverlapTool::ifObjectClicked(
    glm::vec2 objPos /*,glm::vec2 objSize*/) {
    glm::vec2 mousPos =
        MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition());
    // return (mousPos.x<objPos.x+objSize.x) && (mousPos.x>objPos.x-objSize.x)
    // && (mousPos.y>objPos.y-objSize.y) && (mousPos.y<objPos.y-objSize.y);
    mousPos = MapUtil::GlobalCoordToCellCoord(mousPos);
    objPos = MapUtil::GlobalCoordToCellCoord(objPos);
    return (mousPos == objPos);
}
