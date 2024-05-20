//
// Created by 盧威任 on 5/20/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UNIT_HPP
#include "Unit/Health.hpp"
#include "pch.hpp"
class Huntable {
public:
    Huntable() {}
    virtual ~Huntable() {}

public:
    virtual void setOrderNoOrder() = 0;
    virtual void setOrderTakenDamage() = 0;
    virtual glm::vec2 getCurrentLocationInCell() = 0;
    virtual std::shared_ptr<Health> getHealth() = 0;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UNIT_HPP
