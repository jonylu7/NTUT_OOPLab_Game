//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#include "Structure/Structure.hpp"
class Player {
public:
    Player() {}
    ~Player() {}
    void setTotalCurrency(int value) { m_TotalCurrency = value; }
    void addTotalCurrency(float value) { m_TotalCurrency += value; };

    void setFixedPower(int value) { m_FixedPower = value; }
    void addFixedPower(int value) { m_FixedPower += value; }

    int getTotalCurrency() { return m_TotalCurrency; }


protected:
    int
    getTotalPower(std::vector<std::shared_ptr<Structure>> m_BuiltStructure) {
        int totalPower = 0;
        for (int i = 0; i < m_BuiltStructure.size(); i++) {
            totalPower += m_BuiltStructure[i]->getElectricPower();
        }
        return totalPower;
    }

protected:
    int m_MaxTroopSize = 200;
    int m_FixedPower = 0;
    float m_TotalCurrency = 0;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
