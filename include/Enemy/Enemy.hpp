//
// Created by nudle on 2024/4/26.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ENEMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ENEMY_HPP

#include "Mechanics/GameObjectID.hpp"

enum class EnemyMode { DEFAULT, ATTACK, DEFENSE };
enum class SceneMode { TUTORIAL, FREE };
class EnemyPlayer {
private:
    int m_totalPower = 0;
    int m_totalCurrency = 0;
    SceneMode m_SceneMode;

public:
    EnemyPlayer(SceneMode sceneMode)
        : m_SceneMode(sceneMode){};
    void Start();
    void Update();

protected:
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ENEMY_HPP
