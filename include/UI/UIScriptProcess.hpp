//
// Created by nudle on 2024/3/8.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_HPP
#include "Structure/Structure.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "GameObjectID.hpp"
#include <queue>
#include <future>
#include <chrono>
#include "Util/GameObject.hpp"


class UIScriptProcess{
private:
    bool b_Baracks = false;
    bool b_OreRefinery = false;
    bool b_PowerPlants = false;
    bool b_WarFactory = false;
    bool b_ADVPowerPlant = false;
    float TargetTime=0.F;
    float m_CDLeft=0.f;
    unitType m_currentStructure;
    bool b_STALL=false;
    std::deque<unitType> buildQueue;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
public:
    UIScriptProcess(){};
    ~UIScriptProcess(){};
    //
    bool GetIfFinished(unitType type);
    void SetFinished(unitType type);
    void SetUsed(unitType type);
    float GetCDLeft(){ return m_CDLeft;}
    //Event
    void buttonEvent(unitType type);
    void Update();

    //CountDown
    void SetCoolDown(float time);
    void CountDown();
    //transform to ptr
    float GetStructureTime(unitType type);
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
