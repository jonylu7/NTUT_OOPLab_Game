//
// Created by nudle on 2024/5/9.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TASK_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TASK_HPP
#include "Util/GameObject.hpp"
#include "Camera.hpp"
#define CAM_OFFSET 0.05
class Task:public Util::GameObject{
public:
    Task():Util::GameObject(){ SetZIndex(20);}
    ~Task()override{}
    void importCamera(std::shared_ptr<CameraClass> camera){
        m_Camera=camera;
    }
    void setObjectScale(float scale){
        m_Transform.scale={scale,scale};
    }
    void Draw()override{
        if (!m_Visible) {
            return;
        }
        if (b_MovingRelativeToCamera) {
            //m_Transform.translation = {m_Camera->getPosition().x*CAM_OFFSET,m_Camera->getPosition().y*CAM_OFFSET};
            //printf("(Task): pos = {%5f,%5f}",m_Transform.translation.x,m_Transform.translation.y);
            m_Drawable->Draw(m_Transform, m_ZIndex);
        } else {
            m_Drawable->Draw(m_Transform, m_ZIndex);
        }
    }
private:
    std::shared_ptr<CameraClass> m_Camera;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TASK_HPP
