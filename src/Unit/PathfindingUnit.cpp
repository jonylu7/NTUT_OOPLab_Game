//
// Created by nudle on 2024/3/15.
//
#include "Unit/PathfindingUnit.hpp"
void PathfindingUnit::UpdateNextCell(){
    switch (m_currentDir) {
    case MoveDirection::RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y};
        break;
    }
    case MoveDirection::LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y};
        break;
    }
    case MoveDirection::UP:{
        m_nextCell={m_nextCell.x,m_nextCell.y+1};
        break;
    }
    case MoveDirection::DOWN:{
        m_nextCell={m_nextCell.x,m_nextCell.y-1};
        break;
    }
    case MoveDirection::UP_RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y+1};
        break;
    }
    case MoveDirection::DOWN_LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y-1};
        break;
    }
    case MoveDirection::DOWN_RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y-1};
        break;
    }
    case MoveDirection::UP_LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y+1};
        break;
    }
    }
}
void PathfindingUnit::findNextCellDir() {
    if (m_targetCell.x == m_currentCell.x &&m_targetCell.y == m_currentCell.y) {
        m_currentDir = MoveDirection::IDLE;
    }else if(m_targetCell.y==m_currentCell.y){
        if(m_targetCell.x>m_currentCell.x)m_currentDir=MoveDirection::RIGHT;
        if(m_targetCell.x<m_currentCell.x)m_currentDir=MoveDirection::LEFT;
    }else if(m_targetCell.x==m_currentCell.x){
        if(m_targetCell.y>m_currentCell.y)m_currentDir=MoveDirection::UP;
        if(m_targetCell.y<m_currentCell.y)m_currentDir=MoveDirection::DOWN;
    }else if(m_targetCell.x/m_currentCell.x==m_targetCell.y/m_currentCell.y){
        if(m_targetCell.x>m_currentCell.x)m_currentDir=MoveDirection::UP_RIGHT;
        if(m_targetCell.x<m_currentCell.x)m_currentDir=MoveDirection::DOWN_LEFT;
    } else if(m_targetCell.x<m_currentCell.x&&m_targetCell.y>m_currentCell.y){
        m_currentDir=MoveDirection::UP_LEFT;
    }else if(m_targetCell.x>m_currentCell.x&&m_targetCell.y<m_currentCell.y){
        m_currentDir=MoveDirection::DOWN_RIGHT;
    }

}
void PathfindingUnit::walkTowardNextCell(){
    switch (m_currentDir) {
    case MoveDirection::RIGHT:{
        m_currentLocation={m_currentLocation.x+m_MovementSpeed,m_currentLocation.y};
        break;
    }
    case MoveDirection::LEFT:{
        m_currentLocation={m_currentLocation.x-m_MovementSpeed,m_currentLocation.y};
        break;
    }
    case MoveDirection::UP:{
        m_currentLocation={m_currentLocation.x,m_currentLocation.y+m_MovementSpeed};
        break;
    }
    case MoveDirection::DOWN:{
        m_currentLocation={m_currentLocation.x,m_currentLocation.y-m_MovementSpeed};
        break;
    }
    case MoveDirection::UP_RIGHT:{
        m_currentLocation={m_currentLocation.x+m_MovementSpeed,m_currentLocation.y+m_MovementSpeed};
        break;
    }
    case MoveDirection::DOWN_LEFT:{
        m_currentLocation={m_currentLocation.x-m_MovementSpeed,m_currentLocation.y-m_MovementSpeed};
        break;
    }
    case MoveDirection::DOWN_RIGHT:{
        m_currentLocation={m_currentLocation.x+m_MovementSpeed,m_currentLocation.y-m_MovementSpeed};
        break;
    }
    case MoveDirection::UP_LEFT:{
        m_currentLocation={m_currentLocation.x-m_MovementSpeed,m_currentLocation.y+m_MovementSpeed};
        break;
    }
    }
}