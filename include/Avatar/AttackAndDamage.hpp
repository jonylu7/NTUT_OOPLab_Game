//
// Created by 盧威任 on 3/22/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGE_HPP
#include "Unit/IHealthable.hpp"
#include "Util/Time.hpp"
#include "Weapon.hpp"

class AttackAndDamage {
public:
    AttackAndDamage() {}
    virtual ~AttackAndDamage() {}

    void damageTargetWithWeapon(std::shared_ptr<IHealthable> target,
                                std::shared_ptr<Weapon> weapon) {
        auto targethealth = target->getHealth();
        auto damage =
            ((1 - targethealth->getArmorRate()) * m_Weapon->getSoftAttack()) +
            (targethealth->getArmorRate() * m_Weapon->getHardAttack());
        targethealth->addHP(-1 * damage);
    }

    void openFireToTarget(std::shared_ptr<IHealthable> target) {
        // cd time
        m_DeltaTime += m_Time.GetDeltaTime();
        if (m_Weapon->getIntervalInS() <= m_DeltaTime) {
            m_DeltaTime = 0;
            damageTargetWithWeapon(target, m_Weapon);
        }
    }

    std::shared_ptr<Weapon> getWeapon() { return m_Weapon; }
    void setWeapon(std::shared_ptr<Weapon> weapon) { m_Weapon = weapon; }

private:
    float m_DeltaTime = 0;

protected:
    Util::Time m_Time;
    std::shared_ptr<Weapon> m_Weapon = std::make_shared<Weapon>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGE_HPP
