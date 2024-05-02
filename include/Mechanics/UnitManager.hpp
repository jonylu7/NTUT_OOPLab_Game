//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
#include "Cursor.hpp"
#include "FindValidPathToDest.hpp"
#include "GameObjectID.hpp"
#include "Mechanics/Constructing.hpp"
#include "Mechanics/CursorSelection.hpp"
#include "Mechanics/Player.hpp"
#include "Mechanics/Spawning.hpp"
#include "Mechanics/StructureArray.hpp"
#include <chrono>

#include <utility>

class UnitManager : public Constructing,
                    public Spawning,
                    public CursorSelection,
                    public Player {
public:
    UnitManager() {}
    ~UnitManager() {}
    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        StartBuiltStructure();
        importmap(m_Map);

        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    void Update() {
        UpdateBuiltStructure();
        UpdateUnitArray();

        CursorSelect(m_Map, &cursorstart, &cursorend);

        // currency update
        std::chrono::high_resolution_clock::time_point m_currentTime =
            std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = m_currentTime - m_StartTime;
        if (elapsed.count() - m_lastElapsed >= 1) { // update every second
            m_lastElapsed = elapsed.count();
        }

        SelectdConstructionSite(m_Map);
    }

public:
    int getTotalPower() {
        return Player::getTotalPower(this->m_BuiltStructure);
    }

private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::chrono::high_resolution_clock::time_point m_StartTime;
    double m_lastElapsed = 0.F;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
