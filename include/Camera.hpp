//
// Created by 盧威任 on 2/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP
#include "Component/Component.hpp"
#include "Core/Context.hpp"
#include "config.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/Drawable.hpp"

class CameraClass : public Component {
public:
    CameraClass() {
        setPosition(glm::vec2(0,0));
    }
    CameraClass(glm::vec2 position) {
        setPosition(position);
    }
    ~CameraClass() {}

    static float getCameraZoom() { return m_Zoom; }
    void setCameraZoom(float zoom) { m_Zoom = zoom; }

    void addCameraZoom(float add);

    glm::vec2 getPosition() { return m_Position; }

    void setPosition(glm::vec2 position) { m_Position = position; }

    static glm::mat4x4 getProjectionMatrix() {
        /*
         * adjust projection matrix when window size is changing
         */
         return glm::ortho(0.0F, float(WINDOW_WIDTH / 2), 0.0F,
                                        float(WINDOW_HEIGHT / 2), 0.F, 100.F);
    }

    static glm::mat4x4 getViewMatrix() {
        /*
         * get camera position
         */
        glm::vec3 cameraFront(0.F, 0.F, -1.F);
        glm::vec3 cameraUp(0.F, 1.F, 0.F);
        return glm::lookAt(
                glm::vec3(m_Position.x, m_Position.y, 50.F), // position
                cameraFront + glm::vec3(m_Position.x, m_Position.y, 0.F), cameraUp);
    }

    float getMovingSpeed() { return m_MovingSpeed; }
    float getZoomingSpeed() { return m_ZoomingSpeed; }

    void Start() override;
    void Update() override;
    void UpdateWhenCursorAtBoarder();
    void UpdateWhenCursorScroll();

private:
    static float m_Zoom;
    static glm::vec2 m_Position;
    float m_MovingSpeed = 2.5F;
    float m_ZoomingSpeed = 0.5F;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP




