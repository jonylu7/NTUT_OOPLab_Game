//
// Created by 盧威任 on 4/25/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_AVATARMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_AVATARMANAGER_HPP
#include "Avatar/Avatar.hpp"
#include "AvatarNavigator.hpp"
#include "Map/Map.hpp"
#include "NemesisManager.hpp"
#include <unordered_map>
class AvatarManager {
public:
    void AppendAvatar(std::shared_ptr<Avatar> newAvatar) {
        m_AvatarArray.push_back(newAvatar);
        unitArrayAndLocation[newAvatar] = newAvatar->getCurrentCell();
    }

    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        m_Navigator->Start(m_Map);
    }

    void Update() {
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

    void giveOrderToAvatar(std::shared_ptr<Avatar> unit);

    void updateTileWhileAvatarMoving(std::shared_ptr<Avatar> unit) {
        if (unit->ifArrivedAtNextCell()) {
            m_Map->removeAvatarsByCellPosition(unit,
                                               unitArrayAndLocation[unit]);
            m_Map->setAvatarByCellPosition(unit, unit->getCurrentCell());
            unitArrayAndLocation[unit] = unit->getCurrentCell();
        }
    }

    // if given order has enemy

protected:
    std::vector<std::shared_ptr<Avatar>> m_AvatarArray;
    std::unordered_map<std::shared_ptr<Avatar>, glm::vec2> unitArrayAndLocation;

private:
    std::shared_ptr<NemesisManager> m_NemesisManager =
        std::make_shared<NemesisManager>();
    std::shared_ptr<AvatarNavigator> m_Navigator =
        std::make_shared<AvatarNavigator>();
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_AVATARMANAGER_HPP
