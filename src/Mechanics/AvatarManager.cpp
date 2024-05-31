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
                assignOrderToMyAvatar(m_AvatarArray[i]);
            }
        }
    }
}

void AvatarManager::assignMoveOrderToAvatar(std::shared_ptr<Avatar> avatar,
                                            glm::vec2 destcell) {
    auto queue =
        m_Navigator->findPath(avatar->getMoving()->getCurrentCell(), destcell);
    avatar->getMoving()->setMovePath(queue);
    avatar->getAvatarOrder()->setAvatarOrder(AvatarOrderType::MOVE);
}

void AvatarManager::assignAttackOrderToAvatar(std::shared_ptr<Avatar> avatar,
                                              glm::vec2 destcell) {
    m_NemesisManager->removeNemesis(avatar);
    if (m_Map->getTileByCellPosition(destcell)->ifEnemyAtTile()) {
        if (m_Map->getTileByCellPosition(destcell)->ifStructureExists()) {
            m_NemesisManager->addNemesis(
                avatar, m_Map->getTileByCellPosition(destcell)->getStructure());
        } else {
            m_NemesisManager->addNemesis(
                avatar,
                m_Map->getTileByCellPosition(destcell)->getAvatars()[0]);
        }
    }
}
void AvatarManager::assignAttackOrderToAvatar(std::shared_ptr<Avatar> avatar,
                                              glm::vec2 destcell,HouseType myHouse) {
    m_NemesisManager->removeNemesis(avatar);
    if (m_Map->getTileByCellPosition(destcell)->ifEnemyAtTile(myHouse)) {
        if (m_Map->getTileByCellPosition(destcell)->ifStructureExists()) {
            m_NemesisManager->addNemesis(
                avatar, m_Map->getTileByCellPosition(destcell)->getStructure());
        } else {
            m_NemesisManager->addNemesis(
                avatar,
                m_Map->getTileByCellPosition(destcell)->getAvatars()[0]);
        }
    }
}

void AvatarManager::assignOrderToMyAvatar(std::shared_ptr<Avatar> avatar) {
    if (avatar->getID().getHouseType() == HouseType::MY) {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {

            auto destcell = MapUtil::GlobalCoordToCellCoord(
                MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));

            assignMoveOrderToAvatar(avatar, destcell);
            assignAttackOrderToAvatar(avatar, destcell);
        }
    }
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
