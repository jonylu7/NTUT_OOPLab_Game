#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

// IWYU pragma: export

#include "Core/Program.hpp"
#include "Core/UniformBuffer.hpp"
#include "Core/VertexArray.hpp"

struct Matrix {
    glm::mat2 m_Porj;
    glm::mat2 m_Model;
};

class Rectangle {
public:
    Rectangle();

    ~Rectangle() = default;

    void Update();

private:
    Core::Program m_Program = Core::Program("../assets/shaders/Triangle.vert",
                                            "../assets/shaders/Triangle.frag");
    std::unique_ptr<Core::VertexArray> m_VertexArray =
        std::make_unique<Core::VertexArray>();
    std::unique_ptr<Core::UniformBuffer<Matrix>> m_Matrices =
        std::make_unique<Core::UniformBuffer<Matrix>>(m_Program, "Rectangle",
                                                      0);
};

#endif
