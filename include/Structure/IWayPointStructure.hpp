//
// Created by nudle on 2024/3/3.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINTSTRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINTSTRUCTURE_HPP
#include "Line.hpp"
#include "Structure.hpp"

class IWayPointStructure {
private:
    glm::vec2 waypointLocation = {0, 0};

public:
    virtual glm::vec2 GetWayPointLocation() { return this->waypointLocation; };
    void SetWayPointLocation(glm::vec2 newLocation) {
        this->waypointLocation = {newLocation.x + 0.5 * CELL_SIZE.x,
                                  newLocation.y + 0.5 * CELL_SIZE.y};
    };
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINTSTRUCTURE_HPP
