//
// Created by 盧威任 on 5/3/24.
//

#include "Mechanics/AvatarManager.hpp"

void AvatarManager::giveOrderToAvatar(std::shared_ptr<Avatar> unit) {
    FindValidPathToDest m_wayPointAvatar(m_Map);

    auto queue = m_wayPointAvatar.findPath(unit->getCurrentCell(),
                                           unit->getDestinationCell());
    // unit
    unit->setMovePath(queue);
    unit->setNewDestinationIsSetted(false);

    if (m_Map->getTileByCellPosition(unit->getDestinationCell())
            ->ifEnemyAtTile()) {
        m_NemesisManager.addNemesis(
            unit, m_Map->getTileByCellPosition(unit->getDestinationCell())
                      ->getAvatars()[0]);
    } else {
        unit->setAvatarOrder(AvatarOrderType::MOVE);
    }
}
