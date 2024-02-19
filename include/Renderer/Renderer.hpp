//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_RENDERER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_RENDERER_HPP
#include "BatchRender.hpp"
#include "Component/Component.hpp"
#include <vector>
class Renderer {
private:
    std::vector<std::shared_ptr<BatchRender>> m_BatchRenderList;

public:
    Renderer();
    ~Renderer(){};
    void addObject(std::shared_ptr<BatchRender> object) {
        m_BatchRenderList.push_back(object);
    };
    void render() {
        for (auto i : m_BatchRenderList) {
            i->render();
        }
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_RENDERER_HPP
