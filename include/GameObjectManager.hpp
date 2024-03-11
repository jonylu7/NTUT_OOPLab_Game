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
class GameObjectManager {
public:
    GameObjectManager() {}
    ~GameObjectManager() {}
    void Start() {
        for (auto pair : m_StrcutMap) {
            pair.second->Start();
        }
    }
    void Update() {
        for (auto pair : m_StrcutMap) {
            pair.second->Update();
        }
    }

    void Append(std::shared_ptr<Structure> newstruct) {}

    void RemoveStructByID(const GameObjectID id) {
        auto it = m_StrcutMap.find(id);
    }

private:
    std::unordered_map<GameObjectID, std::shared_ptr<Structure>> m_StrcutMap;
    // std::vector<std::shared_ptr<Unit>> m_UnitArray;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
