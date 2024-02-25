//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GRID_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GRID_HPP
#include "Core/Drawable.hpp"
#include "Core/Program.hpp"
#include "Core/UniformBuffer.hpp"
#include "Core/VertexArray.hpp"
#include "Line.hpp"

class Grid {
    struct Matrices {
        glm::mat2 m_View;
        glm::mat2 m_Projection;
    };

public:
    Grid(){};
    ~Grid(){};
    void StartDrawingGridByWindowSize();
    void Start();
    void Update();
    void switchActivate() { m_Activate = !m_Activate; };


private:
    std::vector<Line> m_lineVector;

    Core::Program m_Program = Core::Program("../assets/shaders/Triangle.vert",
                                            "../assets/shaders/Triangle.frag");
    std::unique_ptr<Core::UniformBuffer<Matrices>> m_Matrices =
        std::make_unique<Core::UniformBuffer<Matrices>>(m_Program, "Rectangle",
                                                        0);
    float m_lineWidth = 1.0F;

    std::unique_ptr<Core::VertexArray> m_VertexArray =
        std::make_unique<Core::VertexArray>();

    bool m_Activate = false;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GRID_HPP
