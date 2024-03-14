//
// Created by nudle on 2024/3/8.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_H
#define PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_H
#include "Structure/Structure.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "UI.hpp"
#include "GameObjectID.hpp"
#include <queue>
#include <future>
#include <chrono>
#include "Util/GameObject.hpp"


class UIScriptProcess{
private:
    bool b_Baracks,b_OreRefinery,b_PowerPlants,b_WarFactory,b_ADVPowerPlant= false;
    float Counter=0.F,TargetTime=0.F;
    bool b_STALL=false;
    std::queue<std::shared_ptr<Structure>> buildQueue;
    std::shared_ptr<Structure> temp_PTR;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
public:
    UIScriptProcess(){};
    //
    bool GetIfFinished(std::shared_ptr<Structure> structure);
    bool GetIfFinished(unitType type);
    void SetFinished(std::shared_ptr<Structure> structure);
    //Event
    void buttonEvent(std::shared_ptr<Structure>(m_Structure));

    void Update();

    //CountDown
    void SetCoolDown(float time);
    void CountDown();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_H
