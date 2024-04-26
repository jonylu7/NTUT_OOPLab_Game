//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP

#include "Map/MapUtility.hpp"
#include "Unit/AttackAndDamageUnit.hpp"
#include "Unit/PathfindingUnit.hpp"
#include "Unit/PathUtility.hpp"

class Avatar : public PathfindingUnit,
               public AttackAndDamageUnit,
               public Util::GameObject,
               public Selectable {

public:
    enum class UnitMode { DEAD, MOVE, IDLE, MOVE_ATTACK, ALIVE };
    Avatar(){};
    ~Avatar() override{};

    virtual void Start(glm::vec2 destination) { // destination = Barrack's
                                                // waypointLocation
        // setCurrentCell()  //CurrentCell = Structure's Location
        this->SetDrawable(customizeImage());
//        setSpriteSheet();
        SetVisible(true);
        setCurrentCell(destination);
        setNextCell(destination);

        setMovementSpeed(4);
        m_currentMode = UnitMode::MOVE;
        m_Transform.scale = {0.5, 0.5};
    }
    virtual void aliveUpdate() {
        if (walkTowardNextCell() || b_justStarted) {
            b_justStarted = false;
            setCurrentCell(
                MapUtil::GlobalCoordToCellCoord(getCurrentLocation()));
            // setCurrentDir(m_wayPointUnit.getFirstCellDir());
            setNextCell(PathUtility::getNextCellByCurrent(getCurrentDir(),
                                                          getNextCell()));
            printf("(aliveUpdate) getting new dir\n");
        }
        // m_wayPointUnit.Update();

        SetVisible(true);
        m_Transform.translation = getCurrentLocation();

        Draw();
//        m_SpriteSheetAnimation->Draw(m_Transform, DEFAULT_ZINDEX);

        printf("Avatar cell={%d,%d}\n", getCurrentLocation().x,
               getCurrentLocation().y);
        printf("-----------avatar------------------\n");
    }

    float getDistance(glm::vec2 cell) {
        return sqrt(pow(cell.x - getCurrentCell().x, 2) +
                    pow(cell.y - getCurrentCell().y, 2));
    }

    void setSpriteSheet(){
        m_AvatarSpriteSheet->Start(
            "../assets/sprites/mech.png", 50, 39, 247, 0);
    }

    void DEBUG_printCurrentMoveDirection(MoveDirection Dir) {
        switch (Dir) {
        case MoveDirection::RIGHT: {
            printf("(DEBUG)Avatar DIR:Right\n");
            break;
        }
        case MoveDirection::LEFT: {
            printf("(DEBUG)Avatar DIR:Left\n");
            break;
        }
        case MoveDirection::UP: {
            printf("(DEBUG)Avatar DIR:Up\n");
            break;
        }
        case MoveDirection::DOWN: {
            printf("(DEBUG)Avatar DIR:Down\n");
            break;
        }
        case MoveDirection::UP_RIGHT: {
            printf("(DEBUG)Avatar DIR:Up_Right\n");
            break;
        }
        case MoveDirection::DOWN_LEFT: {
            printf("(DEBUG)Avatar DIR:Down_Left\n");
            break;
        }
        case MoveDirection::DOWN_RIGHT: {
            printf("(DEBUG)Avatar DIR:Down_Right\n");
            break;
        }
        case MoveDirection::UP_LEFT: {
            printf("(DEBUG)Avatar DIR:Up_Left\n");
            break;
        }
        case MoveDirection::IDLE: {
            printf("(DEBUG)Avatar DIR:IDLE\n");
            break;
        }
        }
    }

    UnitMode getUnitMode() { return m_currentMode; }
    virtual void customizeUpdate() {
        if (1 == 1) {
        }
    }

    void whenSelected() override {}

    virtual std::shared_ptr<Util::Image> customizeImage() {
        return std::make_unique<Util::Image>("../assets/sprites/Hunter.png");
    }
    virtual void playSpriteAnimation(){
        switch (m_currentDir) {
        case MoveDirection::UP:{
            m_SpriteSheetAnimation->setFrameRange(0,0);
            break;
        }
        case MoveDirection::UP_RIGHT:{
            m_SpriteSheetAnimation->setFrameRange(0,0);
            break;
        }
        case MoveDirection::UP_LEFT:{
            m_SpriteSheetAnimation->setFrameRange(9,14);
            break;
        }
        case MoveDirection::RIGHT:{
            m_SpriteSheetAnimation->setFrameRange(0,0);
            break;
        }
        case MoveDirection::LEFT:{
            m_SpriteSheetAnimation->setFrameRange(15,0);
            break;
        }
        case MoveDirection::DOWN_RIGHT:{
            m_SpriteSheetAnimation->setFrameRange(0,0);
            break;
        }
        case MoveDirection::DOWN_LEFT:{
            m_SpriteSheetAnimation->setFrameRange(0,0);
            break;
        }
        case MoveDirection::DOWN:{
            m_SpriteSheetAnimation->setFrameRange(0,0);
            break;
        }
        case MoveDirection::IDLE:{
            m_SpriteSheetAnimation->setFrameRange(0,0);
            break;
        }
        }
    }
    virtual void Update() override {
        switch (m_currentMode) {
        case (UnitMode::DEAD): {
            SetVisible(false);
            break;
        }
        case (UnitMode::MOVE): {
            aliveUpdate();
            break;
        }
        case (UnitMode::MOVE_ATTACK): {
            aliveUpdate();
            customizeUpdate();
            break;
        }
            // attack
        }
    }

protected:
    std::shared_ptr<Util::Image> m_Image;
    std::shared_ptr<SpriteSheet> m_AvatarSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<Util::SpriteSheetAnimation> m_SpriteSheetAnimation =
        std::make_shared<Util::SpriteSheetAnimation>();
private:
    bool b_SelectedByCursor = true;
    bool b_justStarted = true;
    UnitMode m_currentMode;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
