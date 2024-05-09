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

    void buildNewStructure(std::shared_ptr<MapClass> m_Map,
                           std::shared_ptr<Structure> newstruct,bool force=false) {
        std::vector<glm::vec2> coords = newstruct->GetAbsoluteOccupiedArea();
        if(!force){
            if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
                if (ifCanBuildStructureAtTile(m_Map, newstruct) == true) {
                    m_BuiltStructure.push_back(newstruct);
                    m_Map->builtStructureByCellPosition(newstruct, coords);
                    newstruct->setStructOrder(
                        StructureOrder::StructureOrderType::BUILT);
                }
            }
        }else{
            m_BuiltStructure.push_back(newstruct);
            m_Map->builtStructureByCellPosition(newstruct, coords);
            newstruct->setStructOrder(
                StructureOrder::StructureOrderType::BUILT);
        }
    }

    bool ifCanBuildStructureAtTile(std::shared_ptr<MapClass> m_Map,
                                   std::shared_ptr<Structure> newstruct) {
        std::vector<glm::vec2> coords = newstruct->GetAbsoluteOccupiedArea();
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
        for (auto pair : m_BuiltStructure) {
            pair->Start();
        }
    }

    void UpdateBuiltStructure() {
        for (auto pair : m_BuiltStructure) {
            pair->Update();
        }
    }
    void add(std::shared_ptr<Structure> structure) {
        m_BuiltStructure.push_back(structure);
    }

    void updateAvatarSpawnLocation(std::vector<std::shared_ptr<Structure>> structure){
        for(auto i:structure){
            if(std::dynamic_pointer_cast<Barracks>(i)){
                if(i->getHouseType()==HouseType::ENEMY){
                    m_EnemyBarrackCell=i->GetObjectLocation();
                    m_EnemyWayPointCell=std::dynamic_pointer_cast<Barracks>(i)->GetWayPointLocation();
                } else{
                    m_PlayerBarrackCell=i->GetObjectLocation();
                    m_PlayerWayPointCell=std::dynamic_pointer_cast<Barracks>(i)->GetWayPointLocation();
                }
            }
        }
    }

    glm::vec2 getEnemyBarrackCell(){return m_EnemyBarrackCell;}
    glm::vec2 getEnemyWayPointCell(){return m_EnemyWayPointCell;}
    glm::vec2 getPlayerBarrackCell(){return m_PlayerBarrackCell;}
    glm::vec2 getPlayerWayPointCell(){return m_PlayerWayPointCell;}

protected:
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
    glm::vec2 m_EnemyBarrackCell={-1,-1};
    glm::vec2 m_EnemyWayPointCell={-1,-1};
    glm::vec2 m_PlayerBarrackCell={-1,-1};
    glm::vec2 m_PlayerWayPointCell={-1,-1};
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
