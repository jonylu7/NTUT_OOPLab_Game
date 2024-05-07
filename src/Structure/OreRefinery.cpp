
#include "Structure/OreRefinery.hpp"
void OreRefinery::Start() {
    // Set Texture----------------------------------------
    m_StructureSpriteSheet->Start(
        "../assets/sprites/OreRefinery_SpriteSheet.png", 72, 72, 10, 0);
    SetRelativeOccupiedArea({{0, 0}, {1, 0}, {1, 1}, {1, 2}, {2, 1}});
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
void OreRefinery::Start(glm::vec2 location) {
    // Set Texture----------------------------------------
    m_StructureSpriteSheet->Start(
        "../assets/sprites/OreRefinery_SpriteSheet.png", 72, 72, 10, 0);
    SetRelativeOccupiedArea({{0, 0}, {1, 0}, {1, 1}, {1, 2}, {2, 1}});
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