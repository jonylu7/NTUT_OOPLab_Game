//
// Created by 盧威任 on 3/8/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
#include "Core/Drawable.hpp"
#include "pch.hpp"
class DrawOverlays : public Core::Drawable {

    /* boxes:draw box on cell
     *cross:draw cross on cell
     * selected: defines bottom left & top right, show selected "corner" on
     *given cell range circle: defines only the center(cell coord) & the
     *radius(cell) circle-dash: defines only the center(cell coord) & the
     *radius(cell)
     */
    enum class OverlayShapes { BOXES, CROSS, SELECTED, CIRCLE };

public:
    DrawOverlays(){};
    ~DrawOverlays(){};
    void Start(std::vector<int> cellcoords, OverlayShapes shapes) {}

    void InitVertexAndColor() {
        /*
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
            */
    }

    void Draw(const Util::Transform &trans, const float zindex) override {}

    void DrawUsingCamera(const Util::Transform &trans,
                         const float zindex) override {
        /*
        if (m_Activate == false) {
            return;
        }
        glLineWidth(m_shapelineWidth);

        m_Program.Bind();
        m_Program.Validate();
        m_VertexArray->Bind();

        auto cp = CameraClass::getProjectionMatrix();
        auto cv = CameraClass::getViewMatrix();

        constexpr glm::mat4 eye(1.F);

        glm::vec2 size = {1.F, 1.F};

        auto data = Util::ConvertToUniformBufferDataUsingCameraMatrix(
            transform, size, zIndex);

        m_Matrices->SetData(0, data);
        m_VertexArray->Bind();

        m_VertexArray->DrawLines(m_lineVector.size() * 5 * 2);
         */
    }

private:
    Core::Program m_Program = Core::Program("../assets/shaders/DrawLines.vert",
                                            "../assets/shaders/DrawLines.frag");

    std::unique_ptr<Core::UniformBuffer<Core::Matrices>> m_Matrices =
        std::make_unique<Core::UniformBuffer<Core::Matrices>>(m_Program, "Grid",
                                                              0);

    float m_shapelineWidth = 1.0F;
    glm::vec2 shapelinecolor;

    std::unique_ptr<Core::VertexArray> m_VertexArray =
        std::make_unique<Core::VertexArray>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
