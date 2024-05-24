//
// Created by nudle on 2024/5/23.
//
#include "AI/EnemyScripts.hpp"
void EnemyScripts::Start(std::shared_ptr<EnemyPlayer> enemyPlayer,std::shared_ptr<UnitManager> GameObjectManager,std::shared_ptr<UnitManager> EnemyObjectManager,std::shared_ptr<MapClass> map){
    m_Enemy=enemyPlayer;
    m_GameObjectManager=GameObjectManager;
    m_EnemyObjectManager = EnemyObjectManager;
    m_Map=map;
}

void EnemyScripts::Update(){
    m_buildDeltaTime += m_Time.GetDeltaTime();
    m_avatarDeltaTime += m_Time.GetDeltaTime();
    m_mainDeltaTime += m_Time.GetDeltaTime();

    if (m_buildDeltaTime >= m_buildingCDTime) { // update when CD over
        m_buildDeltaTime = 0;
        UpdateSpawnScript(SpawnMode::BUILDINGS);
    }
    if (m_avatarDeltaTime >= m_buildingCDTime) { // update when CD over
        m_avatarDeltaTime = 0;
        UpdateSpawnScript(SpawnMode::AVATAR);
    }

    if(m_mainDeltaTime>=1){
        m_mainDeltaTime=0;
        m_Enemy->addTotalCurrency(m_buildingCost/m_buildingCDTime*(-1.f));
        m_Enemy->addTotalCurrency(m_avatarCost/m_buildingCDTime*(-1.f));
        modeUpdate();
    }

}

void EnemyScripts::modeUpdate(){
    if(!ifBuiltBasic()){
        buildBasic();
    } else{
        if(m_EnemyObjectManager->getTroopSize()==0||(m_GameObjectManager->getTroopSize()/m_EnemyObjectManager->getTroopSize()>=2 && m_GameObjectManager->getTroopSize()!=0)){
            //Defense mode , spawn Troop only
            spawnUnit();
        }else{
            if(m_GameObjectManager->getTroopSize()/m_EnemyObjectManager->getTroopSize()<=0.5){
                //Attack , set all troop to attack mode , set defensive Troop = 0
                updateAllTroopStates();
            }else{
                //Safe now , build adv or spawn troop
                if(!ifBuiltADV()){
                    buildADV();
                    spawnUnit();
                }else{
                    spawnUnit();
                }
            }
        }
    }
    offensiveUpdate();
}

void EnemyScripts::setCDTime(float time,SpawnMode spawnMode,bool cheat){
    if(spawnMode==SpawnMode::AVATAR){
        if(m_EnemyObjectManager->getTotalPower()<=0){
            m_AvatarCDTime = time*2;
        }else{
            m_AvatarCDTime =  time;
        }
    }
    if(spawnMode==SpawnMode::BUILDINGS){
        if(m_EnemyObjectManager->getTotalPower()<=0){
            m_buildingCDTime = time*2;
        }else{
            m_buildingCDTime =  time;
        }
    }

    if(cheat){
        m_AvatarCDTime*=CHEAT;
        m_buildingCDTime*=CHEAT;
    }
}

void EnemyScripts::setCost(float cost,SpawnMode spawnMode){
    if(spawnMode==SpawnMode::AVATAR){
        m_avatarCost=cost;
    }
    if(spawnMode==SpawnMode::BUILDINGS){
        m_buildingCost=cost;
    }
}

void EnemyScripts::buildBasic(){
    if(m_selectedBuildingType!=UnitType::NONE){
        return;
    }
    if(m_Enemy->getUnitConstructCount(UnitType::POWER_PLANT)<1 && m_Enemy->getTotalCurrency()> 300 ){
        setCDTime(15.f,SpawnMode::BUILDINGS);
        setCost(300,SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::POWER_PLANT;
    }else if(m_Enemy->getUnitConstructCount(UnitType::ORE_REF)<1 && m_Enemy->getTotalCurrency()> 2000){
        setCDTime(100.f,SpawnMode::BUILDINGS);
        setCost(2000,SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::ORE_REF;
    }else if(m_Enemy->getUnitConstructCount(UnitType::BARRACKS)<1 && m_Enemy->getTotalCurrency()> 300){
        setCDTime(15.f,SpawnMode::BUILDINGS);
        setCost(300,SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::BARRACKS;
    }
}

void EnemyScripts::buildADV(){
    if(m_selectedBuildingType!=UnitType::NONE){
        return;
    }
    if(m_Enemy->getUnitConstructCount(UnitType::WAR_FACT)<1 && m_Enemy->getTotalCurrency()> 2000){
        setCDTime(100.f,SpawnMode::BUILDINGS);
        setCost(2000,SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::WAR_FACT;
    }else if(m_Enemy->getUnitConstructCount(UnitType::ADV_POWER_PLANT)<1 && m_Enemy->getTotalCurrency()> 500){
        setCDTime(25.f,SpawnMode::BUILDINGS);
        setCost(500,SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::ADV_POWER_PLANT;
    }
}

void EnemyScripts::spawnUnit(){
    if(m_selectedAvatarType!=UnitType::NONE){
        return;
    }
    if(m_Enemy->getAvatarCount()<=25 && m_Enemy->getTotalCurrency()> 100){
        setCDTime(5.f,SpawnMode::AVATAR);
        setCost(100,SpawnMode::AVATAR);
        m_selectedAvatarType = UnitType::INFANTRY;
    }
}

void EnemyScripts::UpdateSpawnScript(SpawnMode spawnMode){
    //issue , avatar spawn and structure spawn should be separated CD time , so can spawn avatar and structure same time

    if(spawnMode == SpawnMode::BUILDINGS){
        if(m_selectedBuildingType == UnitType::NONE){
            return;
        }
        m_GameObjectManager->spawn(m_Map,m_selectedBuildingType ,HouseType::ENEMY,{m_baseCell.x+constructCountX,m_baseCell.y+constructCountY});
        m_Enemy->addUnitConstructCount(m_selectedBuildingType,1);
        setCost(0,SpawnMode::BUILDINGS);
        setCDTime(0.f,SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::NONE;

        if(constructCountX>10){
            constructCountY+=5;
            constructCountX=0;
        }else{
            constructCountX+=5;
        }
    }
    if(spawnMode == SpawnMode::AVATAR) {
        if(m_selectedAvatarType == UnitType::NONE){
            return;
        }
        if(m_selectedAvatarType == UnitType::INFANTRY){
            m_GameObjectManager->spawn(m_Map,m_selectedAvatarType ,HouseType::ENEMY);
            setCost(0,SpawnMode::AVATAR);
            setCDTime(0.f,SpawnMode::AVATAR);
            m_selectedAvatarType = UnitType::NONE;
        }
    }
}