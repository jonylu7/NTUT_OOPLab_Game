//
// Created by nudle on 2024/3/3.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINT_HPP
#include "Display/Line.hpp"
#include "Structure.hpp"

class IWayPointStructure {
private:
    glm::vec2 waypointLocation = {0, 0};

public:
    virtual glm::vec2 GetWayPointLocation() { return this->waypointLocation; };

    void
    SetWayPointLocationByCellCoord(glm::vec2 newLocation) { //=DrawLocation+Cell

        newLocation = {newLocation.x * CELL_SIZE.x,
                       newLocation.y * CELL_SIZE.y};
        this->waypointLocation = {newLocation.x + 0.5 * CELL_SIZE.x,
                                  newLocation.y + 0.5 * CELL_SIZE.y};
    };
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINT_HPP
