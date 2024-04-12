//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP

#include "Map/Map.hpp"
#include "Unit/PathUtility.hpp"

#include <random>
class FindValidPathToDest {


private:
    glm::vec2 m_destinationCell;
    glm::vec2 m_nextCell;
    glm::vec2 m_currentCell;
    MoveDirection m_currentDir = MoveDirection::IDLE;

    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::deque<MoveDirection> m_dirQue;

public:
    FindValidPathToDest(){};
    ~FindValidPathToDest(){};
    void Start(std::shared_ptr<MapClass> map) { m_Map = map; }

protected:
    // set
    void setDestinationCell(glm::vec2 cell) { this->m_destinationCell = cell; }
    void setCurrentCell(glm::vec2 cell) {
        this->m_currentCell = glm::vec2(cell);
    }
    void setCurrentDir(MoveDirection direction) { m_currentDir = direction; }
    void setNextCell(glm::vec2 cell) { this->m_nextCell = glm::vec2(cell); }

    // get
    glm::vec2 getDestinationCell() { return m_destinationCell; }

    glm::vec2 getCurrentCell() { return m_currentCell; }
    MoveDirection getCurrentDir() { return m_currentDir; }
    glm::vec2 getNextCell() { return m_nextCell; }


    Side randomlyChooseSide() {
        // Create a random number generator engine
        std::random_device rd;  // Obtain a random seed from the hardware
        std::mt19937 gen(rd()); // Initialize the Mersenne Twister
                                // pseudo-random number generator

        // Define a distribution (uniform distribution in this case)
        std::uniform_int_distribution<int> distribution(
            0, 1); // Uniform distribution between 1 and 6 (inclusive)

        // Generate a random number
        int random_number = distribution(gen); // Generate a random number using
                                               // the generator and distribution

        switch (random_number) {
        case 0:
            return Side::R;
        case 1:
            return Side ::L;
        }
    }

public:
    std::deque<MoveDirection> findPath(glm::vec2 currentcell,
                                       glm::vec2 destinationcell) ;
    MoveDirection findNewDirWhenCrash(Side side, glm::vec2 currentcell,
                                      MoveDirection currentdir) ;
    bool isTouchedByObstacle(Side side,glm::vec2 currentcell,MoveDirection currentdir);

    std::vector<MoveDirection>  moveAlongsideObstacle(Side side, glm::vec2 currentcell,
                          MoveDirection currentdir,glm::vec2 destinationcell);
    bool findStraightPath(glm::vec2 currentcell, glm::vec2 destinationcell,
                          std::vector<MoveDirection> *path);
   bool canResumeWalkingStraight(glm::vec2 currentcell, glm::vec2 destinationcell);
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_FINDVALIDPATHTODEST_HPP
