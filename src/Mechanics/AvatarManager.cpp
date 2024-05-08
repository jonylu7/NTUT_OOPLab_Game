//
// Created by 盧威任 on 5/3/24.
//

#include "Mechanics/AvatarManager.hpp"

void AvatarManager::Update() {
    for (auto unit : m_AvatarArray) {
        unit->Update();
        if (unit->getAvatarOrder() == AvatarOrderType::MOVE) {
            updateTileWhileAvatarMoving(unit);
        }
        if (unit->getSelected()) {
            giveOrderToAvatar(unit);
        }
    }
}

void AvatarManager::giveOrderToAvatar(std::shared_ptr<Avatar> unit) {

    auto queue = m_Navigator->findPath(unit->getCurrentCell(),
                                       unit->getDestinationCell());
    // unit
    unit->setMovePath(queue);
    unit->setNewDestinationIsSetted(false);

    if (m_Map->getTileByCellPosition(unit->getDestinationCell())
            ->ifEnemyAtTile()) {
        m_NemesisManager->addNemesis(
            unit, m_Map->getTileByCellPosition(unit->getDestinationCell())
                      ->getAvatars()[0]);
    } else {
        unit->setAvatarOrder(AvatarOrderType::MOVE);
    }
}

void AvatarManager::updateTileWhileAvatarMoving(
    std::shared_ptr<Avatar> avatar) {
    if (avatar->ifArrivedAtNextCell()) {
        m_Map->removeAvatarsByCellPosition(avatar,
                                           unitArrayAndLocation[avatar]);
        m_Map->setAvatarByCellPosition(avatar, avatar->getCurrentCell());
        unitArrayAndLocation[avatar] = avatar->getCurrentCell();
    }
}

void AvatarManager::AppendAvatar(std::shared_ptr<Avatar> newAvatar) {
    m_AvatarArray.push_back(newAvatar);
    unitArrayAndLocation[newAvatar] = newAvatar->getCurrentCell();
    m_Map->setAvatarByCellPosition(newAvatar, newAvatar->getCurrentCell());
}
