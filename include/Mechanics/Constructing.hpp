//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CONSTRUCTING_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CONSTRUCTING_HPP
#include "Mechanics/StructureArray.hpp"
#include "Structure/Structure.hpp"
class Constructing : public StructureArray {
public:
    Constructing() {}
    virtual ~Constructing() {}
    void
    AddStructSelectingConstructionSite(std::shared_ptr<Structure> newstruct) {
        newstruct->Start();
        m_StructSelectingConstructionSite = newstruct;
        m_IsSelectingConstructionSite = true;
    }

    void SelectdConstructionSite(std::shared_ptr<MapClass> m_Map) {
        if (m_IsSelectingConstructionSite) {
            if (m_StructSelectingConstructionSite->getConstructed()) {
                Append(m_Map, m_StructSelectingConstructionSite);
                m_IsSelectingConstructionSite = false;
            }
            m_StructSelectingConstructionSite->Update();
        }
    }

protected:
    std::shared_ptr<Structure> m_StructSelectingConstructionSite =
        std::make_shared<Structure>();
    bool m_IsSelectingConstructionSite = false;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CONSTRUCTING_HPP
