#include "Rectangle.hpp"

#include "Core/IndexBuffer.hpp"
#include "Core/VertexBuffer.hpp"

Rectangle::Rectangle() {
    std::vector<float> vertices={
        0.6F,0.6F,
        0.0F,0.6F,
        0.0F,0.0F,
        0.6F,0.0F
    };
    std::vector<unsigned int> index={
        0,1,2,
        2,3,0
    };
m_VertexArray->AddVertexBuffer(std::make_unique<Core::VertexBuffer>(vertices,2));
m_VertexArray->SetIndexBuffer(std::make_unique<Core::IndexBuffer>(index));
}

void Rectangle::Update() {
    m_Program.Bind();
    m_Program.Validate();
    m_VertexArray->Bind();
    m_VertexArray->DrawRectangles();
}
