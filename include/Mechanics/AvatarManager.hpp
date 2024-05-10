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
    /*
     * Start AvatagManager, initlize map and navigator
     */
    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        m_Navigator->Start(m_Map);
    }

    /*
     *  Update Manager, call giveordertoavatar and update while avatarmoving"
     */
    void Update();
    void AppendAvatar(std::shared_ptr<Avatar> newAvatar);

public:
    std::vector<std::shared_ptr<Avatar>> getAvatarArray() {
        return m_AvatarArray;
    }
    void forceMove(std::shared_ptr<Avatar> unit,glm::vec2 cell);
protected:
    void giveOrderToAvatar(std::shared_ptr<Avatar> unit);

    void updateTileWhileAvatarMoving(std::shared_ptr<Avatar> unit);

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
