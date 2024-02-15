//
// Created by 盧威任 on 2/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP
#include "config.hpp"
class CameraClass{
public:
    CameraClass(){
        m_ProjectionMatrix=glm::mat4x4();
        m_ViewMatrix=glm::mat4x4();
        adjustProjection();
    }
    CameraClass(glm::vec2 position){
        setPosition(position);
        m_ProjectionMatrix=glm::mat4x4();
        m_ViewMatrix=glm::mat4x4();
        adjustProjection();
    }
    ~CameraClass(){}

    float getCameraZoom(){
        return m_Zoom;
    }
    void setCameraZoom(float zoom){
        m_Zoom=zoom;
    }

    void addCameraZoom(float add){
        m_Zoom+=add;
    }

    glm::vec2 getPosition(){
        return m_Position;
    }

    void setPosition(glm::vec2 position){
        m_Position=position;
    }

    void adjustProjection(){
        /*
         * adjust projection matrix when window size is changing
         */
        m_ProjectionMatrix=glm::identity<glm::mat4x4>();
        m_ProjectionMatrix=glm::ortho(0.0F,32.F*42.F,0.0F,32.F*42.F,-200.F,200.F);
    }

    glm::mat4x4 getProjectionMatrix(){
        return m_ProjectionMatrix;
    }

    glm::mat4x4 getViewMatrix(){
        /*
         * get camera position
         */
        glm::vec3 cameraFront(0.F,0.F,-1.F);
        glm::vec3 cameraUp(0.F,1.F,0.F);
        m_ViewMatrix=glm::lookAt(glm::vec3(m_Position.x,m_Position.y,50.F), // position
                                   cameraFront+glm::vec3(m_Position.x,m_Position.y,0.F),
                                   cameraUp
                                   );
        return m_ViewMatrix;
    }



private:
    float m_Zoom=1.F;
    glm::vec2 m_Position={0.F,0.F};
    glm::mat4x4 m_ProjectionMatrix,m_ViewMatrix;

};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP
