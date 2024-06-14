//
// Created by 盧威任 on 5/25/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WUI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WUI_HPP
#include "Button.hpp"
#include "UI/UI.hpp"
class WonUI : public UI {
public:
    WonUI() {}
    ~WonUI() {}
    void Update() override {
        if (m_ContinueButton->ifClicked()) {
            m_UIStatus->setUIStatusType(UIStatusType::UI_RESTART);
        } else if (m_ExitButton->ifClicked()) {
            m_UIStatus->setUIStatusType(UIStatusType::UI_EXIT);
        }
        Draw();
    }

    void Draw() override {
        m_PausedImage->Draw(
            Util::Transform({glm::vec2(0, 70), float(0), glm::vec2(0.8, 0.8)}),
            1);
        m_ContinueButton->Draw();
        m_ExitButton->Draw();
    }

    void setPausedImage(std::shared_ptr<Util::Image> image) {
        m_PausedImage = image;
    }

private:
    std::shared_ptr<Util::Image> m_PausedImage =
        std::make_shared<Util::Image>("../assets/images/PlayerWon.png");

    std::shared_ptr<Button> m_ContinueButton = std::make_shared<Button>(
        std::make_shared<Util::Image>("../assets/images/restart.png"), 1, true,
        Util::Transform({glm::vec2(300, -100), float(0), glm::vec2(0.4, 0.4)}));

    std::shared_ptr<Button> m_ExitButton = std::make_shared<Button>(
        std::make_shared<Util::Image>("../assets/images/exit.png"), 1, true,
        Util::Transform(
            {glm::vec2(-300, -100), float(0), glm::vec2(0.4, 0.4)}));
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WUI_HPP
