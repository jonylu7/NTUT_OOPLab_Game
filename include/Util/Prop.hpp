//
// Created by nudle on 2024/5/9.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PROP_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PROP_HPP
#include "Structure/Structure.hpp"
class Prop:public Structure{
public:
    Prop(bool selectable = false):Structure(selectable){}
    ~Prop()override{}
    void Start(glm::vec2 width)override{
        m_width=width;
        this->SetAttachVisible(true);
        SetZIndex(8);
        m_HighLight.SetZIndex(10);
    }
    void attachmentUpdate()override{
        m_HighLight.SetObjectLocation({this->GetDrawLocation().x+m_highlightOffset.x,this->GetDrawLocation().y+m_highlightOffset.y});
        m_HighLight.Draw();
    }
    void setScale(glm::vec2 scale){
        m_Transform.scale=scale;
    }
    void setHighLightImage(std::string path){
        m_HighLight.SetDrawable(std::make_unique<Util::Image>(path));
    }
    void setHighLightOffset(glm::vec2 globalDistance){
        m_highlightOffset=globalDistance;
    }
    void setObjectLocation(glm::vec2 location,float offsetCell){
        location = MapUtil::PositionStickToGrid(location);
        m_ObjectLocation = location;
        m_DrawLocation = {location.x + offsetCell * CELL_SIZE.x,
                          location.y + offsetCell * CELL_SIZE.y};
        m_Transform.translation = m_DrawLocation;
    }
    bool isOverlaps(glm::vec2 cell){
        if(cell.x>m_ObjectLocation.x&&cell.x<m_ObjectLocation.x+m_width.x){
            if(cell.y>m_ObjectLocation.y&&cell.y<m_ObjectLocation.y+m_width.y){
                return true;
            }
        }
        return false;
    }
    void Update()override{
        Draw();
        attachmentUpdate();
    }
private:
    glm::vec2 m_width={1,1};
    glm::vec2 m_highlightOffset={0,0};
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PROP_HPP
