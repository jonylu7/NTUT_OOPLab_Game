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

    void Start(std::shared_ptr<MapClass> map) {
        m_BuiltStructure->Start(map);
        m_Map = map;
    }
    void Update() {

        m_StructSelectingConstructionSite->Update();

        m_BuiltStructure->UpdateBuiltStructure();
    }

    void AddStructSelectingBuiltSite(std::shared_ptr<Structure> newstruct) {
        // selecting site
        newstruct->Start();
        m_StructSelectingConstructionSite = newstruct;

        newstruct->getStructureOrder()->setStructureOrder(
            StructureOrderType::SELECTING_SITE);
    }

    void SelectingBuildSite() {
        // bulit or not
        if (m_StructSelectingConstructionSite->getStructureOrder()
                ->getStructureOrderType() ==
            StructureOrderType::SELECTING_SITE) {
            m_BuiltStructure->buildNewStructure(
                m_StructSelectingConstructionSite);
        }
    }

    std::shared_ptr<BuiltStructure> getStructureArray() {
        return m_BuiltStructure;
    }

    void setBarrackWayPointByCell(glm::vec2 cell){
        m_BuiltStructure->setBarrackWayPointByCell(cell);
    }

protected:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::shared_ptr<BuiltStructure> m_BuiltStructure =
        std::make_shared<BuiltStructure>();
    std::shared_ptr<Structure> m_StructSelectingConstructionSite =
        std::make_shared<Structure>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREMANAGER_HPP
