//
// Created by 盧威任 on 2/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WORLD_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WORLD_HPP
#include "Cell.hpp"
#include <memory>
#include <vector>
typedef unsigned int CELL;
class WorldClass {
public:
    WorldClass(){};
    ~WorldClass(){};

private:
    CELL WorldWidth = 100;
    CELL WorldHeight = 100;
    std::vector<std::shared_ptr<CellClass>> Map;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WORLD_HPP
