//
// Created by 盧威任 on 5/3/24.
//

#include "Mechanics/AvatarManager.hpp"

void AvatarManager::Update() {
    m_NemesisManager->Update();
    for (auto unit : m_AvatarArray) {
        unit->Update();
        if (unit->getAvatarOrder() == AvatarOrderType::MOVE) {
            updateTileWhileAvatarMoving(unit);
        }
        if (unit->getSelected()) {
            giveOrderToMyAvatar(unit);
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
                unit->setAvatarOrder(AvatarOrderType::MOVE);
                m_NemesisManager->addNemesis(
                    unit,
                    m_Map
                        ->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
                            MapUtil::ScreenToGlobalCoord(dest)))
                        ->getAvatars()[0]);
            } else {
                unit->setAvatarOrder(AvatarOrderType::MOVE);
            }
        }
    }
}
void AvatarManager::forceMove(std::shared_ptr<Avatar> unit, glm::vec2 cell) {
    unit->setAvatarOrder(AvatarOrderType::MOVE);
    auto queue =
        m_Navigator->findPath(unit->getMoving()->getCurrentCell(), cell);
    unit->getMoving()->setMovePath(queue);
}

void AvatarManager::updateTileWhileAvatarMoving(
    std::shared_ptr<Avatar> avatar) {
    if (avatar->getMoving()->ifArrivedAtNextCell()) {
        m_Map->removeAvatarsByCellPosition(avatar,
                                           unitArrayAndLocation[avatar]);
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
