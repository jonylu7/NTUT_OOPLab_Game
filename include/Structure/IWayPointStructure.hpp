//
// Created by nudle on 2024/3/3.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINTSTRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINTSTRUCTURE_HPP
#include "Structure.hpp"
#include "Line.hpp"

class IWayPointStructure{
private:
    glm::vec2 waypointLocation;
public:
    virtual glm::vec2 GetWayPointLocation(){return this->waypointLocation;};
    void SetWayPointLocation(glm::vec2 newLocation){
        this->waypointLocation=newLocation;
    };
    virtual glm::vec2 GetStructureLocation()=0;
};


#endif // PRACTICALTOOLSFORSIMPLEDESIGN_IWAYPOINTSTRUCTURE_HPP
