//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_AVATAR_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_AVATAR_HPP
#include "Avatar/AttackAndDamage.hpp"
#include "Avatar/AvatarOrder.hpp"
#include "Avatar/Moving.hpp"
#include "Avatar/PathUtility.hpp"
#include "Display/SpriteSheet.hpp"
#include "Display/SpriteSheetAnimation.hpp"
#include "Map/MapUtility.hpp"
#include "Mechanics/GameObjectID.hpp"
#include "Selectable.hpp"
#include "Unit/Huntable.hpp"
#include "Util/Image.hpp"
enum class AI_Type{NONE,DEFENCE,ATTACK};
class Avatar : public Util::GameObject, public Selectable, public Huntable {

public:
    Avatar(){};
    Avatar(UnitType unit, HouseType house, Weapon weapon = COLT_45)
        : m_ID(GameObjectID(UnitType::NONE, house)) {
        getAttackAndDamage()->setWeapon(std::make_shared<Weapon>(weapon));
    };
    ~Avatar() override{};

    virtual void Start(glm::vec2 spawnlocationcell);
    void noorderUpdate();
    void spawnedUpdate();
    void moveUpdate();
    void deadUpdate();
    void attackUpdate();

    float getDistance(glm::vec2 cell) {
        return sqrt(pow(cell.x - m_Moving->getCurrentCell().x, 2) +
                    pow(cell.y - m_Moving->getCurrentCell().y, 2));
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

    virtual void Update() override;

    void DrawAvatar();

    void setAIType(AI_Type type){
        m_aiType=type;
    }
    AI_Type getAIType(){
        return m_aiType;
    }
public:
    GameObjectID getID() { return m_ID; }

    std::shared_ptr<AttackAndDamage> getAttackAndDamage() {
        return m_AttackAndDamage;
    }
    std::shared_ptr<Moving> getMoving() { return m_Moving; }
    std::shared_ptr<AvatarOrder> getAvatarOrder() { return m_Order; }

    void setHealth(std::shared_ptr<Health> health) { m_Health = health; }

public:
    // huntable
    std::shared_ptr<Health> getHealth() override { return m_Health; }
    void setOrderNoOrder() override {
        m_Order->setAvatarOrder(AvatarOrderType::NO_ORDER);
    };
    void setOrderTakenDamage() override {
        m_Order->setAvatarOrder(AvatarOrderType::TAKEN_DAMAGE);
    };
    glm::vec2 getCurrentLocationInCell() override {
        return getMoving()->getCurrentCell();
    };

protected:
    std::shared_ptr<SpriteSheet> m_AvatarSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<Util::SpriteSheetAnimation> m_SpriteSheetAnimation =
        std::make_shared<Util::SpriteSheetAnimation>();

    // order
    std::shared_ptr<AvatarOrder> m_Order = std::make_shared<AvatarOrder>();
    // moving
    std::shared_ptr<Moving> m_Moving = std::make_shared<Moving>();
    // health
    std::shared_ptr<Health> m_Health = std::make_shared<Health>();
    // attack and damage
    std::shared_ptr<AttackAndDamage> m_AttackAndDamage =
        std::make_shared<AttackAndDamage>();

private:
    GameObjectID m_ID;
    AI_Type m_aiType = AI_Type::NONE;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_AVATAR_HPP
