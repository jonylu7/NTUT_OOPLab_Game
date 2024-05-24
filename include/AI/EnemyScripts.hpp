//
// Created by nudle on 2024/5/2.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
#include "Enemy.hpp"
#include "Mechanics/UnitManager.hpp"

#define SPACE 4

enum class SpawnMode { BUILDINGS, AVATAR };
<<<<<<< HEAD

=======
>>>>>>> 8575025 (merge ai)
class EnemyScripts {
private:
    std::shared_ptr<EnemyPlayer> m_Enemy;
    std::shared_ptr<UnitManager> m_GameObjectManager;
    std::shared_ptr<UnitManager> m_EnemyObjectManager;
    std::shared_ptr<MapClass> m_Map;

    glm::vec2 m_baseCell = {20, 20};
    int constructCountX = 0;
    int constructCountY = 0;

    float m_buildingCDTime = 0;
    float m_AvatarCDTime = 0;
    float m_buildingCost = 0.F;
    float m_avatarCost = 0.F;

    UnitType m_selectedBuildingType = UnitType::NONE;
    UnitType m_selectedAvatarType = UnitType::NONE;

<<<<<<< HEAD
<<<<<<< HEAD
    UnitType m_selectedUnitType = UnitType::NONE;

=======
    float CDTime = 0;
    std::chrono::high_resolution_clock::time_point m_StartTime;
    double m_lastElapsed = 0.F;
    float m_cost = 0.F;
    int timeStamp = 0;

    UnitType m_selectedUnitType = UnitType::NONE;
=======
    float m_buildDeltaTime = 0;
    float m_avatarDeltaTime = 0;
    float m_mainDeltaTime = 0;
    Util::Time m_Time;
>>>>>>> 8575025 (merge ai)

>>>>>>> bb96505 (merge)

public:
    EnemyScripts(){};
    ~EnemyScripts(){};
    void Start(std::shared_ptr<EnemyPlayer> enemyPlayer,
               std::shared_ptr<UnitManager> GameObjectManager,
               std::shared_ptr<UnitManager> EnemyObjectManager,
               std::shared_ptr<MapClass> map);
    void Update();
    void modeUpdate();
    void offensiveUpdate() {
        //        if(m_EnemyObjectManager->getOffensiveTroopSize()>0){
        //            m_EnemyObjectManager->setOffensiveTroopAttack(m_GameObjectManager->getMostValuableTarget());
        //        }
    }
<<<<<<< HEAD
    void Update() {
        std::chrono::high_resolution_clock::time_point m_currentTime =
            std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = m_currentTime - m_StartTime;
        if (timeStamp >= CDTime) { // update when CD over
            UpdateSpawnScript();
        } else if (elapsed.count() - m_lastElapsed >= 1) {
            m_lastElapsed = elapsed.count();
            timeStamp++;
            m_Enemy->addTotalCurrency(m_cost / CDTime * (-1));
        }
        modeUpdate();
<<<<<<< HEAD
    }
    void modeUpdate() {
        if (!isBuiltBasic()) {
            buildBasic();
        } else {
            if (/*m_GameObjectManager->getTroopSize()/m_EnemyObjectManager->getTroopSize()>=2*/
                0) {
                // Defense mode , spawn Troop only
                spawnUnit();
            } else {
                if (/*m_GameObjectManager->getTroopSize()/m_EnemyObjectManager->getTroopSize()>=0.5*/
                    0) {
                    // Attack , set all troop to attack mode , set defensive
                    // Troop = 0
                    attackModeUpdate();
                } else {
                    // Safe now , build adv or spawn troop
                    if (!isBuiltADV()) {
                        buildADV();
                        spawnUnit();
                    } else {
                        spawnUnit();
                    }
                }
            }
        }
        offensiveUpdate();
=======
    void updateAllTroopStates() {
        //        m_EnemyObjectManager->setAllTroopToAttackMode();
        //        m_EnemyObjectManager->setDefensiveTroopSize(0);
>>>>>>> 8575025 (merge ai)
    }
    void offensiveUpdate() {
        //        if(m_EnemyObjectManager->getOffensiveTroopSize()>0){
        //            m_EnemyObjectManager->setOffensiveTroopAttack(m_GameObjectManager->getMostValuableTarget());
        //        }
    }
    void attackModeUpdate() {
        //        m_EnemyObjectManager->setAllTroopToAttackMode();
        //        m_EnemyObjectManager->setDefensiveTroopSize(0);
=======
    }
    void modeUpdate() {
        if (!isBuiltBasic()) {
            buildBasic();
        } else {
            if (/*m_GameObjectManager->getTroopSize()/m_EnemyObjectManager->getTroopSize()>=2*/
                0) {
                // Defense mode , spawn Troop only
                spawnUnit();
            } else {
                if (/*m_GameObjectManager->getTroopSize()/m_EnemyObjectManager->getTroopSize()>=0.5*/
                    0) {
                    // Attack , set all troop to attack mode , set defensive
                    // Troop = 0
                    attackModeUpdate();
                } else {
                    // Safe now , build adv or spawn troop
                    if (!isBuiltADV()) {
                        buildADV();
                        spawnUnit();
                    } else {
                        spawnUnit();
                    }
                }
            }
        }
        offensiveUpdate();
>>>>>>> bb96505 (merge)
    }

<<<<<<< HEAD
    void setCDTime(float time, bool cheat = true) {
        if (m_Enemy->getTotalPower() <= 0) {
            CDTime = time * 2;
        } else {
            CDTime = time;
        }
        if (cheat) {
            CDTime *= CHEAT;
        }
    }
    void setCost(float cost) { m_cost = cost; }
<<<<<<< HEAD

    bool isBuiltBasic() {
        return m_Enemy->getUnitConstructCount(UnitType::POWER_PLANT) >= 1 &&
               m_Enemy->getUnitConstructCount(UnitType::ORE_REF) >= 1 &&
               m_Enemy->getUnitConstructCount(UnitType::BARRACKS) >= 1;
    }
    bool isBuiltADV() {
        return m_Enemy->getUnitConstructCount(UnitType::WAR_FACT) >= 1 &&
               m_Enemy->getUnitConstructCount(UnitType::ADV_POWER_PLANT) >= 1;
    }

    void buildBasic() {
        if (m_selectedUnitType != UnitType::NONE) {
            return;
        }
        if (m_Enemy->getUnitConstructCount(UnitType::POWER_PLANT) < 1 &&
            m_Enemy->getTotalCurrency() > 300) {
            setCDTime(15.f);
            setCost(300);
            m_selectedUnitType = UnitType::POWER_PLANT;
        } else if (m_Enemy->getUnitConstructCount(UnitType::ORE_REF) < 1 &&
                   m_Enemy->getTotalCurrency() > 2000) {
            setCDTime(100.f);
            setCost(2000);
            m_selectedUnitType = UnitType::ORE_REF;
        } else if (m_Enemy->getUnitConstructCount(UnitType::BARRACKS) < 1 &&
                   m_Enemy->getTotalCurrency() > 300) {
            setCDTime(15.f);
            setCost(300);
            m_selectedUnitType = UnitType::BARRACKS;
        }
    }
    void buildADV() {
        if (m_selectedUnitType != UnitType::NONE) {
            return;
        }
        if (m_Enemy->getUnitConstructCount(UnitType::WAR_FACT) < 1 &&
            m_Enemy->getTotalCurrency() > 2000) {
            setCDTime(100.f);
            setCost(2000);
            m_selectedUnitType = UnitType::WAR_FACT;
        } else if (m_Enemy->getUnitConstructCount(UnitType::ADV_POWER_PLANT) <
                       1 &&
                   m_Enemy->getTotalCurrency() > 500) {
            setCDTime(25.f);
            setCost(500);
            m_selectedUnitType = UnitType::ADV_POWER_PLANT;
        }
    }
    void spawnUnit() {
        if (m_selectedUnitType != UnitType::NONE) {
            return;
        }
        if (m_Enemy->getAvatarCount() <= 25 &&
            m_Enemy->getTotalCurrency() > 100) {
            setCDTime(5.f);
            setCost(100);
            m_selectedUnitType = UnitType::INFANTRY;
        }
    }
    void UpdateSpawnScript() {
        // issue , avatar spawn and structure spawn should be separated CD time
        // , so can spawn avatar and structure same time
        if (m_selectedUnitType == UnitType::NONE) {
            return;
        } else if (m_selectedUnitType == UnitType::INFANTRY) {
            m_GameObjectManager->spawn(m_Map, m_selectedUnitType,
                                       HouseType::ENEMY);
            setCost(0);
            setCDTime(0.f);
            m_selectedUnitType = UnitType::NONE;
        } else {
            m_GameObjectManager->spawn(m_Map, m_selectedUnitType,
                                       HouseType::ENEMY,
                                       {m_baseCell.x + constructCountX,
                                        m_baseCell.y + constructCountY});
            setCost(0);
            setCDTime(0.f);
            m_selectedUnitType = UnitType::NONE;
            if (constructCountX > 10) {
                constructCountY += 3;
                constructCountX = 0;
            } else {
                constructCountX = 0;
            }
        }
=======
=======
    void setCDTime(float time, SpawnMode spawnMode, bool cheat = true);
    void setCost(float cost, SpawnMode spawnMode);
>>>>>>> 8575025 (merge ai)

    bool ifBuiltBasic() {
        return m_Enemy->getUnitConstructCount(UnitType::POWER_PLANT) >= 1 &&
               m_Enemy->getUnitConstructCount(UnitType::ORE_REF) >= 1 &&
               m_Enemy->getUnitConstructCount(UnitType::BARRACKS) >= 1;
    }
    bool ifBuiltADV() {
        return m_Enemy->getUnitConstructCount(UnitType::WAR_FACT) >= 1 &&
               m_Enemy->getUnitConstructCount(UnitType::ADV_POWER_PLANT) >= 1;
>>>>>>> bb96505 (merge)
    }

    void buildBasic();
    void buildADV();
    void spawnUnit();
    void UpdateSpawnScript(SpawnMode spawnMode);
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ENEMYSCRIPTS_HPP
