//
// Created by 盧威任 on 5/5/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_IHEALTHABLE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_IHEALTHABLE_HPP
#include "Health.hpp"
#include <memory>
class IHealthable {
public:
    virtual std::shared_ptr<Health> getHealth() = 0;
    virtual void setHealth(std::shared_ptr<Health> health) = 0;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_IHEALTHABLE_HPP
