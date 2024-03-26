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
#include "Unit/Avatar.hpp"
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
        for (auto unit : m_UnitArray){
            unit->Update();
            printf("(GOM) update back success\n");
        }
    }

    void Append(std::shared_ptr<Structure> newstruct) {
        newstruct->Start();
        m_BuiltStructure.push_back(newstruct);
    }
    void unitAppend(std::shared_ptr<Avatar> newUnit) {
        m_UnitArray.push_back(newUnit);
        printf("(GOM) push back success\n");
    }

    void RemoveStructByID(const GameObjectID id) {}

    int GetTotalPower() {
        int totalPower = 0;
        for (int i = 0; i < m_BuiltStructure.size(); i++) {
            totalPower += m_BuiltStructure[i]->GetElectricPower();
        }
        return totalPower;
    }

    std::vector<std::shared_ptr<Structure>> getStructureArray(){return m_BuiltStructure;}

private:
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
    std::vector<std::shared_ptr<Avatar>> m_UnitArray;

    std::vector<std::vector<std::shared_ptr<TileClass>>> m_Map;

};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GAMEOBJECTMANAGER_HPP
