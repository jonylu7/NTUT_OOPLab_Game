//
// Created by 盧威任 on 6/17/24.
//
#include "Mechanics/NemesisManager.hpp"

void NemesisManager::Update() {
    for (auto pair : m_Nemesis) {
        auto hunter = pair.first;
        auto prey = pair.second;
        if (ifNemesisWithinWeaponRange(hunter)) {
            hunter->getAvatarOrder()->setAvatarOrder(
                AvatarOrderType::OPEN_FIRE);
            prey->setOrderTakenDamage();
            hunter->getAttackAndDamage()->openFireToTarget(prey);
        }

        if (pair.second->getHealth()->ifDead()) {
            removeNemesis(hunter);
            hunter->getAvatarOrder()->setAvatarOrder(AvatarOrderType::NO_ORDER);
            prey->setOrderNoOrder();

            break;
        }

        if (*pair.first->getHealth()->getLivingStatus() == LivingStatus::DEAD) {
            removeNemesis(hunter);
            hunter->getAvatarOrder()->setAvatarOrder(AvatarOrderType::NO_ORDER);
            prey->setOrderNoOrder();
            break;
        }
    }
}

bool NemesisManager::ifNemesisWithinWeaponRange(
    std::shared_ptr<Avatar> hunter) {
    if (ifAvatarHasNemesis(hunter) == false) {
        return false;
    }
    if (hunter->getDistance(m_Nemesis[hunter]->getCurrentLocationInCell()) <=
        hunter->getAttackAndDamage()
            ->getWeapon()
            ->getFireRange()) // check with in range
    {
        return true;
    } else {

        return false;
    }
}
