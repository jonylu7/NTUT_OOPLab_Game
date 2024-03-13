//
// Created by 盧威任 on 3/8/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
#include "Core/Drawable.hpp"
#include "Util/TransformUtils.hpp"
#include "pch.hpp"
class DrawOverlays : public Core::Drawable {

    /* boxes:draw box on cell
     *cross:draw cross on cell
     * selected: defines bottom left & top right, show selected "corner" on
     *given cell range circle: defines only the center(cell coord) & the
     *radius(cell) circle-dash: defines only the center(cell coord) & the
     *radius(cell)
     */

public:
    enum class OverlayShapes {
        BOXES,
        CROSS,
        CROSSWBOX,
        SELECTED,
        CIRCLE,
        CIRCLE_DASHED
    };
    DrawOverlays(){};
    ~DrawOverlays(){};
    void Start(std::vector<int> cellcoords, OverlayShapes shapes) {
        m_drawShapes = shapes;
        if (shapes == OverlayShapes::BOXES) {
            InitBOXES();
        } else if (shapes == OverlayShapes::CROSS) {
        }
    }

    void InitCrosses() {
        std::vector<float> vertex = {
            CELL_SIZE.x - 2,
            CELL_SIZE.y - 2, // top right
            CELL_SIZE.x - 2,
            1.F, // bottom right
            1.F,
            1.F, // bottom left
            1.F,
            CELL_SIZE.y - 2,
        };                                            //
        std::vector<float> color = {0.3F, 0.3F, 0.9F, //
                                    0.3F, 0.3F, .9F,  //
                                    0.3F, 0.3F, .9F,  //
                                    0.3F, 0.3F, .9F};
        std::vector<unsigned int> indices = {
            0, 1, 2, //
            1, 2, 3  //
        };
        m_VertexArray->AddVertexBuffer(
            std::make_unique<Core::VertexBuffer>(vertex, 2));
        m_VertexArray->AddVertexBuffer(
            std::make_unique<Core::VertexBuffer>(color, 3));
        m_VertexArray->SetIndexBuffer(
            std::make_unique<Core::IndexBuffer>(indices));
    }
    void InitBOXES() {
        std::vector<float> vertex = {
            CELL_SIZE.x - 2,
            CELL_SIZE.y - 2, // top right
            CELL_SIZE.x - 2,
            1.F, // bottom right
            1.F,
            1.F, // bottom left
            1.F,
            CELL_SIZE.y - 2,
        };                                            //
        std::vector<float> color = {0.3F, 0.3F, 0.9F, //
                                    0.3F, 0.3F, .9F,  //
                                    0.3F, 0.3F, .9F,  //
                                    0.3F, 0.3F, .9F};
        std::vector<unsigned int> indices = {
            0, 1, 2, //
            1, 2, 3  //
        };
        m_VertexArray->AddVertexBuffer(
            std::make_unique<Core::VertexBuffer>(vertex, 2));
        m_VertexArray->AddVertexBuffer(
            std::make_unique<Core::VertexBuffer>(color, 3));
        m_VertexArray->SetIndexBuffer(
            std::make_unique<Core::IndexBuffer>(indices));
    }

    void Draw(const Util::Transform &trans, const float zindex) override {}

    void DrawUsingCamera(const Util::Transform &trans,
                         const float zindex) override {
        m_Program.Bind();
        m_Program.Validate();

        auto cp = CameraClass::getProjectionMatrix();
        auto cv = CameraClass::getViewMatrix();

        constexpr glm::mat4 eye(1.F);

        glm::vec2 size = {1.F, 1.F};

        auto data = Util::ConvertToUniformBufferDataUsingCameraMatrix(
            trans, size, zindex);

        m_Matrices->SetData(0, data);
        m_VertexArray->Bind();
        glLineWidth(1.F);

        if (m_drawShapes == OverlayShapes::BOXES) {
            m_VertexArray->DrawRectangles();
        } else if (m_drawShapes == OverlayShapes::CROSS) {
            m_VertexArray->DrawRectangles()
        }
    }

private:
    Core::Program m_Program = Core::Program("../assets/shaders/DrawLines.vert",
                                            "../assets/shaders/DrawLines.frag");

    std::unique_ptr<Core::UniformBuffer<Core::Matrices>> m_Matrices =
        std::make_unique<Core::UniformBuffer<Core::Matrices>>(m_Program, "Grid",
                                                              0);
    OverlayShapes m_drawShapes;
    float m_shapeLineWidth = 1.0F;
    glm::vec2 shapeLinecolor;

    std::unique_ptr<Core::VertexArray> m_VertexArray =
        std::make_unique<Core::VertexArray>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
