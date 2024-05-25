//
// Created by 盧威任 on 5/25/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PAUSEDUI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PAUSEDUI_HPP
#include "Button.hpp"
#include "UIStatus.hpp"
class PausedUI {
public:
    PausedUI() {}
    ~PausedUI() {}
    void Update() {
        if (m_ContinueButton->ifClicked()) {
            m_UIStatus->setUIStatusType(UIStatusType::UI_CONTINUE);
        } else if (m_ExitButton->ifClicked()) {
            m_UIStatus->setUIStatusType(UIStatusType::UI_EXIT);
        }
        Draw();
    }

    void Draw() {
        m_ContinueButton->Draw();
        m_ExitButton->Draw();
    }

public:
    std::shared_ptr<UIStatus> getUIStatus() { return m_UIStatus; }

private:
    std::shared_ptr<UIStatus> m_UIStatus = std::make_shared<UIStatus>();
    std::shared_ptr<Button> m_ContinueButton = std::make_shared<Button>(
        std::make_shared<Util::Image>("../assets/images/continue.png"), 1, true,
        Util::Transform());

    std::shared_ptr<Button> m_ExitButton = std::make_shared<Button>(
        std::make_shared<Util::Image>("../assets/images/exit.png"), 1, true,
        Util::Transform({glm::vec2(10, 10), float(0), glm::vec2(1, 1)}));
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PAUSEDUI_HPP
