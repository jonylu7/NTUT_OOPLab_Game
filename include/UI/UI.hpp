//
// Created by 盧威任 on 5/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#include "UI/UIStatus.hpp"
#include "pch.hpp"
class UI {
public:
    UI() {}
    virtual ~UI(){};
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual std::shared_ptr<UIStatus> getUIStatus() { return m_UIStatus; }

protected:
    std::shared_ptr<UIStatus> m_UIStatus = std::make_shared<UIStatus>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
