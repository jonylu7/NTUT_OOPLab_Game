//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
#include "Cursor.hpp"
#include "FindValidPathToDest.hpp"
#include "GameObjectID.hpp"
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

class GameObjectManager {
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
        }
        for (auto unit : m_UnitArray) {
            unit->Update();
        }

        CursorSelect(&cursorstart, &cursorend);

        // currency update
        std::chrono::high_resolution_clock::time_point m_currentTime =
            std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = m_currentTime - m_StartTime;
        if (elapsed.count() - m_lastElapsed >= 1) { // update every second
            m_lastElapsed = elapsed.count();
            updateTotalCurrency();
        }
        SelectdConstructionSite();
    }

    // Select Unit to take action

    void CursorSelect(glm::vec2 *start, glm::vec2 *end) {

        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            *start = Util::Input::GetCursorPosition();
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
            // clear up last selected
            for (auto i : lastSeletctedObjects) {
                i->setSelected(false);
            }
            lastSeletctedObjects.clear();

            // get cursor position
            *end = Util::Input::GetCursorPosition();

            // select objects
            auto startcell = MapUtil::GlobalCoordToCellCoord(
                MapUtil::ScreenToGlobalCoord(*start));
            auto endcell = MapUtil::GlobalCoordToCellCoord(
                MapUtil::ScreenToGlobalCoord(*end));

            int max_x_cell = std::max(startcell.x, endcell.x);
            int max_y_cell = std::max(startcell.y, endcell.y);
            int min_x_cell = std::min(startcell.x, endcell.x);
            int min_y_cell = std::min(startcell.y, endcell.y);

            for (int i = min_y_cell; i <= max_y_cell; i++) {
                for (int j = min_x_cell; j <= max_x_cell; j++) {
                    auto objects = m_Map->getTileByCellPosition(glm::vec2(j, i))
                                       ->getSelectableObjects();
                    for (auto i : objects) {
                        if (i->getSelected() == false) {
                            i->setSelected(true);
                            lastSeletctedObjects.push_back(i);
                        }
                    }
                }
            }
        }
    }

    void Append(std::shared_ptr<Structure> newstruct) {
        m_BuiltStructure.push_back(newstruct);
        m_Map->AppendSelectableObjectByCellPosition(
            MapUtil::GlobalCoordToCellCoord(newstruct->GetObjectLocation()),
            newstruct);
    }
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

    int GetTotalCurrency() { return m_Player->getTotalCurrency(); }
    void updateTotalCurrency() {
        int totalCurrency = m_Player->getTotalCurrency();
        if (m_BuiltStructure.size() > 0) {
            for (int i = 0; i < m_BuiltStructure.size(); i++) {
                totalCurrency += m_BuiltStructure[i]->GetBuildingIncome();
            }
        }
        m_Player->setTotalCurrency(totalCurrency);
    }

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

    void
    AddStructSelectingConstructionSite(std::shared_ptr<Structure> newstruct) {
        newstruct->Start();
        m_StructSelectingConstructionSite = newstruct;
        m_IsSelectingConstructionSite = true;
    }

    void SelectdConstructionSite() {
        if (m_IsSelectingConstructionSite) {
            if (m_StructSelectingConstructionSite->getConstructed()) {
                Append(m_StructSelectingConstructionSite);
                m_IsSelectingConstructionSite = false;
            }
            m_StructSelectingConstructionSite->Update();
        }
    }

private:
    std::vector<std::shared_ptr<Selectable>> lastSeletctedObjects;
    bool m_IsSelectingConstructionSite = false;
    std::shared_ptr<Structure> m_StructSelectingConstructionSite =
        std::make_shared<Structure>();
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
    std::vector<std::shared_ptr<Avatar>> m_UnitArray;
    FindValidPathToDest m_wayPointUnit;
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<CursorClass> m_Cursor;
    std::chrono::high_resolution_clock::time_point m_StartTime;
    double m_lastElapsed = 0.F;
    glm::vec2 cursorstart;
    glm::vec2 cursorend;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
