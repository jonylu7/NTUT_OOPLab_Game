//
// Created by 盧威任 on 4/25/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_AVATARMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_AVATARMANAGER_HPP
#include "Avatar/Avatar.hpp"
#include <unordered_map>
class AvatarManager {
public:
    void AppendAvatar(std::shared_ptr<Avatar> newAvatar) {
        m_AvatarArray.push_back(newAvatar);
        unitArrayAndLocation[newAvatar] = newAvatar->getCurrentCell();
    }

    void UpdateAvatarArray() {
        for (auto unit : m_AvatarArray) {
            unit->setSelected(true);

            unit->Update();

            if (unit->ifNewDestionationIsSetted()) {
                setNewDestinationForAvatar(unit);
            }
            keepUpdatingAvatarsPosition(unit);
        }
    }

    void setNewDestinationForAvatar(std::shared_ptr<Avatar> unit) {
        FindValidPathToDest m_wayPointAvatar(m_Map);

        auto queue = m_wayPointAvatar.findPath(unit->getCurrentCell(),
                                               unit->getDestinationCell());
        // unit
        unit->setMovePath(queue);
        unit->SetNewDestinationIsSetted(false);

        if (m_Map->getTileByCellPosition(unit->getDestinationCell())
                ->ifEnemyAtTile()) {
            unit->setAvatarOrder(AvatarOrderType::MOVE_ATTACK);
        } else {
            unit->setAvatarOrder(AvatarOrderType::MOVE);
        }
    }

    void keepUpdatingAvatarsPosition(std::shared_ptr<Avatar> unit) {
        if (unit->arrivedAtNextCell()) {
            m_Map->removeAvatarsByCellPosition(unit,
                                               unitArrayAndLocation[unit]);
            m_Map->setAvatarByCellPosition(unit, unit->getCurrentCell());
            unitArrayAndLocation[unit] = unit->getCurrentCell();
        }
    }

protected:
    void importmap(std::shared_ptr<MapClass> map) { m_Map = map; }
    std::vector<std::shared_ptr<Avatar>> m_AvatarArray;
    std::unordered_map<std::shared_ptr<Avatar>, glm::vec2> unitArrayAndLocation;

private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_AVATARMANAGER_HPP
