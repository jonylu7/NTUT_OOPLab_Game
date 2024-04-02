//
// Created by nudle on 2024/3/6.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_HIGHLIGHT_H
#define PRACTICALTOOLSFORSIMPLEDESIGN_HIGHLIGHT_H
#include "Util/GameObject.hpp"
class HighLight:public Util::GameObject{
public:
    HighLight(){};
    void SetHLScale(glm::vec2 Scale){m_Transform.scale={Scale.x+0.1,Scale.y+0.1};};
    void SetObjectLocation(glm::vec2 location){m_Transform.translation=location;};
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_HIGHLIGHT_H
