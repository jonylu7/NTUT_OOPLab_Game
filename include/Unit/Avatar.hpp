//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "Map/MapUtility.hpp"
#include "Selectable.hpp"
#include "Spritesheet.hpp"
#include "Unit/AttackAndDamageUnit.hpp"
#include "Unit/PathUtility.hpp"
#include "Unit/PathfindingUnit.hpp"
#include "Util/Image.hpp"
#include "Util/SpriteSheetAnimation.hpp"

class Avatar : public PathfindingUnit,
               public AttackAndDamageUnit,
               public Util::GameObject,
               public Selectable {

public:
    enum class UnitMode { DEAD, MOVE, IDLE, MOVE_ATTACK, ALIVE };
    Avatar(){};
    ~Avatar() override{};

    virtual void Start(glm::vec2 destination);
    virtual void aliveUpdate();

    float getDistance(glm::vec2 cell) {
        return sqrt(pow(cell.x - getCurrentCell().x, 2) +
                    pow(cell.y - getCurrentCell().y, 2));
    }

    void setSpriteSheet() {
        m_AvatarSpriteSheet->Start("../assets/sprites/mech.png", 50, 39, 247,
                                   0);
    }

    void DEBUG_printCurrentMoveDirection(MoveDirection Dir);

    UnitMode getUnitMode() { return m_currentMode; }
    virtual void customizeUpdate() {
        if (1 == 1) {
        }
    }

    void whenSelected() override;

    virtual std::shared_ptr<Util::Image> customizeImage() {
        return std::make_unique<Util::Image>(
            "../assets/sprites/mech_single.png");
    }

    virtual void Update() override;

protected:
    std::shared_ptr<Util::Image> m_Image;
    std::shared_ptr<SpriteSheet> m_AvatarSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<Util::SpriteSheetAnimation> m_SpriteSheetAnimation =
        std::make_shared<Util::SpriteSheetAnimation>();

private:
    bool b_justStarted = true;
    UnitMode m_currentMode;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
