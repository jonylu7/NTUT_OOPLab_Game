#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Giraffe.hpp"
#include "Capybara.hpp"
#include "Triangle.hpp"
#include "Barracks.hpp"
#include "button.hpp"

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

    Triangle m_Triangle;
    std::shared_ptr<Util::GameObject> m_Giraffe= std::make_shared<Giraffe>();
    std::shared_ptr<Util::GameObject> m_Capybara=std::make_shared<Capybara>();
    std::shared_ptr<Util::GameObject> m_Barracks=std::make_shared<Barracks>();
    std::shared_ptr<Util::GameObject> buttonTest=std::make_shared<button>();
};

#endif
