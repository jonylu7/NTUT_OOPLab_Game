#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

// IWYU pragma: export

#include "Core/Program.hpp"
#include "Core/UniformBuffer.hpp"
#include "Core/VertexArray.hpp"


class Rectangle {
public:
    Rectangle();

    ~Rectangle() = default;

    void Update();

private:
    Core::Program m_Program = Core::Program("../assets/shaders/Rectangle.vert",
                                            "../assets/shaders/Rectangle.frag");
    std::unique_ptr<Core::VertexArray> m_VertexArray =
        std::make_unique<Core::VertexArray>();


};

#endif
