#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_BARRACKS_HPP

#include "SpriteSheet.hpp"
#include "Util/SpriteSheetAnimation.hpp"
#include "WayPointStructure.hpp"

class Barracks : public WayPointStructure {
public:
    Barracks(float electricPower = -20.F, float buildingTime = 15.F*CHEAT,
             float buildingCost = 300.F, float buildingHp = 800.F,
             HouseType house = HouseType::NONE)

        : WayPointStructure(electricPower, buildingTime, buildingCost,
                            buildingHp,
                            GameObjectID(unitType::BARRACKS, house)){};
    void Start() override;
    void SetObjectLocation(glm::vec2 location) override{
        location = ChangeToCell(location);
        ObjectLocation = location;
        DrawLocation = {location.x + 1 * CELL_SIZE.x,
                        location.y + 1 * CELL_SIZE.y};
        m_Transform.translation = DrawLocation;
    }
};
#endif
