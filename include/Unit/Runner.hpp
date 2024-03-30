//
// Created by nudle on 2024/3/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_RUNNER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_RUNNER_HPP
#include "Avatar.hpp"
#define ATTACK_RANGE 7

class Runner : public Avatar{
private:
    bool b_beingChase= false;

    std::shared_ptr<Avatar> m_hunter;
    glm::vec2 lastTargetCell;
    std::vector<MoveDirection> dictionary = {
        MoveDirection::UP,    MoveDirection::UP_RIGHT,
        MoveDirection::RIGHT, MoveDirection::DOWN_RIGHT,
        MoveDirection::DOWN,  MoveDirection::DOWN_LEFT,
        MoveDirection::LEFT,  MoveDirection::UP_LEFT};
    enum class runMode{REASONABLE,LIDL_RANDOM,FULL_RANDOM};
    int edgeCount=0;
public:
    void setBeingChase(std::shared_ptr<Avatar> hunter);
    std::shared_ptr<Util::Image> customizeImage()override{ return std::make_unique<Util::Image>("../assets/sprites/Runner.png");}
    void customizeUpdate()override;
    MoveDirection findNewDir(MoveDirection Dir,int edgeCount);
    MoveDirection oppositeDir(MoveDirection Dir,runMode mode);
    glm::vec2 getNextCellByCurrentPlus3(MoveDirection currentdir,glm::vec2 currentcell,int n,int m) ;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_RUNNER_HPP
