//
// Created by 盧威任 on 2/16/24.
//

#include "Grid.hpp"
#include "Core/Drawable.hpp"

void Grid::Start(std::vector<Line> lineVector) {
    m_lineVector = lineVector;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

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

    glLineWidth(2.0f);
}

void Grid::Update() {

    const float width = 1280.0F / 2.0F;
    const float height = 720.0F / 2.0F;
    glLineWidth(lineWidth);
    std::vector<float> vertex = {};

    for (auto line : m_lineVector) {
        vertex.push_back(line.getlineFrom().x);
        vertex.push_back(line.getlineFrom().y);
        vertex.push_back(line.getColor().x);
        vertex.push_back(line.getColor().y);
        vertex.push_back(line.getColor().z);

        vertex.push_back(line.getlineTo().x);
        vertex.push_back(line.getlineTo().y);
        vertex.push_back(line.getColor().x);
        vertex.push_back(line.getColor().y);
        vertex.push_back(line.getColor().z);
    }
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_lineVector.size() * 5 * 2, &vertex);

    m_Program.Bind();
    m_Program.Validate();

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

    // m_Matrices->SetData(0, data);
    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    m_Matrices->SetData(0, data);

    glDrawArrays(GL_LINES, 0, m_lineVector.size() * 5 * 2);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    m_Program.Unbind();
}