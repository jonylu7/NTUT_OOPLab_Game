//
// Created by 盧威任 on 3/22/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#include "Util/Time.hpp"
#include "Weapon.hpp"

enum class LivingStatus {
    DEAD,
    ALIVE,
    NOT_BORN_YET,

    REGRET_ABOUT_LIVING, // just a joke, or not
};

class AttackAndDamageUnit {
public:
    AttackAndDamageUnit() {}
    virtual ~AttackAndDamageUnit() {}

    int getHP() { return m_HP; }

    void setHP(int hp) {
        m_HP = hp;
        if (m_HP <= 0) {
            m_LivingStatus = LivingStatus::DEAD;
        }
    }

    void takeDamage(int softattack, int hardattack) {

        m_HP -= (100 - m_ArmorRate) * (1 / 100) * softattack +
                m_ArmorRate * (1 / 100) * hardattack;
        if (m_HP <= 0) {
            m_LivingStatus = LivingStatus::DEAD;
        }
    }

    void openFireToTarget(std::shared_ptr<AttackAndDamageUnit> target) {
        // cd time
        m_DeltaTime += m_Time.GetDeltaTime();
        if (m_Weapon.getIntervalInS() <= m_DeltaTime) {
            m_DeltaTime = 0;
            target->takeDamage(m_Weapon.getSoftAttack(),
                               m_Weapon.getHardAttack());
        }
    }

    LivingStatus getLivingStatus() const { return m_LivingStatus; };

    void setLivingStatus(LivingStatus status) { m_LivingStatus = status; };

    Weapon getWeapon() { return m_Weapon; }

private:
    float m_DeltaTime = 0;

protected:
    LivingStatus m_LivingStatus = LivingStatus::NOT_BORN_YET;
    Util::Time m_Time;
    int m_HP;
    Weapon m_Weapon;
    float m_ArmorRate;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
