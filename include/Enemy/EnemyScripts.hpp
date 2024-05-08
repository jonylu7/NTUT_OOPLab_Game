//
// Created by nudle on 2024/5/2.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
#include "Enemy.hpp"
#include "Mechanics/UnitManager.hpp"

#define SPACE 4
class EnemyScripts {
private:
    std::shared_ptr<EnemyPlayer> m_Enemy;
    std::shared_ptr<UnitManager> m_GameObjectManager;
    std::shared_ptr<MapClass> m_Map;

    glm::vec2 m_baseCell = {20, 20};
    int constructCountX = 0;
    int constructCountY = 0;

    float CDTime = 0;
    std::chrono::high_resolution_clock::time_point m_StartTime;
    double m_lastElapsed = 0.F;

public:
    EnemyScripts(){};
    ~EnemyScripts(){};
    void Start(std::shared_ptr<EnemyPlayer> enemyPlayer,
               std::shared_ptr<UnitManager> GameObjectManager,
               std::shared_ptr<MapClass> map) {
        m_StartTime = std::chrono::high_resolution_clock::now();
        m_Enemy = enemyPlayer;
        m_GameObjectManager = GameObjectManager;
        m_Map = map;
    }
    void Update() {

        std::chrono::high_resolution_clock::time_point m_currentTime =
            std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = m_currentTime - m_StartTime;
        if (elapsed.count() - m_lastElapsed >= CDTime) { // update when CD over
            m_lastElapsed = elapsed.count();
            UpdateSpawnScript();
        }
    }
    void UpdateSpawnScript() {
        /*
        if(m_Enemy->getUnitConstructCount(UnitType::POWER_PLANT)<1 &&
        m_Enemy->getTotalCurrency()> 300){
            m_GameObjectManager->spawn(m_Map,UnitType::POWER_PLANT
        ,HouseType::ENEMY,{m_baseCell.x+constructCountX,m_baseCell.y+constructCountY});
            constructCountX+=SPACE;
            CDTime=15.f*CHEAT;
        }else if(m_Enemy->getUnitConstructCount(UnitType::ORE_REF)<1 &&
        m_Enemy->getTotalCurrency()> 2000){
            m_GameObjectManager->spawn(m_Map,UnitType::ORE_REF
        ,HouseType::ENEMY,{m_baseCell.x+constructCountX,m_baseCell.y+constructCountY});
            constructCountX+=SPACE;
            CDTime=100.f*CHEAT;
        }else if(m_Enemy->getUnitConstructCount(UnitType::BARRACKS)<1 &&
        m_Enemy->getTotalCurrency()> 300){
            m_GameObjectManager->spawn(m_Map,UnitType::BARRACKS
        ,HouseType::ENEMY,{m_baseCell.x+constructCountX,m_baseCell.y+constructCountY});
            constructCountX+=SPACE;
            CDTime=15.f*CHEAT;
        }else if(m_Enemy->getAvatarCount()<=25 && m_Enemy->getTotalCurrency()>
        100){ m_GameObjectManager->spawn(m_Map,UnitType::
        INFANTRY,HouseType::ENEMY); CDTime=5.f*CHEAT; }else
        if(m_Enemy->getUnitConstructCount(UnitType::WAR_FACT)<1 &&
        m_Enemy->getTotalCurrency()> 2000){
            m_GameObjectManager->spawn(m_Map,UnitType::
        WAR_FACT,HouseType::ENEMY,{m_baseCell.x+constructCountX,m_baseCell.y+constructCountY});
            constructCountX+=SPACE;
            CDTime=100.f*CHEAT;
        }else if(m_Enemy->getUnitConstructCount(UnitType::ADV_POWER_PLANT)<1 &&
        m_Enemy->getTotalCurrency()> 500){
            m_GameObjectManager->spawn(m_Map,UnitType::
        ADV_POWER_PLANT,HouseType::ENEMY,{m_baseCell.x+constructCountX,m_baseCell.y+constructCountY});
            constructCountX+=SPACE;
            CDTime=25.f*CHEAT;
        }

        if(constructCountX>=15){
            constructCountY+=SPACE;
            constructCountX=0;
        }
         */
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
