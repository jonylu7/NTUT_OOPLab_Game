//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_OBJECT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_OBJECT_HPP
#include "Component.hpp"
#include <string>
#include <vector>

class Object {
public:
    Object(std::string name)
        : m_ObjectName(name),
          m_ObjectList(){};
    ~Object(){};

    template <typename T>
    void addComponent(T data) {
        m_ObjectList.push_back(std::make_shared<T>(data));
    };

    void popComponent() { m_ObjectList.pop_back(); }

    std::shared_ptr<Component> getComponentByIndex(int index) {
        return m_ObjectList[index];
    };

    std::string getObjectName() { return m_ObjectName; };

    void Start() {
        for (auto i : m_ObjectList) {
            i->Start();
        }
    }
    void Update() {
        for (auto i : m_ObjectList) {
            i->Update();
        }
    }

private:
    std::string m_ObjectName;
    std::vector<std::shared_ptr<Component>> m_ObjectList;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_OBJECT_HPP
