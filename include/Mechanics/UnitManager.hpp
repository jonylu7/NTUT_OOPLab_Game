//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
#include "Cursor.hpp"
#include "FindValidPathToDest.hpp"
#include "GameObjectID.hpp"
#include "Mechanics/AvatarManager.hpp"
#include "Mechanics/CursorSelection.hpp"
#include "Mechanics/Player.hpp"
#include "Mechanics/StructureArray.hpp"
#include "Mechanics/StructureManager.hpp"
#include <chrono>

#include <utility>

class UnitManager : public Player {
public:
    UnitManager() {}
    ~UnitManager() {}
    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        m_StructureManager.Start();

        m_AvatarManager.Start(m_Map);

        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    void Update() {
        m_StructureManager.Update();
        m_AvatarManager.Update();

        m_CursorSelection.CursorSelect(m_Map);

        // currency update
        std::chrono::high_resolution_clock::time_point m_currentTime =
            std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = m_currentTime - m_StartTime;
        if (elapsed.count() - m_lastElapsed >= 1) { // update every second
            m_lastElapsed = elapsed.count();
        }

        m_StructureManager.SelectdBuiltSite(m_Map);
    }

public:
    int getTotalPower() {
        return Player::getTotalPower(
            m_StructureManager.getStructureArray().getBuiltStructureArray());
    }
    AvatarManager getAvatarManager() { return m_AvatarManager; }
    StructureManager getStrucutreManager() { return m_StructureManager; }

private:
    CursorSelection m_CursorSelection;
    StructureManager m_StructureManager;
    AvatarManager m_AvatarManager;
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::chrono::high_resolution_clock::time_point m_StartTime;
    double m_lastElapsed = 0.F;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
