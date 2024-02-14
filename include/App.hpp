#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include <ctime>
#include "Barracks.hpp"
#include "Capybara.hpp"
#include "Giraffe.hpp"
#include "Structure.hpp"
#include "Triangle.hpp"
#include "Infantry.hpp"
#include "Cell.hpp"
#include "Rectangle.hpp"
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

    std::time_t How_long_has_passed(){
        return std::time(0)-initialTime;
    }

private:
    State m_CurrentState = State::START;
    //Triangle m_Triangle;
    Rectangle rect;
    std::shared_ptr<Util::GameObject> m_Giraffe= std::make_shared<Giraffe>();
    std::shared_ptr<Util::GameObject> m_Capybara=std::make_shared<Capybara>();
    std::shared_ptr<Util::GameObject> m_Barracks=std::make_shared<Barracks>();
    std::shared_ptr<Structure> m_Structure=std::make_shared<Structure>();
    std::shared_ptr<Infantry> m_Inf=std::make_shared<Infantry>();

    glm::vec2 CameraStartingPosition=glm::vec2(0.F,0.F);
    glm::vec2 CameraPosition=CameraStartingPosition;
    float CameraZoom=0.F;
    float CameraMovingSpeed=0.5F;
    float CameraZoomingSpeed=0.5F;

    std::time_t initialTime=std::time(0);
    CellClass cellTest;



};

#endif
