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
    Util::GameObject m_debug;
    Util::GameObject m_debug1;
public:
    UIScriptProcess(){};
    //
    bool GetIfFinished(std::shared_ptr<Structure> structure);
    void SetFinished(std::shared_ptr<Structure> structure);
    //Event
    void buttonEvent(std::shared_ptr<Structure>(m_Structure));

    void Update();

    //CountDown
    void SetCoolDown(float time);
    void CountDown();
    //Delay??
    std::future<void> asyncUpdate() {
        return std::async(std::launch::async, [this] {
            while (b_STALL) {
                Counter+=0.1F;
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟每秒调用一次update
            }
        });
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UISCRIPTPROCESS_H
