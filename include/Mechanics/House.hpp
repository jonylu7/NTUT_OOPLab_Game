//
// Created by 盧威任 on 3/23/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP

enum class HouseType { ENEMY, NEUTRAL, FRIEND, MY, NONE };

class House {
public:
    House()
        : m_House(HouseType::NONE) {}
    House(HouseType house)
        : m_House(house) {}
    ~House() {}

    HouseType getHouse() { return m_House; }
    void setHouse(HouseType house) { m_House = house; }

protected:
    HouseType m_House;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP
