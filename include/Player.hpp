//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
class Player {
public:
    Player() {}
    ~Player() {}

    void setCurrency(int value) { m_totalCurrency += value; };

    int getTotalPower() {}
    int getTotalCurrency() { return m_totalCurrency; }

private:
    int m_totalCurrency = 0;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
