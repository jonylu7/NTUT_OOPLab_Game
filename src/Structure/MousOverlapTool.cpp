//
// Created by nudle on 2024/3/5.
//

#include "Structure/MousOverlapTool.h"


bool MousOverlapTool::checkMous(glm::vec2 objPos/*,glm::vec2 objSize*/) {
    glm::vec2 mousPos=MapClass::ScreenToGlobalCoord(Util::Input::GetCursorPosition());
    //return (mousPos.x<objPos.x+objSize.x) && (mousPos.x>objPos.x-objSize.x) && (mousPos.y>objPos.y-objSize.y) && (mousPos.y<objPos.y-objSize.y);
    mousPos = MapClass::GlobalCoordToCellCoord(mousPos);
    objPos = MapClass::GlobalCoordToCellCoord(objPos);
    return (mousPos==objPos);
}
