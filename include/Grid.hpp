//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_GRID_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_GRID_HPP
#include "Core/Drawable.hpp"
#include "Core/Program.hpp"
#include "Core/UniformBuffer.hpp"
#include "Core/VertexArray.hpp"
#include "Line.hpp"
#include "Util/TransformUtils.hpp"
#include <deque>

class Grid : public Core::Drawable {

public:
    Grid(){};
    ~Grid(){};
    void InitVertexAndColor();
    void Start(std::vector<Line> lineVector);
    void queStart(std::deque<Line> lineVector);
    void Draw(const Util::Transform &transform, const float zIndex) override;
    void DrawUsingCamera(const Util::Transform &transform,
                         const float zIndex) override;

    void setLine(glm::vec2 from, glm::vec2 to, glm::vec3 color = {1, 1, 1});
    void SetActivate(bool active) { m_Activate = active; };

    void setLineWidth(float linewidth) { m_lineWidth = linewidth; }
    float getLineWidth() { return m_lineWidth; }

private:
    std::vector<Line> m_lineVector;

    Core::Program m_Program = Core::Program("../assets/shaders/DrawLines.vert",
                                            "../assets/shaders/DrawLines.frag");

    std::unique_ptr<Core::UniformBuffer<Core::Matrices>> m_Matrices =
        std::make_unique<Core::UniformBuffer<Core::Matrices>>(m_Program, "Grid",
                                                              0);

    float m_lineWidth = 1.0F;

    std::unique_ptr<Core::VertexArray> m_VertexArray =
        std::make_unique<Core::VertexArray>();

    bool m_Activate = false;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GRID_HPP
