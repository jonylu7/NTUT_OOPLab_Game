//
// Created by nudle on 2024/5/2.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
#include "Enemy.hpp"
#include "Mechanics/UnitManager.hpp"

#define SPACE 4

enum class SpawnMode { BUILDINGS,AVATAR};
class EnemyScripts{
private:
    std::shared_ptr<EnemyPlayer> m_Enemy;
    std::shared_ptr<UnitManager> m_GameObjectManager;
    std::shared_ptr<UnitManager> m_EnemyObjectManager;
    std::shared_ptr<MapClass> m_Map;

    glm::vec2 m_baseCell = {20,20};
    int constructCountX = 0;
    int constructCountY = 0;

    float m_buildingCDTime=0;
    float m_AvatarCDTime=0;
    float m_buildingCost = 0.F;
    float m_avatarCost = 0.F;

    UnitType m_selectedBuildingType = UnitType::NONE;
    UnitType m_selectedAvatarType = UnitType::NONE;

    float m_buildDeltaTime = 0;
    float m_avatarDeltaTime = 0;
    float m_mainDeltaTime = 0;
    Util::Time m_Time;
public:
    EnemyScripts(){};
    ~EnemyScripts(){};
    void Start(std::shared_ptr<EnemyPlayer> enemyPlayer,std::shared_ptr<UnitManager> GameObjectManager,std::shared_ptr<UnitManager> EnemyObjectManager,std::shared_ptr<MapClass> map);
    void Update();
    void modeUpdate();
    void  offensiveUpdate(){
        //        if(m_EnemyObjectManager->getOffensiveTroopSize()>0){
        //            m_EnemyObjectManager->setOffensiveTroopAttack(m_GameObjectManager->getMostValuableTarget());
        //        }
    }
    void updateAllTroopStates(){
        //        m_EnemyObjectManager->setAllTroopToAttackMode();
        //        m_EnemyObjectManager->setDefensiveTroopSize(0);
    }

    void setCDTime(float time,SpawnMode spawnMode,bool cheat = true);
    void setCost(float cost,SpawnMode spawnMode);

    bool ifBuiltBasic(){
        return m_Enemy->getUnitConstructCount(UnitType::POWER_PLANT)>=1 && m_Enemy->getUnitConstructCount(UnitType::ORE_REF)>=1 && m_Enemy->getUnitConstructCount(UnitType::BARRACKS)>=1 ;
    }
    bool ifBuiltADV(){
        return m_Enemy->getUnitConstructCount(UnitType::WAR_FACT)>=1 && m_Enemy->getUnitConstructCount(UnitType::ADV_POWER_PLANT)>=1 ;
    }

    void buildBasic();
    void buildADV();
    void spawnUnit();
    void UpdateSpawnScript(SpawnMode spawnMode);
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
