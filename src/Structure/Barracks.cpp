#include "Structure/Barracks.hpp"

void Barracks::Start() {
    // Set Texture----------------------------------------
    m_StructureSpriteSheet->Start("../assets/sprites/Barracks_SpriteSheet.png",
                                  48, 48, 13, 0);
    SetRelativeOccupiedArea({{0, 0}, {0, 1}, {1, 0}, {1, 1}});
    m_wayPoint->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/flagB.png"));
    m_HighLight.SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
    // Set ZIndex
    this->SetZIndex(DEFAULT_ZINDEX);
    m_wayPoint->SetZIndex(DEFAULT_ZINDEX);
    m_HighLight.SetZIndex(DEFAULT_ZINDEX - 1);
    // Set Attachment Scale &
    // Visibility----------------------------------------
    m_HighLight.SetHLScale(this->GetTransform().scale);
    whenSelected();
    // State
    setStructOrder(StructureOrderType::NOT_CONSTRUCTED_YET);
}
void Barracks::Start(glm::vec2 location) {
    // Set Texture----------------------------------------
    m_StructureSpriteSheet->Start("../assets/sprites/Barracks_SpriteSheet.png",
                                  48, 48, 13, 0);
    SetRelativeOccupiedArea({{0, 0}, {0, 1}, {1, 0}, {1, 1}});
    m_wayPoint->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/flagB.png"));
    m_HighLight.SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
    // Set ZIndex
    this->SetZIndex(DEFAULT_ZINDEX);
    m_wayPoint->SetZIndex(DEFAULT_ZINDEX);
    m_HighLight.SetZIndex(DEFAULT_ZINDEX - 1);
    // Set Attachment Scale &
    // Visibility----------------------------------------
    m_HighLight.SetHLScale(this->GetTransform().scale);
    whenSelected();
    // State
    this->SetObjectLocation(location);
    m_SpriteSheetAnimation->initSpriteSheetAnimation(m_StructureSpriteSheet,
                                                     true, INTERVAL, false);
    m_LivingStatus = LivingStatus::ALIVE;
    m_StructOrder = StructureOrderType::BUILT;
}