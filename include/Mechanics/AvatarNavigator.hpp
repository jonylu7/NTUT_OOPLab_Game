//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_AVATARNAVIGATOR_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_AVATARNAVIGATOR_HPP

#include "Avatar/PathUtility.hpp"
#include "Map/Map.hpp"
#include <random>

class AvatarNavigator {

public:
    AvatarNavigator(){};
    ~AvatarNavigator(){};

    void Start(std::shared_ptr<MapClass> map) { m_Map = map; }

protected:
    Side randomlyChooseSide();

public:
    std::deque<MoveDirection> findPath(glm::vec2 currentcell,
                                       glm::vec2 destinationcell);
    MoveDirection findNewDirWhenCrash(Side side, glm::vec2 currentcell,
                                      MoveDirection currentdir);
    bool isTouchedByObstacle(Side side, glm::vec2 currentcell,
                             MoveDirection currentdir);

    std::vector<MoveDirection> moveAlongsideObstacle(Side side,
                                                     glm::vec2 currentcell,
                                                     MoveDirection currentdir,
                                                     glm::vec2 destinationcell);
    bool findStraightPath(glm::vec2 currentcell, glm::vec2 destinationcell,
                          std::vector<MoveDirection> *path);
    bool canResumeWalkingStraight(glm::vec2 currentcell,
                                  glm::vec2 destinationcell);

private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_AVATARNAVIGATOR_HPP
