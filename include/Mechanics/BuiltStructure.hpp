//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
#include "Structure/Structure.hpp"
#include "pch.hpp"
class BuiltStructure {
public:
    BuiltStructure() {}
    virtual ~BuiltStructure() {}

    void buildNewStructure(std::shared_ptr<MapClass> m_Map,
                           std::shared_ptr<Structure> newstruct) {
        m_BuiltStructure.push_back(newstruct);
        std::vector<glm::vec2> coords = newstruct->GetAbsoluteOccupiedArea();
        if (ifCanBuildStructureAtTile(m_Map, newstruct) == true) {
            m_Map->builtStructureByCellPosition(newstruct, coords);
        }
    }

    bool ifCanBuildStructureAtTile(std::shared_ptr<MapClass> m_Map,
                                   std::shared_ptr<Structure> newstruct) {
        std::vector<glm::vec2> coords = newstruct->GetAbsoluteOccupiedArea();
        for (auto i : coords) {
            if (m_Map->getTileByCellPosition(i)->getBuildable() == false) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::shared_ptr<Structure>> getBuiltStructureArray() {
        return m_BuiltStructure;
    }

    void StartBuiltStructure() {
        for (auto pair : m_BuiltStructure) {
            pair->Start();
        }
    }

    void UpdateBuiltStructure() {
        for (auto pair : m_BuiltStructure) {
            pair->Update();
        }
    }

protected:
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
