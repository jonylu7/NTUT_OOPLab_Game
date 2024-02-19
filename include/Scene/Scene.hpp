//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
#include "Camera.hpp"
#include "Component/Object.hpp"
#include <vector>
class Scene {
public:
    Scene() {}
    ~Scene() {}
    void Init();
    void Start() {
        for (auto i : m_ObjectList) {
            i->Start();
        }
        m_IsRunning = true;
    };
    void addObjectToScene(std::shared_ptr<Object> object) {
        m_ObjectList.push_back(object);
        if (m_IsRunning) {
            object->Start();
        }
    }
    virtual void Update();

    CameraClass getCamera() { return m_camera; };

private:
    CameraClass m_camera;
    std::vector<std::shared_ptr<Object>> m_ObjectList;
    bool m_IsRunning = false;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
