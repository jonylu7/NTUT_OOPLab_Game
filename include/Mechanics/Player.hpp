//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#include "Structure/AdvancePowerPlants.hpp"
#include "Structure/PowerPlants.hpp"
#include "UnitManager.hpp"
class Player {
public:
    Player() {}
    ~Player() {}
    void setTotalCurrency(int value) { m_TotalCurrency = value; }
    void addTotalCurrency(float value) { m_TotalCurrency += value; };

    void setFixedPower(int value) { m_FixedPower = value; }
    void addFixedPower(int value) { m_FixedPower += value; }

    int getTotalCurrency() { return m_TotalCurrency; }

    void Start(std::shared_ptr<MapClass> map) { m_UnitManager->Start(map); }
    void Update() {
        m_UnitManager->Update();

        if (m_mainDeltaTime >= 1) {
            m_mainDeltaTime = 0;
            updateCurrency();
        }
        m_mainDeltaTime += m_Time.GetDeltaTime();
    }

    std::shared_ptr<UnitManager> getUnitManager() { return m_UnitManager; }

    int getTotalPower() {
        int power = 0;
        for (auto i : m_UnitManager->getStructureManager()
                          ->getStructureArray()
                          ->getBuiltStructureArray()) {
            power +=
                std::dynamic_pointer_cast<PowerPlants>(i)->getElectricPower();
            power += std::dynamic_pointer_cast<ADVPowerPlants>(i)
                         ->getElectricPower();
        }
        return power + m_FixedPower;
    }

    bool getCheatMode() { return m_cheat; }
    void setCheatMode(bool cheat) { m_cheat = cheat; }

private:
    void updateCurrency() {

        for (auto i : m_UnitManager->getStructureManager()
                          ->getStructureArray()
                          ->getBuiltStructureArray()) {
            if (std::dynamic_pointer_cast<OreRefinery>(i)) {
                addTotalCurrency(150);
            }
        }
    }

private:
    int m_MaxTroopSize = 200;
    int m_FixedPower = 0;
    float m_TotalCurrency = 0;
    std::shared_ptr<UnitManager> m_UnitManager =
        std::make_shared<UnitManager>();

private:
    float m_mainDeltaTime = 0;
    Util::Time m_Time;
    bool m_cheat = false;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
