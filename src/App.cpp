#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    m_Giraffe->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
    m_Giraffe->SetZIndex(5);
    m_Giraffe->Start();

    auto gf = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 500,
                                            "Giraffe");
    gf->SetZIndex(m_Giraffe->GetZIndex() - 1);
    gf->Start();
    m_Giraffe->AppendChild(gf);

    m_Capybara->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
    m_Capybara->Start();

    m_CurrentState = State::UPDATE;

}

void App::Update() {
    if (Util::Input::IsLButtonPressed()) {
        LOG_DEBUG("Left button pressed");
    }
    if (Util::Input::IsRButtonPressed()) {
        LOG_DEBUG("Right button pressed");
    }
    if (Util::Input::IsMButtonPressed()) {
        LOG_DEBUG("Middle button pressed");
    }
    if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    }
    if (Util::Input::IsMouseMoving()) {
        LOG_DEBUG("Mouse moving! x:{}, y{}", Util::Input::GetCursorPosition().x, Util::Input::GetCursorPosition().y);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        LOG_DEBUG("A");
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
        LOG_DEBUG("B");
        Util::Input::SetCursorPosition({0.0F, 0.0F});
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)){
        LOG_DEBUG("Left");
    }

    if(Util::Input::IsKeyPressed(Util::Keycode::UP)){
        LOG_DEBUG("UP");
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)){
        LOG_DEBUG("RIght");
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::DOWN)){
        LOG_DEBUG("Down");
    }

    //m_Giraffe->Update();
    m_Capybara->Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
