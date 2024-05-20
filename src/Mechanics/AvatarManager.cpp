//
// Created by 盧威任 on 5/3/24.
//

#include "Mechanics/AvatarManager.hpp"

void AvatarManager::Update() {
    m_NemesisManager->Update();
    for (int i = 0; i < m_AvatarArray.size(); i++) {
        // if dead remove, else update it
        if (m_AvatarArray[i]->getHealth()->ifDead()) {
            // remove from map
            m_Map->removeAvatarByCellPosition(
                m_AvatarArray[i],
                m_AvatarArray[i]->getMoving()->getCurrentCell());
            // remove from array
            m_AvatarArray.erase(m_AvatarArray.begin() + i);
            i--;
        } else {
            m_AvatarArray[i]->Update();

            // update tile while avatar is moving
            if (m_AvatarArray[i]->getAvatarOrder()->getAvatarOrder() ==
                AvatarOrderType::MOVE) {
                updateTileWhileAvatarMoving(m_AvatarArray[i]);
            }

            // give order to avatar
            if (m_AvatarArray[i]->getSelected()) {
                giveOrderToMyAvatar(m_AvatarArray[i]);
            }
        }
    }
}

void AvatarManager::giveOrderToMyAvatar(std::shared_ptr<Avatar> unit) {
    if (unit->getID().getHouseType() == HouseType::MY) {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
            auto dest = Util::Input::GetCursorPosition();
            auto queue =
                m_Navigator->findPath(unit->getMoving()->getCurrentCell(),
                                      MapUtil::GlobalCoordToCellCoord(
                                          MapUtil::ScreenToGlobalCoord(dest)));
            // unit
            unit->getMoving()->setMovePath(queue);

            if (m_Map
                    ->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
                        MapUtil::ScreenToGlobalCoord(dest)))
                    ->ifEnemyAtTile()) {
                unit->getAvatarOrder()->setAvatarOrder(AvatarOrderType::MOVE);
                m_NemesisManager->addNemesis(
                    unit,
                    m_Map
                        ->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
                            MapUtil::ScreenToGlobalCoord(dest)))
                        ->getAvatars()[0]);
            } else {
                m_NemesisManager->removeNemesis(unit);
                unit->getAvatarOrder()->setAvatarOrder(AvatarOrderType::MOVE);
            }
        }
    }
}
void AvatarManager::forceMove(std::shared_ptr<Avatar> unit, glm::vec2 cell) {
    unit->getAvatarOrder()->setAvatarOrder(AvatarOrderType::MOVE);
    auto queue =
        m_Navigator->findPath(unit->getMoving()->getCurrentCell(), cell);
    unit->getMoving()->setMovePath(queue);
}

void AvatarManager::updateTileWhileAvatarMoving(
    std::shared_ptr<Avatar> avatar) {
    if (avatar->getMoving()->ifArrivedAtNextCell()) {
        m_Map->removeAvatarByCellPosition(avatar, unitArrayAndLocation[avatar]);
        m_Map->setAvatarByCellPosition(avatar,
                                       avatar->getMoving()->getCurrentCell());
        unitArrayAndLocation[avatar] = avatar->getMoving()->getCurrentCell();
    }
}

void AvatarManager::AppendAvatar(std::shared_ptr<Avatar> newAvatar) {
    m_AvatarArray.push_back(newAvatar);
    unitArrayAndLocation[newAvatar] = newAvatar->getMoving()->getCurrentCell();
    m_Map->setAvatarByCellPosition(newAvatar,
                                   newAvatar->getMoving()->getCurrentCell());
}
