
#include "Structure/OreRefinery.hpp"
void OreRefinery::Start() {
    // Set Texture----------------------------------------
    SetDrawable(std::make_unique<Util::Image>("../assets/sprites/OreRefinery.png"));
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
    m_HighLight.SetHLScale(this->GetTranScale());
    onSelected();
    // State
    SetCurrentUpdateMode(Structure::updateMode::Moveable);
}
