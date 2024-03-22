//
// Created by 盧威任 on 2/16/24.
//

#include "Grid.hpp"
#include "Core/Drawable.hpp"
#include <iostream>

void Grid::Start(std::vector<Line> lineVector) {

    // debug grid:
    m_lineVector = lineVector;

    InitVertexAndColor();
}
void Grid::queStart(std::deque<Line> lineQue) {

    // debug grid:
    m_lineVector = std::vector<Line> (lineQue.begin(),lineQue.end());

    InitVertexAndColor();
}

void Grid::Draw(const Util::Transform &transform, const float zindex) {
    // nothing
}

void Grid::DrawUsingCamera(const Util::Transform &transform,
                           const float zIndex) {

    if (m_Activate == false) {
        return;
    }
    glLineWidth(m_lineWidth);

    m_Program.Bind();
    m_Program.Validate();
    m_VertexArray->Bind();

    auto cp = CameraClass::getProjectionMatrix();
    auto cv = CameraClass::getViewMatrix();

    constexpr glm::mat4 eye(1.F);

    // size of the cell
    glm::vec2 size = {1.F, 1.F};

    auto data = Util::ConvertToUniformBufferDataUsingCameraMatrix(transform,
                                                                  size, zIndex);

    m_Matrices->SetData(0, data);
    m_VertexArray->Bind();

    m_VertexArray->DrawLines(m_lineVector.size() * 5 * 2);
}

void Grid::InitVertexAndColor() {
    std::vector<float> vertex = {};
    std::vector<float> color = {};
    std::vector<unsigned int> index = {};
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
void Grid::setLine(glm::vec2 from, glm::vec2 to, glm::vec3 color) {

    m_VertexArray = std::make_unique<Core::VertexArray>();
    m_lineVector.clear(); // 清空原有的線段
    m_lineVector.push_back(Line(from, to, color));
    InitVertexAndColor(); // 重新初始化頂點和顏色
}
