//
// Created by 盧威任 on 1/30/24.
//

#include "Structure/Structure.hpp"
#include "Util/Input.hpp"
#include "Util/Transform.hpp"
#include "config.hpp"
void Structure::Start() {
    m_HighLight.SetDrawable(std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
    m_HighLight.SetHLScale(this->GetTranScale());
    m_HighLight.SetZIndex(DEFAULT_ZINDEX);
    SetZIndex(DEFAULT_ZINDEX);
    m_HighLight.SetObjectLocation(this->GetObjectLocation());
    this->SetAttachVisible(false);
    m_CurrentState=updateMode::Moveable;
}
void Structure::Update() {
    switch (m_CurrentState) {
    case updateMode::Invisidable:{
        this->updateInvinsible();
        break;
    }
    case updateMode::Fixed:{
        this->updateFixed();
        break;
    }
    case updateMode::Moveable:{
        this->updateMoveable();
        break;
    }
    }
}
void Structure::updateFixed(){
    m_HighLight.SetObjectLocation({ObjectLocation.x+0.5*CELL,ObjectLocation.y+0.5*CELL});
    Draw();
    if(Util::Input::IsKeyDown(Util::Keycode::T)){//Need to change
        b_select=!b_select;
    }
    if(b_select){
        this->onSelected(true);
    }else{
        this->onSelected(false);
    }
}
void Structure::updateMoveable(){
    glm::vec2 location=Util::Input::GetCursorPosition();
    location=MapClass::ScreenToGlobalCoord(location);
    this->SetObjectLocation(location);
    this->SetVisible(true);
    this->Draw();
    if(Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)){
        this->SetObjectLocation(location);
        this->SetCurrentUpdateMode(updateMode::Fixed);
    }
}
void Structure::updateInvinsible(){
    this->SetAttachVisible(false);
}

void Structure::DecreaseHp(float Hp){
    this->buildingHp-=Hp;
}
float Structure::GetElectricPower(){
    return this->electricPower;
}
float Structure::GetBuildingTime(){
    return this->buildingTime;
}
float Structure::GetBuildingCost(){
    return this->buildingCost;
}
float Structure::GetBuildingHp(){
    return this->buildingHp;
}
glm::vec2 Structure::ChangeToCell(glm::vec2 location) {
    int _x=location.x/CELL;
    int _y=location.y/CELL;
    return {_x*CELL,_y*CELL};
}
void Structure::SetObjectLocation(glm::vec2 location) {
    location=ChangeToCell(location);
    ObjectLocation = location;
    m_Transform.translation = {location.x+0.5*CELL,location.y+0.5*CELL};
}
void Structure::onSelected(bool selected){
    m_HighLight.SetObjectLocation(this->GetObjectLocation());
    this->SetAttachVisible(selected);
    m_HighLight.Draw();
};
void Structure::SetAttachVisible(bool visible) {
    m_HighLight.SetVisible(visible);
}
