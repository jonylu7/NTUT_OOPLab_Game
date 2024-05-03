//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "Avatar/AttackAndDamageUnit.hpp"
#include "Avatar/AvatarOrder.hpp"
#include "Avatar/Moving.hpp"
#include "Avatar/PathUtility.hpp"
#include "Display/Image.hpp"
#include "Display/SpriteSheet.hpp"
#include "Display/SpriteSheetAnimation.hpp"
#include "Map/MapUtility.hpp"
#include "Mechanics/GameObjectID.hpp"
#include "Selectable.hpp"

class Avatar : public Moving,
               public AttackAndDamageUnit,
               public Util::GameObject,
               public Selectable,
               public GameObjectID,
               public AvatarOrder {

public:
    Avatar(){};
    ~Avatar() override{};

    virtual void Start(glm::vec2 destination);
    void aliveUpdate();
    void deadUpdate();
    void attackUpdate();

    float getDistance(glm::vec2 cell) {
        return sqrt(pow(cell.x - getCurrentCell().x, 2) +
                    pow(cell.y - getCurrentCell().y, 2));
    }

    void setSpriteSheet() {
        m_AvatarSpriteSheet->Start("../assets/sprites/mech.png", 50, 39, 247,
                                   0);
    }

    void DEBUG_printCurrentMoveDirection(MoveDirection Dir);

    virtual void customizeUpdate() {
        if (1 == 1) {
        }
    }

    void whenSelected() override;

    virtual std::shared_ptr<Util::Image> customizeImage() {
        return std::make_unique<Util::Image>(
            "../assets/sprites/mech_single.png");
    }

    GameObjectID getID() { return m_ID; }

    virtual void Update() override;

protected:
    // std::shared_ptr<Avatar> m_Nemesis = std::make_shared<Avatar>();
    std::shared_ptr<Util::Image> m_Image;
    std::shared_ptr<SpriteSheet> m_AvatarSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<Util::SpriteSheetAnimation> m_SpriteSheetAnimation =
        std::make_shared<Util::SpriteSheetAnimation>();

private:
    bool b_justStarted = true;
    GameObjectID m_ID;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
