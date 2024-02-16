//
// Created by 盧威任 on 2/16/24.
//

#include "Grid.hpp"
#include "Core/Drawable.hpp"

void Grid::Start(std::vector<Line> lineVector) {
    glLineWidth(100.F);
    m_lineVector = lineVector;
    /*
    // Create the vbo and buffer some memory
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, m_lineVector.size() * sizeof(float), 0,
                 GL_DYNAMIC_DRAW);

    // Enable the vertex array attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    */

    std::vector<float> vertex = {};
    std::vector<float> color = {};
    for (auto line : m_lineVector) {
        vertex.push_back(line.getlineFrom().x);
        vertex.push_back(line.getlineFrom().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);

        vertex.push_back(line.getlineTo().x);
        vertex.push_back(line.getlineTo().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);
    }
    m_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(vertex, 2));
    m_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(color, 3));
}

void Grid::Update() {

    const float width = 1280.0F / 2.0F;
    const float height = 720.0F / 2.0F;

    // m_lineVector.size() * 5 * 2 & vertex

    m_Program.Bind();
    m_Program.Validate();
    m_VertexArray->Bind();

    Matrices data = {
        {
            1.F, 0.F, //
            0.F, 1.F  //
        },
        {
            1.0F / width, 0.0F, //
            0.0F, 1.0F / height //
        },
    };

    std::vector<float> vertex = {};
    std::vector<float> color = {};
    for (auto line : m_lineVector) {
        vertex.push_back(line.getlineFrom().x);
        vertex.push_back(line.getlineFrom().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);

        vertex.push_back(line.getlineTo().x);
        vertex.push_back(line.getlineTo().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);
    }

    // m_Matrices->SetData(0, data);

    m_Matrices->SetData(0, data);
    m_VertexArray->Bind();

    m_VertexArray->DrawLines(m_lineVector.size() * 5 * 2);
}