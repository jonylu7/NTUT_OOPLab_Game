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
           WeaponType weapon) {}
    ~Weapon() {}
    // Getter and setter methods for m_fireRate
    static float getFireRate() { return m_FireRate; }

    static void setFireRate(float fireRate) { m_FireRate = fireRate; }

    // Getter and setter methods for m_fireRange
    static float getFireRange() { return m_FireRange; }

    static void setFireRange(float fireRange) { m_FireRange = fireRange; }

    // Getter and setter methods for m_SoftAttack
    static float getSoftAttack() { return m_SoftAttack; }

    static void setSoftAttack(float softAttack) { m_SoftAttack = softAttack; }

    // Getter and setter methods for m_HardAttack
    static float getHardAttack() { return m_HardAttack; }

    static void setHardAttack(float hardAttack) { m_HardAttack = hardAttack; }

    // Getter and setter methods for m_Type
    WeaponType getType() const { return m_Type; }

    void setType(WeaponType type) { m_Type = type; }

private:
    static float m_FireRate;
    static float m_FireRange;
    static float m_SoftAttack;
    static float m_HardAttack;
    WeaponType m_Type;
};

const Weapon COLT_45(180, 5.75, 100, 100, WeaponType::COLT_45);

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WEAPON_HPP
