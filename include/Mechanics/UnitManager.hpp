//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
#include "AvatarNavigator.hpp"
#include "Cursor.hpp"
#include "GameObjectID.hpp"
#include "Mechanics/AvatarManager.hpp"
#include "Mechanics/BuiltStructure.hpp"
#include "Mechanics/CursorSelection.hpp"
#include "Mechanics/Player.hpp"
#include "Mechanics/StructureManager.hpp"
#include <chrono>

#include <utility>

class UnitManager : public Player {
public:
    UnitManager() {}
    ~UnitManager() {}
    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        m_StructureManager->Start(m_Map);

        m_AvatarManager->Start(m_Map);
        m_CursorSelection->Start(m_Map);
        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    void Update() {
        m_StructureManager->Update();
        m_AvatarManager->Update();
        m_CursorSelection->Update();

        // currency update
        std::chrono::high_resolution_clock::time_point m_currentTime =
            std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = m_currentTime - m_StartTime;
        if (elapsed.count() - m_lastElapsed >= 1) { // update every second
            m_lastElapsed = elapsed.count();
        }

        m_StructureManager->SelectingBuildSite();
    }

public:
    int getTotalPower() {
        return Player::getTotalPower(
            *m_StructureManager->getStructureArray()->getBuiltStructureArray());
    }
    std::shared_ptr<AvatarManager> getAvatarManager() {
        return m_AvatarManager;
    }
    std::shared_ptr<StructureManager> getStructureManager() {
        return m_StructureManager;
    }

private:
    std::shared_ptr<CursorSelection> m_CursorSelection =
        std::make_shared<CursorSelection>();
    std::shared_ptr<StructureManager> m_StructureManager =
        std::make_shared<StructureManager>();
    std::shared_ptr<AvatarManager> m_AvatarManager =
        std::make_shared<AvatarManager>();
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::chrono::high_resolution_clock::time_point m_StartTime;
    double m_lastElapsed = 0.F;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
