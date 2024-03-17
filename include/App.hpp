#ifndef APP_HPP
#define APP_HPP

#include "Scene/DefaultScene.hpp"
#include "Scene/MapScene.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };
    State GetCurrentState() const { return m_CurrentState; }
    void Start();
    void Update();
    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    State m_CurrentState = State::START;

    DefaultScene testScene;
    MapScene mapScene;
};

#endif
