//
// Created by 盧威任 on 4/12/24.
//

#include "Mechanics/FindValidPathToDest.hpp"

std::deque<MoveDirection>
FindValidPathToDest::findPath(glm::vec2 currentcell,
                              glm::vec2 destinationcell) {
    std::deque<MoveDirection> m_dirQue;
    if (m_Map->getTileByCellPosition(destinationcell)->getWalkable() == false) {
        return m_dirQue;
    }

    Side whichSideToTouchObstacle = randomlyChooseSide();

    while (currentcell != destinationcell) {
        std::vector<MoveDirection> newDirque;
        bool arrived =
            findStraightPath(currentcell, destinationcell, &newDirque);
        for (auto i : newDirque) {
            m_dirQue.push_back(i);
            currentcell = PathUtility::getNextCellByCurrent(i, currentcell);
        }
        // push newdirque into dirque and update current cell and current dir

        if (arrived) {
            break;
        } else {
            auto facingDir = PathUtility::getDirByRelativeCells(
                currentcell, destinationcell);
            // turn
            MoveDirection turndir;
            if (m_Map->getWalkable(PathUtility::getNextCellByCurrent(
                    facingDir, currentcell)) == false) {
                turndir = findNewDirWhenCrash(whichSideToTouchObstacle,
                                              currentcell, facingDir);
            };

            std::vector<MoveDirection> movealong =
                moveAlongsideObstacle(whichSideToTouchObstacle, currentcell,
                                      turndir, destinationcell);

            for (auto i : movealong) {
                m_dirQue.push_back(i);
                currentcell = PathUtility::getNextCellByCurrent(i, currentcell);
            }
        }
    }
}

std::vector<MoveDirection>
FindValidPathToDest::moveAlongsideObstacle(Side side, glm::vec2 currentcell,
                                           MoveDirection currentdir,
                                           glm::vec2 destinationcell) {

    std::vector<MoveDirection> path;
    while (!canResumeWalkingStraight(currentcell, destinationcell)) {

        // if next is not touched by obstacle, turn
        if (!isTouchedByObstacle(side, currentcell, currentdir)) {
            currentdir = PathUtility::findNewDirWhenNotTouchedByObstacle(
                side, currentcell, currentdir);
        }

        // if next to be obstacle, turn findNewDirWhenCrash

        // walk along
        path.push_back(currentdir);
        currentcell =
            PathUtility::getNextCellByCurrent(currentdir, currentcell);
    }

    return path;
}

MoveDirection
FindValidPathToDest::findNewDirWhenCrash(Side side, glm::vec2 currentcell,
                                         MoveDirection currentdir) {
    MoveDirection newdir = currentdir;
    while (m_Map
               ->getTileByCellPosition(
                   PathUtility::getNextCellByCurrent(newdir, currentcell))
               ->getWalkable() == false) {
        switch (newdir) {
        case MoveDirection::RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::UP_RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN_RIGHT;
            }
        } break;

        case MoveDirection::LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN_LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP_LEFT;
            }
            break;
        }
        case MoveDirection::UP: {
            if (side == Side::R) {
                newdir = MoveDirection::UP_LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP_RIGHT;
            }
            break;
        }
        case MoveDirection::DOWN: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN_RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN_LEFT;
            }
            break;
        }
        case MoveDirection::UP_RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::UP;
            } else if (side == Side::L) {
                newdir = MoveDirection::RIGHT;
            }
            break;
        }
        case MoveDirection::DOWN_LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN;
            } else if (side == Side::L) {
                newdir = MoveDirection::LEFT;
            }
            break;
        }
        case MoveDirection::DOWN_RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN;
            }
            break;
        }
        case MoveDirection::UP_LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP;
            }
            break;
        }
        case MoveDirection::IDLE: {
            // printf("Direction debug didn't move\n");
            break;
        }
        }
    }
    return newdir;
}

bool FindValidPathToDest::isTouchedByObstacle(Side side, glm::vec2 currentcell,
                                              MoveDirection currentdir) {
    // abs
    std::shared_ptr<TileClass> upTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x, currentcell.y + 1));
    std::shared_ptr<TileClass> downTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x, currentcell.y - 1));
    std::shared_ptr<TileClass> rightTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x + 1, currentcell.y));
    std::shared_ptr<TileClass> leftTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x - 1, currentcell.y));

    std::shared_ptr<TileClass> upRightTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x + 1, currentcell.y + 1));
    std::shared_ptr<TileClass> downRightTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x + 1, currentcell.y - 1));
    std::shared_ptr<TileClass> upLeftTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x - 1, currentcell.y + 1));
    std::shared_ptr<TileClass> downLeftTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x - 1, currentcell.y - 1));

    std::shared_ptr<TileClass> checkedTile = std::make_shared<TileClass>();
    switch (currentdir) {
    case MoveDirection::RIGHT:
        if (side == Side::R) {
            checkedTile = downTile;
        } else if (side == Side::L) {
            checkedTile = upTile;
        }
        break;

    case MoveDirection::LEFT:
        if (side == Side::R) {
            checkedTile = upTile;
        } else if (side == Side::L) {
            checkedTile = downTile;
        }
        break;

    case MoveDirection::UP:
        if (side == Side::R) {
            checkedTile = rightTile;
        } else if (side == Side::L) {
            checkedTile = leftTile;
        }
        break;

    case MoveDirection::DOWN:
        if (side == Side::R) {
            checkedTile = leftTile;
        } else if (side == Side::L) {
            checkedTile = rightTile;
        }
        break;

    case MoveDirection::UP_RIGHT:
        if (side == Side::R) {
            checkedTile = rightTile;
        } else if (side == Side::L) {
            checkedTile = upTile;
        }
        break;

    case MoveDirection::DOWN_LEFT:
        if (side == Side::R) {
            checkedTile = leftTile;
        } else if (side == Side::L) {
            checkedTile = downTile;
        }
        break;

    case MoveDirection::DOWN_RIGHT:
        if (side == Side::R) {
            checkedTile = downTile;
        } else if (side == Side::L) {
            checkedTile = rightTile;
        }
        break;

    case MoveDirection::UP_LEFT:
        if (side == Side::R) {
            checkedTile = upTile;
        } else if (side == Side::L) {
            checkedTile = leftTile;
        }
        break;

    case MoveDirection::IDLE:
        // printf("Direction debug didn't move\n");
        break;
    }

    if (checkedTile->getWalkable() == true) {
        return false;
    } else {
        return true;
    }
}

bool FindValidPathToDest::findStraightPath(glm::vec2 currentcell,
                                           glm::vec2 destinationcell,
                                           std::vector<MoveDirection> *path) {

    while (currentcell != destinationcell) {
        MoveDirection followingDir =
            PathUtility::getDirByRelativeCells(currentcell, destinationcell);

        if (m_Map->getWalkable(
                PathUtility::getNextCellByCurrent(followingDir, currentcell))) {
            path->push_back(followingDir);
            currentcell =
                PathUtility::getNextCellByCurrent(followingDir, currentcell);
        } else {
            // if meet obstacle, stop in front of it, but unknown dir.
            return false;
        }
    }
    return true;
}

bool FindValidPathToDest::canResumeWalkingStraight(glm::vec2 currentcell,
                                                   glm::vec2 destinationcell) {
    std::vector<MoveDirection> path;
    auto arrived = findStraightPath(currentcell, destinationcell, &path);
    if (arrived || !path.empty()) {
        return true;
    }
    return false;
}
