//
// Created by nudle on 2024/4/26.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ENEMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ENEMY_HPP

// #include "Mechanics/GameObjectID.hpp"
#include "Mechanics/Player.hpp"
enum class EnemyMode { DEFAULT, ATTACK, DEFENSE };
enum class SceneMode { TUTORIAL, FREE };
class EnemyPlayer : public Player {
private:
    int m_totalPower = 0;
    int m_totalCurrency = 0;
    SceneMode m_SceneMode;

public:
    EnemyPlayer(SceneMode sceneMode)
        : m_SceneMode(sceneMode){};
    void Start();
    void Update();

    void addUnitConstructCount(UnitType type, int value) {
        unitCount[type] += value;
    }
    int getUnitConstructCount(UnitType type) { return unitCount[type]; }
    int getAvatarCount() { return unitCount[UnitType::INFANTRY]; }
    void addAvatarCount(UnitType type, int value) { unitCount[type] += value; }

protected:
    std::unordered_map<UnitType, unsigned int> unitCount;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ENEMY_HPP
