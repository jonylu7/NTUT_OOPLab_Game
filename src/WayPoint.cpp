//
// Created by nudle on 2024/3/4.
//
#include "WayPoint.hpp"

void WayPoint::Update([[maybe_unused]] const Util::Transform &transsform) {
    static glm::vec2 dir = {1, 0.5};

    auto &pos = m_Transform.translation;


    m_Transform.scale = {0.5, 0.5};

}
void WayPoint::SetObjectLocation(glm::vec2 location){
    ObjectLocation=location;
    m_Transform.translation=ObjectLocation;
}