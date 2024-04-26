//
// Created by nudle on 2024/3/8.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_HPP
#include "Mechanics/GameObjectID.hpp"
#include "Mechanics/GameObjectManager.hpp"
#include "Mechanics/Player.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/Structure.hpp"
#include "Structure/WarFactory.hpp"
#include "Unit/Avatar.hpp"
#include "Unit/Infantry.hpp"
#include "Util/GameObject.hpp"
#include <chrono>
#include <future>
#include <queue>

class UIScriptProcess {
private:
    std::shared_ptr<GameObjectManager> m_gameObjectManager;

    // building
    bool b_Baracks = false;
    bool b_OreRefinery = false;
    bool b_PowerPlants = false;
    bool b_WarFactory = false;
    bool b_ADVPowerPlant = false;

    float m_buildCoolDownTime = 0.F;
    float m_offPowerBuildCoolDownTime = 0.F;
    unitType m_currentStructureType;
    bool b_isBuildingInCoolDown = false;
    std::deque<unitType> m_buildQueue;
    std::chrono::time_point<std::chrono::high_resolution_clock>
        m_buildStartTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_buildTempTime;
    std::chrono::time_point<std::chrono::high_resolution_clock>
        m_currentCountDownTime;
    float m_lastBuildElapsed = 0.F;
    int m_currentBuildRemainingCost = 0;
    // building end

    // avatar
    bool b_isReadyToSpawn = false;
    float m_spawnCoolDownTime = 0.F;
    float m_offPowerSpawnCoolDownTime = 0.F;
    unitType m_currentInfType;
    bool b_isSpawningInCooldown = false;
    std::deque<unitType> m_spawnQueue;
    std::chrono::time_point<std::chrono::high_resolution_clock>
        m_SpawnStartTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_SpawnTempTime;
    float m_lastSpawnElapsed = 0.F;
    int m_currentSpawnRemainingCost = 0;
    // avatar end

public:
    UIScriptProcess(){};
    ~UIScriptProcess(){};

    // Getter/Setter
    bool GetIfFinishedBuilding(unitType type);
    int GetObjCost(unitType type);
    // if b_isBuildingInCoolDown==false not currently building
    // true currently is building
    void SetSTALL(bool value) { b_isBuildingInCoolDown = value; };
    /*
     * false for used, true for finished
     */
    void SetIfFinished(unitType type, bool value);
    float GetCDLeft();
    std::string GetFormattedCD();

    // Event
    void AddToBuildQueue(unitType type);
    void AddToSpawnQueue(unitType type);
    void Update(bool queueContinue);

    // CountDown
    void SetBuildCountDown(float time);
    void SetSpawnCountDown(float time);
    float GetBuildCountDownTime();
    float GetSpawnCountDownTime();
    void CountDown();

    // transform to ptr
    float GetStructureTime(unitType type);
    float GetSpawnTime(unitType type);

    unitType GetCurrentStructure() { return m_currentStructureType; };
    unitType GetCurrentInfType() { return m_currentInfType; };
    // spawn unit
    std::shared_ptr<Avatar> spawnAvatar();
    bool getIfReadytoSpawn() { return b_isReadyToSpawn; }
    void setIfReadytoSpawn(bool b) { b_isReadyToSpawn = b; }

    // import from scene
    void
    importGameObjManager(std::shared_ptr<GameObjectManager> gameObjectManager) {
        m_gameObjectManager = gameObjectManager;
    }

private:
    std::shared_ptr<Structure> barracks = std::make_shared<Barracks>();
    std::shared_ptr<Structure> oreRefinery = std::make_shared<OreRefinery>();
    std::shared_ptr<Structure> powerPlant = std::make_shared<PowerPlants>();
    std::shared_ptr<Structure> warFactory = std::make_shared<WarFactory>();
    std::shared_ptr<Structure> advPowerPlant =
        std::make_shared<ADVPowerPlants>();
    std::vector<std::shared_ptr<Structure>> StructureArray = {
        barracks, oreRefinery, powerPlant, warFactory, advPowerPlant,
    };
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_HPP
