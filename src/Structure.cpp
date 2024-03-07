//
// Created by 盧威任 on 1/30/24.
//

#include "Structure.hpp"
#include "Util/Input.hpp"
#include "Util/Transform.hpp"
#include "config.hpp"

void Structure::Update([[maybe_unused]] const Util::Transform &transsform) {
    static glm::vec2 dir = {1, 0.5};

    auto &pos = m_Transform.translation;


    m_Transform.scale = {1.F, 1.F};
    switch (m_CurrentState) {
    case (updateMode::Invisidable):
        break;
    case (updateMode::Moveable):
        pos = Util::Input::GetCursorPosition();
        break;
    case (updateMode::Fixed):
        pos = ObjectLocation;
        break;
    }

    // LOG_DEBUG("GIRA: x: {}, y: {}", pos.x, pos.y);
}
/*void Structure::SetTransformation(glm::vec2 newTrans) {
    this->m_Transform=newTrans;
}*/
void Structure::DecreaseHp(float Hp){
    this->buildingHp-=Hp;
}
float Structure::GetElectricPower(){
    return this->electricPower;
}
float Structure::GetBuildingTime(){
    return this->buildingTime;
}
float Structure::GetBuildingCost(){
    return this->buildingCost;
}
float Structure::GetBuildingHp(){
    return this->buildingHp;
}
void Structure::SetObjectLocation(glm::vec2 location) {
    ObjectLocation = location;
    m_Transform.translation=ObjectLocation;
}

