//
// Created by 盧威任 on 6/17/24.
//
#include "Mechanics/BuiltStructure.hpp"

void BuiltStructure::UpdateBuiltStructure() {
    // check whether the structure is dead or update
    for (int i = 0; i < m_BuiltStructure.size(); i++) {
        if (m_BuiltStructure[i]->getHealth()->ifDead()) {
            // remove from map
            for (auto a : m_BuiltStructure[i]->getAbsoluteOccupiedArea()) {
                m_Map->removeStrcutureByCellPosition(a);
            }
            // remove  from builtstructure array
            m_BuiltStructure.erase(m_BuiltStructure.begin() + i);
            i--;
        } else {
            m_BuiltStructure[i]->Update();
        }
    }
}

void BuiltStructure::buildNewStructure(std::shared_ptr<Structure> newstruct,
                                       bool force) {
    std::vector<glm::vec2> coords = newstruct->getAbsoluteOccupiedArea();
    if (!force) {
        if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
            // check whehter or not can built at tile
            if (ifCanBuildStructureAtTile(newstruct) == true) {
                m_BuiltStructure.push_back(newstruct);
                m_Map->builtStructureByCellPosition(newstruct, coords);
                newstruct->getStructureOrder()->setStructureOrder(
                    StructureOrderType::BUILT);
            }
        }
    } else {
        m_BuiltStructure.push_back(newstruct);
        m_Map->builtStructureByCellPosition(newstruct, coords);
        newstruct->getStructureOrder()->setStructureOrder(
            StructureOrderType::BUILT);
    }
}

bool BuiltStructure::ifCanBuildStructureAtTile(
    std::shared_ptr<Structure> newstruct) {
    std::vector<glm::vec2> coords = newstruct->getAbsoluteOccupiedArea();
    for (auto i : coords) {
        if (m_Map->getTileByCellPosition(i)->getBuildable() == false) {
            return false;
        }
    }
    return true;
}
