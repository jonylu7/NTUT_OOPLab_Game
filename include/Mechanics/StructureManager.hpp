//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREMANAGER_HPP
#include "Mechanics/BuiltStructure.hpp"
class StructureManager {
#include "Structure/Structure.hpp"
public:
    StructureManager() {}
    virtual ~StructureManager() {}

    void Start() { m_StructureArray.StartBuiltStructure(); }
    void Update() { m_StructureArray.UpdateBuiltStructure(); }

    void AddStructSelectingBuiltSite(std::shared_ptr<Structure> newstruct) {
        newstruct->Start();
        m_StructSelectingConstructionSite = newstruct;
        // m_IsSelectingConstructionSite = true;
    }

    void SelectdBuiltSite(std::shared_ptr<MapClass> m_Map) {
        if (m_StructSelectingConstructionSite->getBuilt()) {
            m_StructureArray.buildNewStructure(
                m_Map, m_StructSelectingConstructionSite);
        }
        m_StructSelectingConstructionSite->Update();
    }
    BuiltStructure getStructureArray() { return m_StructureArray; }

protected:
    BuiltStructure m_StructureArray;
    std::shared_ptr<Structure> m_StructSelectingConstructionSite =
        std::make_shared<Structure>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREMANAGER_HPP
