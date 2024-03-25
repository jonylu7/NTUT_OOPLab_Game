//
// Created by 盧威任 on 3/22/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#include "Weapon.hpp"
class AttackAndDamageUnit {
public:
    AttackAndDamageUnit() {}
    virtual ~AttackAndDamageUnit() {}

    int getHP() { return m_HP; }

    void setHP(int hp) { m_HP = hp; }

    void takeDamage(int softattack, int hardattack) {

        m_HP -= (100 - m_ArmorRate) * (1 / 100) * softattack +
                m_ArmorRate * (1 / 100) * hardattack;
    }

    void ForceAttackUnit(std::shared_ptr<AttackAndDamageUnit> target) {

        // check withinrange
        // cd time
        target->takeDamage(m_Weapon.getSoftAttack(), m_Weapon.getHardAttack());
        return;
    }

private:
    int m_HP;
    Weapon m_Weapon;
    float m_ArmorRate;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
