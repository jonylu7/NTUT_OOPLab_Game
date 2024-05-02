//
// Created by 盧威任 on 3/22/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#include "Weapon.hpp"

class AttackAndDamageUnit {
public:
    enum class UnitStatus {
        DEAD,
        ALIVE,
        NOT_BORN_YET,
    };

    AttackAndDamageUnit() {}
    virtual ~AttackAndDamageUnit() {}

    int getHP() { return m_HP; }

    void setHP(int hp) {
        m_HP = hp;
        if (m_HP <= 0) {
            m_CurrentStatus = UnitStatus::DEAD;
        }
    }

    void takeDamage(int softattack, int hardattack) {

        m_HP -= (100 - m_ArmorRate) * (1 / 100) * softattack +
                m_ArmorRate * (1 / 100) * hardattack;
    }

    void forceAttackUnit(std::shared_ptr<AttackAndDamageUnit> target) {
        // cd time
        target->takeDamage(m_Weapon.getSoftAttack(), m_Weapon.getHardAttack());
        return;
    }

    UnitStatus getCurrentStatus() const { return m_CurrentStatus; };

    void setCurrentStatus(UnitStatus mode) { m_CurrentStatus = mode; };

protected:
    UnitStatus m_CurrentStatus = UnitStatus::NOT_BORN_YET;
    int m_HP;
    Weapon m_Weapon;
    float m_ArmorRate;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
