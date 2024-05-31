//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#include "Mechanics/UnitManager.hpp"
class Player {
public:
    Player() {}
    ~Player() {}
    void setTotalCurrency(int value) { m_TotalCurrency = value; }
    void addTotalCurrency(float value) { m_TotalCurrency += value; };

    void setFixedPower(int value) { m_FixedPower = value; }
    void addFixedPower(int value) { m_FixedPower += value; }

public:
    void Start(std::shared_ptr<MapClass> map) { m_UnitManager->Start(map); }
    void Update() {
        updateCurrency();
        m_UnitManager->Update();
    }

public:
    int getTotalPower() {
        return m_UnitManager->getStructureManager()->getStructurePower() +
               m_FixedPower;
    }
    int getTotalCurrency() { return m_TotalCurrency; }
    int getMaxTroopSize() { return m_MaxTroopSize; }

private:
    void updateCurrency() {
        // count 10s
        for (auto i : m_StructureManager->getStructureArray()
                          ->getBuiltStructureArray()) {
            if (std::dynamic_pointer_cast<OreRefinery>(i)) {
                m_TotalCurrency += 150;
            }
        }
    }

private:
    std::shared_ptr<UnitManager> m_UnitManager = st::make_shared<UnitManager>();
    int m_MaxTroopSize = 200;
    int m_FixedPower = 0;
    float m_TotalCurrency = 0;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
