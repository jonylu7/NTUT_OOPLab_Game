//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
#include "Cursor.hpp"
#include "FindValidPathToDest.hpp"
#include "GameObjectID.hpp"
#include "Mechanics/Constructing.hpp"
#include "Mechanics/CursorSelection.hpp"
#include "Mechanics/StructureArray.hpp"
#include "Player.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/Structure.hpp"
#include "Structure/WarFactory.hpp"
#include "Unit/Avatar.hpp"
#include <chrono>
#include <unordered_map>
#include <utility>

class GameObjectManager : public Constructing, public CursorSelection {
public:
    GameObjectManager() {}
    ~GameObjectManager() {}
    void Start(std::shared_ptr<MapClass> map, std::shared_ptr<Player> player,
               std::shared_ptr<CursorClass> cursor) {
        m_Map = map;
        m_Player = player;
        m_Cursor = cursor;

        for (auto pair : m_BuiltStructure) {
            pair->Start();
        }
        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    void Update() {

        for (auto pair : m_BuiltStructure) {
            pair->Update();
            SetOccupiedAreaUnbuildable(m_Map, pair);
        }
        for (auto unit : m_UnitArray) {
            unit->Update();
        }

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

    // Select Unit to take action

    void Append(std::shared_ptr<Avatar> newUnit) {
        m_UnitArray.push_back(newUnit);
    }

    void RemoveStructByID(const GameObjectID id) {}

    int GetTotalPower() {
        int totalPower = 0;
        for (int i = 0; i < m_BuiltStructure.size(); i++) {
            totalPower += m_BuiltStructure[i]->GetElectricPower();
        }
        return totalPower;
    }

    float GetTotalCurrency() { return m_Player->getTotalCurrency(); }
    std::vector<std::shared_ptr<Structure>> getStructureArray() {
        return m_BuiltStructure;
    }

    void setNewDestination(glm::vec2 destination) {
        auto queue = m_wayPointUnit.findPath(destination, destination);
    }
    void cursorSetNewDest() {
        // all prevousily selected objects to set
        if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_RB)) {
            this->setNewDestination(
                MapUtil::GlobalCoordToCellCoord(MapUtil::ScreenToGlobalCoord(
                    Util::Input::GetCursorPosition())));
        }
    }

private:
    std::vector<std::shared_ptr<Avatar>> m_UnitArray;
    FindValidPathToDest m_wayPointUnit;
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<CursorClass> m_Cursor;
    std::chrono::high_resolution_clock::time_point m_StartTime;
    double m_lastElapsed = 0.F;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
