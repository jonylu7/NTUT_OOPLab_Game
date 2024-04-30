//
// Created by 盧威任 on 3/22/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#include "Weapon.hpp"

class AttackAndDamageUnit {
public:
    enum class unitStatus {
        Death,
        Alive,
        NotBornedYet,
    };
    enum class unitOrder {
        ATTACK,
        NOORDER,
        MOVE,
        MOVE_ATTACK,
        Struct_MOVEABLE
    };
    AttackAndDamageUnit() {}
    virtual ~AttackAndDamageUnit() {}

    int getHP() { return m_HP; }

    void setHP(int hp) { m_HP = hp; }

    void takeDamage(int softattack, int hardattack) {

        m_HP -= (100 - m_ArmorRate) * (1 / 100) * softattack +
                m_ArmorRate * (1 / 100) * hardattack;
    }

    void ForceAttackUnit(std::shared_ptr<AttackAndDamageUnit> target) {
        // cd time
        target->takeDamage(m_Weapon.getSoftAttack(), m_Weapon.getHardAttack());
        return;
    }

    void UpdateDeath() {
        if (m_HP <= 0) {
            m_CurrentState = unitStatus::Death;
        }
    }

    unitStatus GetCurrentUpdateMode() const { return m_CurrentState; };
    unitOrder GetCurrentOrder() const { return m_CurrentOrder; }

    void SetCurrentUpdateMode(unitStatus mode) { m_CurrentState = mode; };
    void SetCurrentOrder(unitOrder order) { m_CurrentOrder = order; };

protected:
    unitStatus m_CurrentState = unitStatus::NotBornedYet;
    unitOrder m_CurrentOrder = unitOrder::NOORDER;
    int m_HP;
    Weapon m_Weapon;
    float m_ArmorRate;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
