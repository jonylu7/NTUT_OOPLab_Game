//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
class Player {
public:
    Player() {}
    ~Player() {}

    void setTotalCurrency(int value) { m_totalCurrency = value; };
    void addCurrency(int value) { m_totalCurrency += value; };

    void setTotalPower(int value){m_totalPower=value;}
    void addPower(int value){m_totalPower+=value;}

    int getTotalPower() {return m_totalPower;}
    int getTotalCurrency() { return m_totalCurrency; }
    int getMaxTroopSize(){return m_maxTroopSize;}

private:
    int m_maxTroopSize = 200;
    int m_totalPower = 0 ;
    int m_totalCurrency = 0;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
