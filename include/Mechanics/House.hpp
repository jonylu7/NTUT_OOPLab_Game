//
// Created by 盧威任 on 3/23/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP

enum class HouseType { ENEMY, NEUTRAL, FRIEND, MY, NONE };

class House {
public:
    House() {}
    House(HouseType house)
        : m_house(house) {}
    ~House() {}

    HouseType getHouse() { return m_house; }
    void setHouse(HouseType house) { m_house = house; }

private:
    HouseType m_house;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP
