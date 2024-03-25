//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
#include "GameObjectID.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/Structure.hpp"
#include "Structure/WarFactory.hpp"
#include <unordered_map>
#include <utility>
class GameObjectManager {
public:
    GameObjectManager() {}
    ~GameObjectManager() {}
    void Start() {
        /*
        for (auto pair : m_StrcutMap) {
            pair.second->Start();
            */
        for (auto pair : m_BuiltStructure) {
            pair->Start();
        }
    }
    void Update() {
        for (auto pair : m_BuiltStructure) {
            pair->Update();
        }
    }

    void Append(std::shared_ptr<Structure> newstruct) {
        newstruct->Start();
        m_BuiltStructure.push_back(newstruct);
    }

    void RemoveStructByID(const GameObjectID id) {}

    int GetTotalPower() {
        int totalPower = 0;
        for (int i = 0; i < m_BuiltStructure.size(); i++) {
            totalPower += m_BuiltStructure[i]->GetElectricPower();
        }
        return totalPower;
    }

private:
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
    std::vector<std::vector<std::shared_ptr<TileClass>>> m_Map;
    // std::vector<std::shared_ptr<Unit>> m_UnitArray;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
