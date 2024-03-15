//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP

#include "Tile.hpp"
#include "Util/GameObject.hpp"
#include "Map.hpp"
class PathfindingUnit:public Util::GameObject{
private:
    enum class UnitMode{
        Attacking,Moving,Stop
    };
    enum class MoveDirection{
        Up,TopRight,TopLeft,Right,Left,DownRight,DownLeft,Down,Wait
    };

    glm::vec2 m_targetCell;
    glm::vec2 m_nextCell;
    glm::vec2 m_currentCell;
    glm::vec2 m_currentLocation;

    MoveDirection m_currentDir=MoveDirection::Wait;

    float m_Hp=100.F;
    float m_MoveSpeed=1.F;

public:
    PathfindingUnit(){};
    ~PathfindingUnit(){};

    void setTargetCell(glm::vec2 target){this->m_targetCell=target;}
    glm::vec2 getTargetCell(){return m_targetCell;}

    void findNextCell() {
        if (m_targetCell.x - m_currentCell.x >m_targetCell.y - m_currentCell.y &&m_targetCell.x - m_currentCell.x > 0) {
            m_currentDir = MoveDirection::Right;
        } else if (m_targetCell.x - m_currentCell.x >m_targetCell.y - m_currentCell.y &&m_targetCell.x - m_currentCell.x < 0) {
            m_currentDir = MoveDirection::Up;
        } else if (m_targetCell.x - m_currentCell.x <m_targetCell.y - m_currentCell.y &&m_targetCell.x - m_currentCell.x > 0) {
            m_currentDir = MoveDirection::Down;
        }else if(m_targetCell.x-m_currentCell.x<m_targetCell.y-m_currentCell.y&&m_targetCell.x-m_currentCell.x<0){
            m_currentDir=MoveDirection::Left;
        }else if(m_targetCell.x-m_currentCell.x==m_targetCell.y-m_currentCell.y&&m_targetCell.x-m_currentCell.x<0){
            m_currentDir=MoveDirection::Down;
        }
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
