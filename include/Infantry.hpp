//
// Created by 盧威任 on 1/30/24.
//

#ifndef INFANTRY_HPP
#define INFANTRY_HPP
#include "Util/GameObject.hpp"
#include "glm/glm.hpp"

class Infantry : public Util::GameObject {

public:
    enum class updateMode {
        Uncreated,
        MovingToDestination,
        Standing,
        Attacking
    };
    Infantry()
        : Destination(){};
    ~Infantry(){};

    void Update(const Util::Transform &transform = Util::Transform()) override;
    void Start() override { m_Transform.translation = glm::vec2(10.F, 10.F); };
    updateMode GetCurrentUpdateMode() const { return m_CurrentState; };
    void SetCurrentUpdateMode(updateMode mode) { m_CurrentState = mode; };
    void SetObjectLocation(glm::vec2 location) { Destination = location; }

private:
    updateMode m_CurrentState = updateMode::Uncreated;
    glm::vec2 Destination = glm::vec2(0.F, 0.F);
    float DistanceInFrame = 1.F;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
