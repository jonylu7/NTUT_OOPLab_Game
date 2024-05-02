//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREMANAGER_HPP
#include "Mechanics/StructureArray.hpp"
#include "Structure/Structure.hpp"
class StructureManager {
public:
    StructureManager() {}
    virtual ~StructureManager() {}

    void Start() { m_StructureArray.StartBuiltStructure(); }
    void Update() { m_StructureArray.UpdateBuiltStructure(); }

    void AddStructSelectingBuiltSite(std::shared_ptr<Structure> newstruct) {
        newstruct->Start();
        m_StructSelectingConstructionSite = newstruct;
        m_IsSelectingConstructionSite = true;
    }

    void SelectdBuiltSite(std::shared_ptr<MapClass> m_Map) {
        if (m_IsSelectingConstructionSite) {
            if (m_StructSelectingConstructionSite->getBuilt()) {
                m_StructureArray.Built(m_Map,
                                       m_StructSelectingConstructionSite);
                m_IsSelectingConstructionSite = false;
            }
            m_StructSelectingConstructionSite->Update();
        }
    }
    StructureArray getStructureArray() { return m_StructureArray; }

protected:
    StructureArray m_StructureArray;
    std::shared_ptr<Structure> m_StructSelectingConstructionSite =
        std::make_shared<Structure>();
    bool m_IsSelectingConstructionSite = false;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREMANAGER_HPP
