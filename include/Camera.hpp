//
// Created by 盧威任 on 2/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP
#include "Core/Context.hpp"
#include "Core/Drawable.hpp"
#include "config.hpp"
#include "glm/gtc/matrix_transform.hpp"
// 164.F perfect for
constexpr float FOV_UPPER_LIMIT = 164.F;
constexpr float FOV_LOWER_LIMIT = 1.F;
class CameraClass {
public:
    CameraClass() { setPosition(glm::vec2(0, 0)); }
    ~CameraClass() {}

    static float getCameraZoom() { return m_Zoom; }
    void setCameraZoom(float zoom) { m_Zoom = zoom; }

    void addCameraZoom(float add);

    static glm::vec2 getPosition() { return m_Position; }

    void setPosition(glm::vec2 position);

    static glm::mat4x4 getProjectionMatrix() {

        return glm::ortho(0.0F, float(WINDOW_WIDTH), 0.0F, float(WINDOW_HEIGHT),
                          0.F, 100.F);
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
    void changeFOV(float offset);

    void Start(glm::vec2 minPosition, glm::vec2 maxPosition);
    void Update();
    void UpdateWhenCursorAtBoarder();
    void UpdateWhenCursorScroll();

private:
    static float m_Zoom;
    static glm::vec2 m_Position;
    float m_MovingSpeed = 20.F;
    float m_ZoomingSpeed = 0.1F;
    static float m_Fov;
    static glm::vec2 s_boarderMaximum;
    static glm::vec2 s_boarderMinimum;
    glm::vec2 m_minPosition;
    glm::vec2 m_maxPosition;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CAMERA_HPP
