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

    void Append(std::shared_ptr<MapClass> m_Map,
                std::shared_ptr<Structure> newstruct) {
        m_BuiltStructure.push_back(newstruct);
        m_Map->AppendSelectableObjectByCellPosition(
            MapUtil::GlobalCoordToCellCoord(newstruct->GetObjectLocation()),
            newstruct);
    }

    std::vector<std::shared_ptr<Structure>> getBuiltStructureArray() {
        return m_BuiltStructure;
    }

protected:
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREARRAY_HPP
