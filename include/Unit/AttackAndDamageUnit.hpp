//
// Created by 盧威任 on 3/22/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP

class AttackAndDamageUnit {
public:
    AttackAndDamageUnit() {}
    virtual ~AttackAndDamageUnit() {}

    int getHP() { return m_HP; }
    int getArmorRate() { return m_ArmorRate; }
    int getSoftAttack() { return m_SoftAttack; }
    int getHardAttack() { return m_HardAttack; }

    void setHP(int hp) { m_HP = hp; }
    void setArmorRate(int armor) { m_ArmorRate = armor; }
    void setSoftAttack(int softattack) { m_SoftAttack = softattack; }
    void setHardAttack(int hardattack) { m_SoftAttack = hardattack; }

    void takeDamage(int softattack, int hardattack) {

        m_HP -= (100 - m_ArmorRate) * (1 / 100) * softattack +
                m_ArmorRate * (1 / 100) * hardattack;
    }

    void ForceAttackUnit(std::shared_ptr<AttackAndDamageUnit> target) {

        // check withinrange
        // cd time
        target->takeDamage(m_SoftAttack, m_HardAttack);
        return;
    }

private:
    int m_HP;
    float m_ArmorRate;
    int m_SoftAttack;
    int m_HardAttack;
    float m_AttackRange;

    float cd; // count as seconds
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
