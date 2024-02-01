//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP
#include "glm/glm.hpp"
#include "Clickable.hpp"
class button:public Clickable<bool>{
/**
 * member click box
 * member: image
 * Click function
 * Check Cursor Click function (cursor location)
 * **/
private:
glm::vec2 ClickBoxRegionTopL;
glm::vec2 ClickBoxRegionBotR;
//image??
public:
    bool CheckCursorClick(glm::vec2 cursorLocation);
    bool Click() override;


};



#endif // PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP
