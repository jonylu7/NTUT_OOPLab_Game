//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREARRAY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREARRAY_HPP
#include "Structure/Structure.hpp"
#include "pch.hpp"
class StructureArray {
public:
    StructureArray() {}
    virtual ~StructureArray() {}

    void Built(std::shared_ptr<MapClass> m_Map,
               std::shared_ptr<Structure> newstruct) {
        m_BuiltStructure.push_back(newstruct);
        std::vector<glm::vec2> coords = newstruct->GetAbsoluteOccupiedArea();
        m_Map->builtStructureByCellPosition(newstruct, coords);
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
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREARRAY_HPP
