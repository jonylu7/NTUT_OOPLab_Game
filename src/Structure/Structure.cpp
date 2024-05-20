//
// Created by 盧威任 on 1/30/24.
//
#include "Structure/Structure.hpp"
#include "Mechanics/UnitManager.hpp"
#include "Util/Input.hpp"
#include "Util/Transform.hpp"
#include "config.hpp"

void Structure::Start() {
    if (this->m_ID.getUnitType() == UnitType::NONE) {
        Structure::getHealth()->setLivingStatus(
            std::make_shared<LivingStatus>(LivingStatus::NOT_BORN_YET));
        getStructureOrder()->setStructureOrder(StructureOrderType::NO_ORDER);
    } else {
        m_Transform.scale = {2.f, 2.f};
        m_HighLight.SetDrawable(
            std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
        m_HighLight.SetHLScale(this->GetTransform().scale);
        m_HighLight.SetZIndex(DEFAULT_ZINDEX - 1);
        SetZIndex(DEFAULT_ZINDEX);
        this->SetAttachVisible(false);
        SetSpriteSheet();
        Structure::getHealth()->setLivingStatus(
            std::make_shared<LivingStatus>(LivingStatus::ALIVE));
        getStructureOrder()->setStructureOrder(
            StructureOrderType::SELECTING_SITE);
    }
}
void Structure::Start(glm::vec2 location) {
    m_Transform.scale = {2.f, 2.f};
    m_HighLight.SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
    m_HighLight.SetHLScale(this->GetTransform().scale);
    m_HighLight.SetZIndex(DEFAULT_ZINDEX - 1);
    SetZIndex(DEFAULT_ZINDEX);
    SetAttachVisible(false);
    SetSpriteSheet();
    Structure::getHealth()->setLivingStatus(
        std::make_shared<LivingStatus>(LivingStatus::ALIVE));
    getStructureOrder()->setStructureOrder(StructureOrderType::SELECTING_SITE);
    this->SetObjectLocation(location);
    SetVisible(true);
    m_SpriteSheetAnimation->initSpriteSheetAnimation(m_StructureSpriteSheet,
                                                     false, INTERVAL, false);
    getStructureOrder()->setStructureOrder(StructureOrderType::BUILT);
    Structure::getHealth()->setLivingStatus(
        std::make_shared<LivingStatus>(LivingStatus::ALIVE));
}
void Structure::Update() {

    switch (*getHealth()->getLivingStatus()) {
    case LivingStatus::NOT_BORN_YET:
        this->updateInvinsible();
        break;
    case LivingStatus::ALIVE:
        whenSelected();

        if (getStructureOrder()->getStructureOrderType() ==
            StructureOrderType::SELECTING_SITE) {
            this->updateMoveable();
        } else if (getStructureOrder()->getStructureOrderType() ==
                   StructureOrderType::BUILT) {
            this->updateFixed();
        } else if (getStructureOrder()->getStructureOrderType() ==
                   StructureOrderType::TAKEN_DAMAGE) {
            this->updateFixed();
        }
        break;
    case LivingStatus::DEAD:
        // execute something
        break;
    }
}
void Structure::updateFixed() {
    // Attachment and self readjust location and draw---------------
    attachmentUpdate();
    if (m_SpriteSheetAnimation->getFinished()) {
        m_StructureSpriteSheet->DrawSpriteByIndex(
            m_StructureSpriteSheet->getSize() - 1, m_Transform, DEFAULT_ZINDEX);
    } else {
        m_SpriteSheetAnimation->Play();
        m_SpriteSheetAnimation->Draw(m_Transform, DEFAULT_ZINDEX);
    }
}
void Structure::updateMoveable() {
    // debug
    printf("debug message : Structure movable\n");
    //
    glm::vec2 location = Util::Input::GetCursorPosition();
    location = MapUtil::ScreenToGlobalCoord(location);
    this->SetObjectLocation(location);
    this->SetVisible(true);
    // glm::vec2 cellPos = MapUtil::GlobalCoordToCellCoord(location);
    m_StructureSpriteSheet->DrawSpriteByIndex(
        m_StructureSpriteSheet->getSize() - 1, m_Transform, DEFAULT_ZINDEX);
}

void Structure::SetObjectLocation(glm::vec2 location) {
    location = MapUtil::PositionStickToGrid(location);
    m_ObjectLocation = location;
    m_DrawLocation = {location.x + 0.5 * CELL_SIZE.x,
                      location.y + 0.5 * CELL_SIZE.y};
    m_Transform.translation = m_DrawLocation;
}

void Structure::SetAttachVisible(bool visible) {
    m_HighLight.SetObjectLocation(this->m_DrawLocation);
    m_HighLight.SetVisible(visible);
}
void Structure::attachmentUpdate() {
    m_HighLight.SetObjectLocation(this->GetDrawLocation());
    m_HighLight.Draw();
}
std::vector<glm::vec2> Structure::getAbsoluteOccupiedArea() {
    std::vector<glm::vec2> Area;
    for (auto i : m_RelativeOccupiedArea) {
        Area.push_back({i.x + getLocationCell().x, i.y + getLocationCell().y});
    }
    return Area;
}
