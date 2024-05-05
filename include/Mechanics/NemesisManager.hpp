//
// Created by 盧威任 on 5/3/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
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
    bool ifNemesisWithinWeaponRange(std::shared_ptr<Avatar> avatar) {
        if (ifAvatarHasNemesis(avatar) == false) {
            return false;
        }
        if (1 == 0) // with in range
        {
            return true;
        } else {
            return false;
        }
    }

    void Update() {
        for (auto pair : m_Nemesis) {
            if (ifNemesisWithinWeaponRange(pair.first)) {
                pair.first->setAvatarOrder(AvatarOrderType::OPEN_FIRE);
                pair.second->setAvatarOrder(AvatarOrderType::TAKEN_DAMAGE);
                pair.first->openFireToTarget(pair.second);
            }

            if (pair.second->getLivingStatus() == LivingStatus::DEAD) {
                removeNemesis(pair.first);
                pair.first->setAvatarOrder(AvatarOrderType::NO_ORDER);
                pair.second->setAvatarOrder(AvatarOrderType::NO_ORDER);
            }

            if (pair.first->getLivingStatus() == LivingStatus::DEAD) {
                removeNemesis(pair.first);
                pair.first->setAvatarOrder(AvatarOrderType::NO_ORDER);
                pair.second->setAvatarOrder(AvatarOrderType::NO_ORDER);
            }
        }
    }

private:
    std::unordered_map<std::shared_ptr<Avatar>, std::shared_ptr<Avatar>>
        m_Nemesis;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
