#include "App.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    mapScene.Start();
    m_CurrentState = App::State::UPDATE;
}

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    mapScene.Update();

}

void App::End() { // NOLINT(this method will mutate members in the future)

    LOG_TRACE("End");
}
