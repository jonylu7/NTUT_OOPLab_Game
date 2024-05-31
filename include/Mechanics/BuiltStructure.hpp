//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
#include "Structure/Barracks.hpp"
#include "Structure/Structure.hpp"
#include "pch.hpp"

class BuiltStructure {
public:
    BuiltStructure() {}
    virtual ~BuiltStructure() {}
    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        StartBuiltStructure();
    }
    void buildNewStructure(std::shared_ptr<Structure> newstruct,
                           bool force = false) {
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

    bool ifCanBuildStructureAtTile(std::shared_ptr<Structure> newstruct) {
        std::vector<glm::vec2> coords = newstruct->getAbsoluteOccupiedArea();
        for (auto i : coords) {
            if (m_Map->getTileByCellPosition(i)->getBuildable() == false) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::shared_ptr<Structure>> *getBuiltStructureArray() {
        return &m_BuiltStructure;
    }

    void StartBuiltStructure() {
        for (auto structure : m_BuiltStructure) {
            structure->Start();
        }
    }

    void UpdateBuiltStructure() {
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
    void add(std::shared_ptr<Structure> structure) {
        m_BuiltStructure.push_back(structure);
    }

    void updateAvatarSpawnLocation() {
        for (auto i : m_BuiltStructure) {
            if (std::dynamic_pointer_cast<Barracks>(i)) {
                m_PlayerBarrackCell = MapUtil::GlobalCoordToCellCoord(i->GetObjectLocation());
                m_PlayerWayPointCell =MapUtil::GlobalCoordToCellCoord(
                    std::dynamic_pointer_cast<Barracks>(i)
                        ->GetWayPointLocation());
                int count = 0;
                int offsetX = 1,offsetY=1;
                while(m_Map->getTileByCellPosition(m_PlayerWayPointCell)->getAvatars().size()>=4){
                    offsetX = (rand() % 7*(count/5)) - 3*(count/5);
                    offsetY = (rand() % 7*(count/5)) - 3*(count/5);
                    count++;
                    std::dynamic_pointer_cast<Barracks>(i)->SetWayPointLocationByCellCoord({m_PlayerWayPointCell.x+offsetX,m_PlayerWayPointCell.y+offsetY});
                    m_PlayerWayPointCell =MapUtil::GlobalCoordToCellCoord(
                        std::dynamic_pointer_cast<Barracks>(i)
                            ->GetWayPointLocation());
                }
            }
        }
    }

    glm::vec2 getPlayerBarrackCell() { return {m_PlayerBarrackCell.x-1,m_PlayerBarrackCell.y-1}; }
    glm::vec2 getPlayerWayPointCell() { return m_PlayerWayPointCell; }

private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
    glm::vec2 m_PlayerBarrackCell = {-1, -1};
    glm::vec2 m_PlayerWayPointCell = {-1, -1};
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
