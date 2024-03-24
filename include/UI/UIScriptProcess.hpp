//
// Created by nudle on 2024/3/8.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_HPP
#include "GameObjectID.hpp"
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
    // building
    bool b_Baracks = false;
    bool b_OreRefinery = false;
    bool b_PowerPlants = false;
    bool b_WarFactory = false;
    bool b_ADVPowerPlant = false;

    float TargetTime = 0.F;
    unitType m_currentStructure;
    bool b_STALL = false;
    std::deque<unitType> buildQueue;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    std::chrono::time_point<std::chrono::high_resolution_clock>
        m_CountDownCurrentTime;
    // building end

    // avatar
    bool b_readytoSpawn = false;
    float m_SpawnTime = 0.F;
    unitType m_currentAvatar;
    bool b_spawnInCD= false;
    std::deque<unitType> m_spawnQueue;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_SpawnStartTime;
    // avatar end

public:
    UIScriptProcess(){};
    ~UIScriptProcess(){};
    //
    bool GetIfFinished(unitType type);
    // if b_Stall==false not currently building
    // true currently is building
    void SetSTALL(bool value) { b_STALL = value; };
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
    void SetCountDown(float time);
    void SetSpawnCountDown(float time);
    void CountDown();
    // transform to ptr
    float GetStructureTime(unitType type);
    float GetSpawnTime(unitType type);

    unitType GetCurrentStructure() { return m_currentStructure; };

    // spawn unit
    std::shared_ptr<Avatar> spawnAvatar();
    bool getIfReadytoSpawn(){return b_readytoSpawn;}
    void setIfReadytoSpawn(bool b){b_readytoSpawn=b;}

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
