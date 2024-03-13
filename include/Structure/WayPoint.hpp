//
// Created by nudle on 2024/3/3.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINT_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/TransformUtils.hpp"
class WayPoint : public Util::GameObject {
private:
    glm::vec2 ObjectLocation;

public:
    WayPoint()
        : Util::GameObject() {
        m_Transform.scale = {1, 1};
    };
    void Update(const Util::Transform &transform = Util::Transform()) override;

    void Start() override{
        /*SetDrawable(std::make_unique<Util::Image>("../assets/sprites/flag.png"));*/};
    void SetObjectLocation(glm::vec2 location);
    glm::vec2 GetObjectLocation() { return this->ObjectLocation; }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WAYPOINT_HPP
