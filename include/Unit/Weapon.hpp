//
// Created by 盧威任 on 3/23/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WEAPON_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WEAPON_HPP
enum class WeaponType {
    COLT_45,
    M16,
};

class Weapon {
public:
    Weapon() {}
    ~Weapon() {}
    // Getter and setter methods for m_fireRate
    static float getFireRate() { return m_fireRate; }

    static void setFireRate(float fireRate) { m_fireRate = fireRate; }

    // Getter and setter methods for m_fireRange
    static float getFireRange() { return m_fireRange; }

    static void setFireRange(float fireRange) { m_fireRange = fireRange; }

    // Getter and setter methods for m_softAttack
    static float getSoftAttack() { return m_softAttack; }

    static void setSoftAttack(float softAttack) { m_softAttack = softAttack; }

    // Getter and setter methods for m_HardAttack
    static float getHardAttack() { return m_HardAttack; }

    static void setHardAttack(float hardAttack) { m_HardAttack = hardAttack; }

    // Getter and setter methods for m_Type
    WeaponType getType() const { return m_Type; }

    void setType(WeaponType type) { m_Type = type; }

private:
    static float m_fireRate;
    static float m_fireRange;
    static float m_softAttack;
    static float m_HardAttack;
    WeaponType m_Type;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WEAPON_HPP
