//
// Created by 盧威任 on 5/5/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_HEALTH_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_HEALTH_HPP
#include <memory>
enum class LivingStatus {
    DEAD,
    ALIVE,
    NOT_BORN_YET,

    REGRET_ABOUT_LIVING, // just a joke, or not
};

class Health {
public:
    Health()
        : m_LivingStatus(
              std::make_shared<LivingStatus>(LivingStatus::NOT_BORN_YET)),
          m_HP(100),
          m_ArmorRate(0.5) {}
    Health(std::shared_ptr<LivingStatus> livingstatus, int hp, float armorrate)
        : m_LivingStatus(livingstatus),
          m_HP(hp),
          m_ArmorRate(armorrate) {}

    Health(int hp, float armorrate)
        : m_LivingStatus(
              std::make_shared<LivingStatus>(LivingStatus::NOT_BORN_YET)),
          m_HP(hp),
          m_ArmorRate(armorrate) {}
    ~Health() {}
    std::shared_ptr<LivingStatus> getLivingStatus() const {
        return m_LivingStatus;
    };
    void setLivingStatus(std::shared_ptr<LivingStatus> status) {
        m_LivingStatus = status;
    };

    void setHP(int hp) {
        m_HP = hp;
        if (m_HP <= 0) {
            m_LivingStatus = std::make_shared<LivingStatus>(LivingStatus::DEAD);
        }
    }

    void addHP(int value) {
        m_HP += value;
        if (m_HP <= 0) {
            m_LivingStatus = std::make_shared<LivingStatus>(LivingStatus::DEAD);
        }
    }

    int getHP() { return m_HP; }
    void setArmorRate(float armorrate) { m_ArmorRate = armorrate; }
    float getArmorRate() { return m_ArmorRate; }

private:
    std::shared_ptr<LivingStatus> m_LivingStatus =
        std::make_shared<LivingStatus>();
    int m_HP;
    float m_ArmorRate;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_HEALTH_HPP
