//
// Created by nudle on 2024/4/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SANDBAG_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SANDBAG_HPP
#include "Structure.hpp"

class SandBag : public Structure {
    SandBag(float electricPower = 0.F, float buildingTime = 1.F * CHEAT,
                float buildingCost = 25.F, float buildingHp = 200.F,
                HouseType house = HouseType::NONE)
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    GameObjectID(unitType::SANDBAGS, house)){
          };
    SandBag(HouseType house)
        : Structure(0.F, 1.F * CHEAT, 25.F,200.F,
                    GameObjectID(unitType::SANDBAGS, house)){};
    void SetSpriteSheet() override {
        m_StructureSpriteSheet->Start(
            "../assets/sprites/SandBag_SpriteSheet.png", 48, 48, 13, 0);
        m_relativeOccupiedArea = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    }
    void SetObjectLocation(glm::vec2 location) override {
        location = MapUtil::PositionStickToGrid(location);
        ObjectLocation = location;
        DrawLocation = {location.x + 1 * CELL_SIZE.x,
                        location.y + 1 * CELL_SIZE.y};
        m_Transform.translation = DrawLocation;
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SANDBAG_HPP
