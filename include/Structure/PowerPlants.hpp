#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP

#include "Structure.hpp"

class PowerPlants : public Structure {
public:
    PowerPlants(float electricPower = 100.F, float buildingTime = 15.F*CHEAT,
                float buildingCost = 300.F, float buildingHp = 400.F,
                HouseType house = HouseType::NONE)
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    GameObjectID(unitType::POWER_PLANT, house)) {
//        SetDrawable(
//            std::make_unique<Util::Image>("../assets/sprites/PowerPlants.png"));
    };
    void SetSpriteSheet()override{
        m_StructureSpriteSheet->Start("../assets/sprites/PowerPlants_SpriteSheet.png",48,48,13,0);
        m_relativeOccupiedArea={{0,0},{0,1},{1,0},{1,1}};
    }
    void SetObjectLocation(glm::vec2 location) override{
        location = ChangeToCell(location);
        ObjectLocation = location;
        DrawLocation = {location.x + 1 * CELL_SIZE.x,
                        location.y + 1 * CELL_SIZE.y};
        m_Transform.translation = DrawLocation;
    }
};

#endif
