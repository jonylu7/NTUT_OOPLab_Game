#include "App.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    menuScene.Start();
    m_CurrentState = App::State::UPDATE;
}

void App::Update() {
    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    menuScene.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)

    LOG_TRACE("End");
}
