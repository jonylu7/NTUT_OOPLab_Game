//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREARRAY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREARRAY_HPP
#include "Structure/Structure.hpp"
#include "pch.hpp"
class StructureArray {
public:
    StructureArray(std::shared_ptr<MapClass> map)
        : m_Map(map) {}
    virtual ~StructureArray() {}

    void Append(std::shared_ptr<Structure> newstruct) {
        m_BuiltStructure.push_back(newstruct);
        m_Map->AppendSelectableObjectByCellPosition(
            MapUtil::GlobalCoordToCellCoord(newstruct->GetObjectLocation()),
            newstruct);
    }

protected:
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREARRAY_HPP
