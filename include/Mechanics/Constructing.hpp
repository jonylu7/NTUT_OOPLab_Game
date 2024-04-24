//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CONSTRUCTING_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CONSTRUCTING_HPP
#include "Mechanics/StructureArray.hpp"
#include "Structure/Structure.hpp"
class Constructing : public StructureArray {
public:
    Constructing(std::shared_ptr<MapClass> map)
        : StructureArray(map) {}
    virtual ~Constructing() {}
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
    void SetOccupiedAreaUnbuildable(std::shared_ptr<Structure> structure) {
        for (auto i : structure->GetAbsoluteOccupiedArea()) {
            m_Map->getTileByCellPosition(i)->setBuildable(false);
            m_Map->getTileByCellPosition(i)->setWalkable(false);
        }
    }

protected:
    std::shared_ptr<Structure> m_StructSelectingConstructionSite =
        std::make_shared<Structure>();
    bool m_IsSelectingConstructionSite = false;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CONSTRUCTING_HPP
