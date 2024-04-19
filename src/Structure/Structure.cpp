//
// Created by 盧威任 on 1/30/24.
//
#include "Structure/Structure.hpp"
#include "Mechanics/GameObjectManager.hpp"
#include "Util/Input.hpp"
#include "Util/Transform.hpp"
#include "config.hpp"
void Structure::Start() {
    m_Transform.scale={2.f,2.f};
    m_HighLight.SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
    m_HighLight.SetHLScale(this->GetTranScale());
    m_HighLight.SetZIndex(DEFAULT_ZINDEX - 1);
    SetZIndex(DEFAULT_ZINDEX);
    this->SetAttachVisible(false);
    SetSpriteSheet();
    m_CurrentState = updateMode::Moveable;
}
void Structure::Update() {
    switch (m_CurrentState) {
    case updateMode::Invisidable: {
        this->updateInvinsible();
        break;
    }
    case updateMode::Fixed: {
        this->updateFixed();
        break;
    }
    case updateMode::Moveable: {
        this->updateMoveable();
        break;
    }
    }
}
void Structure::updateFixed() {
    // Attachment and self readjust location and draw---------------
    attachmentUpdate();
    if(m_SpriteSheetAnimation->getFinished()){
        m_StructureSpriteSheet->DrawSpriteByIndex(m_StructureSpriteSheet->getSize()-1,m_Transform,DEFAULT_ZINDEX);
    }else{
        m_SpriteSheetAnimation->Draw(m_Transform,DEFAULT_ZINDEX);
    }
    // Script when select--------------------
}
void Structure::updateMoveable() {
    // debug
    printf("debug message : Structure movable\n");
    //
    glm::vec2 location = Util::Input::GetCursorPosition();
    location = MapUtil::ScreenToGlobalCoord(location);
    this->SetObjectLocation(location);
    this->SetVisible(true);
    //glm::vec2 cellPos = MapUtil::GlobalCoordToCellCoord(location);
    m_StructureSpriteSheet->DrawSpriteByIndex(m_StructureSpriteSheet->getSize()-1,m_Transform,DEFAULT_ZINDEX);
    if (Util::Input::IsKeyPressed(
            Util::Keycode::MOUSE_LB) && ifBuildable()) {
        this->SetObjectLocation(location);
        m_SpriteSheetAnimation->initSpriteSheetAnimation(m_StructureSpriteSheet,true,INTERVAL,false);
        SetOccupiedAreaUnbuildable();
        this->SetCurrentUpdateMode(updateMode::Fixed);
    }
}

void Structure::SetObjectLocation(glm::vec2 location) {
    location = MapUtil::PositionStickToGrid(location);
    ObjectLocation = location;
    DrawLocation = {location.x + 0.5 * CELL_SIZE.x,
                    location.y + 0.5 * CELL_SIZE.y};
    m_Transform.translation = DrawLocation;
}

void Structure::SetAttachVisible(bool visible) {
    m_HighLight.SetObjectLocation(this->DrawLocation);
    m_HighLight.SetVisible(visible);
}
void Structure::attachmentUpdate() {
    m_HighLight.SetObjectLocation(this->GetDrawLocation());
    m_HighLight.Draw();
}
std::vector<glm::vec2> Structure::GetAbsoluteOccupiedArea(){
    std::vector<glm::vec2> Area;
    for(auto i:m_relativeOccupiedArea){
        Area.push_back({i.x+GetObjectCell().x,i.y+GetObjectCell().y});
    }
    return Area;
}
void Structure::SetOccupiedAreaUnbuildable(){
//    for (auto i :GetAbsoluteOccupiedArea()) {
//        m_Map->getTileByCellPosition(i)->setBuildable(false);
//        m_Map->getTileByCellPosition(i)->setWalkable(false);
//    }
}
bool Structure::ifBuildable(){
//    for (auto i :GetAbsoluteOccupiedArea()) {
//        if(m_Map->getTileByCellPosition(i)->getBuildable()== false){
//            return false;
//        }
//    }
    return true;
}
