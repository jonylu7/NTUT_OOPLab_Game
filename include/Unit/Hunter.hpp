//
// Created by nudle on 2024/3/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_HUNTER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_HUNTER_HPP
#include "Avatar.hpp"
#include "Runner.hpp"

#define ATTACK_RANGE 7

class Hunter:public Avatar{
private:
    std::shared_ptr<Runner> m_target;
    glm::vec2 lastTargetCell;

public:
    void setTarget(std::shared_ptr<Runner> m_target){this->m_target=m_target;}
    std::shared_ptr<Util::Image> customizeImage()override{ return std::make_unique<Util::Image>("../assets/sprites/Hunter.png");}
    void customizeUpdate() override;
    void attack(std::shared_ptr<Avatar> attackTarget){};
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_HUNTER_HPP
