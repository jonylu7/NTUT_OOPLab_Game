//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "Avatar/AttackAndDamage.hpp"
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
               public AttackAndDamage,
               public Util::GameObject,
               public Selectable,
               public AvatarOrder,
               public IHealthable {

public:
    Avatar(){};
    Avatar(UnitType unit, HouseType house)
        : m_ID(GameObjectID(UnitType::NONE, HouseType::MY)){};
    ~Avatar() override{};

    virtual void Start(glm::vec2 spawnlocationcell);
    void noOrderUpdate();
    void spawnedUpdate();
    void finishedmovingUpdate();
    void moveUpdate();
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
    HouseType getHouseType() { return m_ID.getHouseType(); }

    void whenSelected() override;

    virtual std::shared_ptr<Util::Image> customizeImage() {
        return std::make_unique<Util::Image>(
            "../assets/sprites/mech_single.png");
    }

    GameObjectID getID() { return m_ID; }

    virtual void Update() override;

    std::shared_ptr<Health> getHealth() override { return m_Health; }
    void setHealth(std::shared_ptr<Health> health) override {
        m_Health = health;
    }

    std::shared_ptr<AttackAndDamage> getAttackAndDamager() {
        return m_AttackAndDamage;
    }

protected:
    std::shared_ptr<SpriteSheet> m_AvatarSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<Util::SpriteSheetAnimation> m_SpriteSheetAnimation =
        std::make_shared<Util::SpriteSheetAnimation>();

    // health
    std::shared_ptr<Health> m_Health = std::make_shared<Health>();
    // attack and damage
    std::shared_ptr<AttackAndDamage> m_AttackAndDamage =
        std::make_shared<AttackAndDamage>();

private:
    GameObjectID m_ID;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
