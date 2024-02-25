#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Core/Program.hpp"
#include "Core/UniformBuffer.hpp"
#include "Core/VertexArray.hpp"

class Triangle {
    struct Matrices {
        glm::mat2 m_View;
        glm::mat2 m_Projection;
    };

public:
    Triangle();

    ~Triangle() = default;

    void Update();

private:
    Core::Program m_Program = Core::Program("../assets/shaders/Triangle.vert",
                                            "../assets/shaders/Triangle.frag");
    std::unique_ptr<Core::VertexArray> m_VertexArray =
        std::make_unique<Core::VertexArray>();

    std::unique_ptr<Core::UniformBuffer<Matrices>> m_Matrices =
        std::make_unique<Core::UniformBuffer<Matrices>>(m_Program, "Triangle",
                                                        0);
};

#endif
