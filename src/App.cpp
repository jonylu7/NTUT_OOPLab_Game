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
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
        m_Paused = true;
    }
    if (m_Paused) {
        pausedUpdate();
    } else {
        menuScene.Update();
    }
}

void App::pausedUpdate() {
    m_PausedUI.Update();
    if (m_PausedUI.getUIStatus()->getUIStatusType() == UIStatusType::UI_EXIT) {
        m_CurrentState = State::END;
    }
    if (m_PausedUI.getUIStatus()->getUIStatusType() ==
        UIStatusType::UI_CONTINUE) {
        m_Paused = false;
        m_CurrentState = State::UPDATE;
        m_PausedUI.getUIStatus()->setUIStatusType(UIStatusType::UI_DEFAULT);
    }
}
void App::End() { // NOLINT(this method will mutate members in the future)

    LOG_TRACE("End");
}
