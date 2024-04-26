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

    void setTotalCurrency(int value) { m_totalCurrency = value; };
    void addCurrency(int value) { m_totalCurrency += value; };

    void setTotalPower(int value) { m_totalPower = value; }
    void addPower(int value) { m_totalPower += value; }

    int getTotalCurrency() { return m_totalCurrency; }
    int getMaxTroopSize() { return m_maxTroopSize; }

protected:
    int
    getTotalPower(std::vector<std::shared_ptr<Structure>> m_BuiltStructure) {
        int totalPower = 0;
        for (int i = 0; i < m_BuiltStructure.size(); i++) {
            totalPower += m_BuiltStructure[i]->GetElectricPower();
        }
        return totalPower;
    }

protected:
    int m_maxTroopSize = 200;
    int m_totalPower = 0;
    int m_totalCurrency = 200;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
