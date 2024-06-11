//
// Created by 盧威任 on 5/25/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MENUUI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MENUUI_HPP
#include "Button.hpp"
#include "UI/UI.hpp"
class MenuUI : public UI {
public:
    MenuUI() {}
    ~MenuUI() {}
    void Update() override {
        if (m_StartButton->ifClicked()) {
            m_UIStatus->setUIStatusType(UIStatusType::UI_START);
        } else if (m_ExitButton->ifClicked()) {
            m_UIStatus->setUIStatusType(UIStatusType::UI_EXIT);
        }
        Draw();
    }

    void Draw() override {
        m_BackgroundImage->Draw(
            Util::Transform({glm::vec2(0, 0), float(0), glm::vec2(0.68, 0.68)}),
            0.1);
        m_Title->Draw(
            Util::Transform({glm::vec2(0, 40), float(0), glm::vec2(0.6, 0.6)}),
            1);
        m_StartButton->Draw();
        m_ExitButton->Draw();
    }

private:
    std::shared_ptr<Util::Image> m_Title =
        std::make_shared<Util::Image>("../assets/images/cnc_title.png");
    std::shared_ptr<Util::Image> m_BackgroundImage =
        std::make_shared<Util::Image>("../assets/images/menu_image.png");
    std::shared_ptr<Button> m_StartButton = std::make_shared<Button>(
        std::make_shared<Util::Image>("../assets/images/start.png"), 1, true,
        Util::Transform({glm::vec2(0, -100), float(0), glm::vec2(0.4, 0.4)}));

    std::shared_ptr<Button> m_ExitButton = std::make_shared<Button>(
        std::make_shared<Util::Image>("../assets/images/exit.png"), 1, true,
        Util::Transform({glm::vec2(0, -160), float(0), glm::vec2(0.4, 0.4)}));
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MENUUI_HPP
