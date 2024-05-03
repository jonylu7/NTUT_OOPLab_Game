//
// Created by 盧威任 on 3/23/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WEAPON_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WEAPON_HPP
#include <memory>
enum class WeaponType {
    COLT_45,
    M16,
    Fireball,
    Art_75mm,
    Art_90mm,
    Art_105mm,
    Art_120mm,
    Nuke,
    Grenade
};

class Weapon {
public:
    Weapon() {}
    Weapon(float firerate, float firerange, float softattack, float hardattack,
           WeaponType weapontype)
        : m_FireRange(firerange),
          m_SoftAttack(softattack),
          m_HardAttack(hardattack),
          m_FireRateInMs(firerate),
          m_Type(weapontype) {}
    ~Weapon() {}
    // Getter and setter methods for m_fireRate
    float getFireRateInM() { return m_FireRateInMs; }

    void setFireRateInM(float fireRateInM) { m_FireRateInMs = fireRateInM; }

    float getIntervalInS() {
        auto r = m_FireRateInMs / 60;
        return (1 / r);
    }

    // Getter and setter methods for m_fireRange
    float getFireRange() { return m_FireRange; }

    void setFireRange(float fireRange) { m_FireRange = fireRange; }

    // Getter and setter methods for m_SoftAttack
    float getSoftAttack() { return m_SoftAttack; }

    void setSoftAttack(float softAttack) { m_SoftAttack = softAttack; }

    // Getter and setter methods for m_HardAttack
    float getHardAttack() { return m_HardAttack; }

    void setHardAttack(float hardAttack) { m_HardAttack = hardAttack; }

    // Getter and setter methods for m_Type
    WeaponType getType() const { return m_Type; }

    void setType(WeaponType type) { m_Type = type; }

private:
    float m_FireRateInMs;
    float m_FireRange;
    float m_SoftAttack;
    float m_HardAttack;
    WeaponType m_Type;
};

const Weapon COLT_45(180, 5.75, 100, 100, WeaponType::COLT_45);

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WEAPON_HPP
