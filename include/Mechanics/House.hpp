//
// Created by 盧威任 on 3/23/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP

enum class HouseType { ENEMY, NEUTRAL, FRIEND, ME, NONE };

class House {
public:
    House()
        : m_HouseType(HouseType::NONE) {}
    House(HouseType housetype)
        : m_HouseType(housetype) {}
    ~House() {}

    HouseType getHouseType() { return m_HouseType; }
    void setHouseType(HouseType housetype) { m_HouseType = housetype; }

protected:
    HouseType m_HouseType;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_HOUSE_HPP
