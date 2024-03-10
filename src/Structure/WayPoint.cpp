//
// Created by nudle on 2024/3/4.
//
#include "Structure/WayPoint.hpp"

void WayPoint::Update([[maybe_unused]] const Util::Transform &transsform) {
    static glm::vec2 dir = {1, 0.5};

    auto &pos = m_Transform.translation;

    m_Transform.scale = {0.5, 0.5};
}
void WayPoint::SetObjectLocation(glm::vec2 location) {
    ChangeToCell(location);
    ObjectLocation = location;
    m_Transform.translation = location;
}
glm::vec2 WayPoint::ChangeToCell(glm::vec2 location) {
    int _x = location.x / CELL_SIZE.x;
    int _y = location.y / CELL_SIZE.y;
    return {_x * CELL_SIZE.x, _y * CELL_SIZE.y};
}
