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

            if (m_AvatarArray[i]->getAvatarOrder()->getAvatarOrder() ==
                AvatarOrderType::CHASE) {
                updateTileWhileAvatarMoving(m_AvatarArray[i]);
            }

            if (m_AvatarArray[i]->getAvatarOrder()->getAvatarOrder() ==
                    AvatarOrderType::CHASE &&
                m_AvatarArray[i]->getMoving()->ifMovePathEmpty()) {
                glm::vec2 targetCell =
                    m_NemesisManager->getNemesisCell(m_AvatarArray[i]);
                auto queue = m_Navigator->findPath(
                    m_AvatarArray[i]->getMoving()->getCurrentCell(),
                    targetCell);
                m_AvatarArray[i]->getMoving()->setMovePath(queue);
                m_AvatarArray[i]->getAvatarOrder()->setAvatarOrder(
                    AvatarOrderType::CHASE);
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
    /*
    if (m_Map->getTileByCellPosition(destcell)->ifStructureExists() &&
        m_Map->getTileByCellPosition(destcell)->ifEnemyAtTile()) {
        destcell.x -= 2;
        destcell.y -= 2;
    }
     */
    bool t = false;
    int runlimit = 0;
    while (!m_Map->getTileByCellPosition(destcell)->getWalkable()) {
        if (t) {
            destcell.x -= 1;
        } else {
            destcell.y -= 1;
        }
        t = !(t);
        runlimit += 1;
        if (runlimit > 30 || destcell.x < 0 || destcell.y < 0) {
            break;
        }
    }

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
                                              glm::vec2 destcell,
                                              HouseType myHouse) {
    m_NemesisManager->removeNemesis(avatar);
    bool condition =
        m_Map->getTileByCellPosition(destcell)->ifEnemyAtTile(myHouse);
    if (condition) {
        if (m_Map->getTileByCellPosition(destcell)->ifStructureExists()) {
            m_NemesisManager->addNemesis(
                avatar, m_Map->getTileByCellPosition(destcell)->getStructure());
            auto queue =
                m_Navigator->findPath(avatar->getMoving()->getCurrentCell(),
                                      {destcell.x + 1, destcell.y + 1});
            avatar->getMoving()->setMovePath(queue);
            avatar->getAvatarOrder()->setAvatarOrder(AvatarOrderType::CHASE);
        } else {
            m_NemesisManager->addNemesis(
                avatar,
                m_Map->getTileByCellPosition(destcell)->getAvatars()[0]);
            auto queue = m_Navigator->findPath(
                avatar->getMoving()->getCurrentCell(), destcell);
            avatar->getMoving()->setMovePath(queue);
            avatar->getAvatarOrder()->setAvatarOrder(AvatarOrderType::CHASE);
        }
    }
}

void AvatarManager::assignOrderToMyAvatar(std::shared_ptr<Avatar> avatar) {
    if (avatar->getID().getHouseType() == HouseType::MY) {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {

            auto destcell = MapUtil::GlobalCoordToCellCoord(
                MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
            if (destcell.x < 0 || destcell.y < 0 ||
                destcell.x > m_Map->getWidth()  - 1 ||
                destcell.y > m_Map->getHeight() - 1) {
                return;
            }

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
        if (avatar->getMoving()->getMovePathSize() == 1) {
            findNearestStandableCellWhenFilled(avatar);
        }
    }
}

void AvatarManager::findNearestStandableCellWhenFilled(
    std::shared_ptr<Avatar> avatar) {
    if (avatar->getMoving()->getStandingCorner() == 5) {
        auto cell = avatar->getMoving()->getCurrentCell();
        bool c = false;
        while (m_Map->getTileByCellPosition(cell)->getAvatars().size() >= 5 &&
               cell.x >= 0 && cell.y >= 0) {
            if (c) {
                cell.x -= 1;
            } else {
                cell.y -= 1;
            }
            c = !(c);
        }
        assignMoveOrderToAvatar(avatar, cell);
    }
}

void AvatarManager::AppendAvatar(std::shared_ptr<Avatar> newAvatar) {
    m_AvatarArray.push_back(newAvatar);
    unitArrayAndLocation[newAvatar] = newAvatar->getMoving()->getCurrentCell();
    m_Map->setAvatarByCellPosition(newAvatar,
                                   newAvatar->getMoving()->getCurrentCell());
}
