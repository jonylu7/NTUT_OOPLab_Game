//
// Created by 盧威任 on 5/3/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
#include "Avatar/Avatar.hpp"
#include "Map/MapUtility.hpp"

class NemesisManager {
public:
    NemesisManager() {}
    ~NemesisManager() {}
    void addNemesis(std::shared_ptr<Avatar> avatar,
                    std::shared_ptr<Avatar> nemesis) {
        m_Nemesis[avatar] = nemesis;
    }

    void removeNemesis(std::shared_ptr<Avatar> avatar) {
        if (ifAvatarHasNemesis(avatar)) {
            m_Nemesis.erase(avatar);
        }
    }

    bool ifAvatarHasNemesis(std::shared_ptr<Avatar> avatar) {
        if (m_Nemesis.count(avatar)) {
            return true;
        } else {
            return false;
        }
    }
    bool ifNemesisWithinWeaponRange(std::shared_ptr<Avatar> hunter) {
        if (ifAvatarHasNemesis(hunter) == false) {
            return false;
        }
        if (hunter->getDistance(
                m_Nemesis[hunter]->getMoving()->getCurrentCell()) <=
            hunter->getWeapon()->getFireRange() *
                CELL_SIZE.x) // check with in range
        {
            return true;
        } else {

            return false;
        }
    }

    void Update() {
        for (auto pair : m_Nemesis) {
            auto hunter = pair.first;
            auto prey = pair.second;
            if (ifNemesisWithinWeaponRange(hunter)) {
                hunter->setAvatarOrder(AvatarOrderType::OPEN_FIRE);
                prey->setAvatarOrder(AvatarOrderType::TAKEN_DAMAGE);
                hunter->getAttackAndDamager()->openFireToTarget(prey);
            }

            if (*pair.second->getHealth()->getLivingStatus() ==
                LivingStatus::DEAD) {
                removeNemesis(hunter);
                hunter->setAvatarOrder(AvatarOrderType::NO_ORDER);
                prey->setAvatarOrder(AvatarOrderType::NO_ORDER);
                break;
            }

            if (*pair.first->getHealth()->getLivingStatus() ==
                LivingStatus::DEAD) {
                removeNemesis(hunter);
                hunter->setAvatarOrder(AvatarOrderType::NO_ORDER);
                prey->setAvatarOrder(AvatarOrderType::NO_ORDER);
                break;
            }
        }
    }

private:
    std::unordered_map<std::shared_ptr<Avatar>, std::shared_ptr<Avatar>>
        m_Nemesis;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
