#include "Rectangle.hpp"

#include "Core/IndexBuffer.hpp"
#include "Core/VertexBuffer.hpp"

Rectangle::Rectangle() {
    std::vector<float> vertices = {14.F, 14.F, 0.0F, 14.F,
                                   0.0F, 0.0F, 14.F, 0.0F};
    std::vector<float> colors = {1.F,  1.F, 1.F, 1.F, 1.F,  1.F,
                                 1.0F, 1.F, 1.F, 1.F, 1.0F, 1.F};
    std::vector<unsigned int> index = {0, 1, 2, 2, 3, 0};
    m_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(vertices, 2));
    m_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(colors, 3));
    m_VertexArray->SetIndexBuffer(std::make_unique<Core::IndexBuffer>(index));
}

void Rectangle::Update() {
    m_Program.Bind();
    m_Program.Validate();
    m_VertexArray->Bind();
    const float width = 1280.0F / 2.0F;
    const float height = 720.0F / 2.0F;
    Matrix data = {
        {},
        {
            1.0F / width, 0.0F, //
            0.0F, 1.0F / height //
        },
    };

    m_Matrices->SetData(0, data);

    m_VertexArray->Bind();
    m_VertexArray->DrawRectangles();
}
