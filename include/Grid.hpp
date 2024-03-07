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

class Grid : public Core::Drawable {

public:
    Grid(){};
    ~Grid(){};
    void InitVertexAndColor();
    void Start(std::vector<Line> lineVector);
    void Draw(const Util::Transform &transform, const float zIndex) override;
    void DrawUsingCamera(const Util::Transform &transform,
                         const float zIndex) override;

    void switchActivate() { m_Activate = !m_Activate; };

private:
    std::vector<Line> m_lineVector;

    Core::Program m_Program = Core::Program("../assets/shaders/DrawLines.vert",
                                            "../assets/shaders/DrawLines.frag");

    std::unique_ptr<Core::UniformBuffer<Core::Matrices>> m_NewMatrices =
        std::make_unique<Core::UniformBuffer<Core::Matrices>>(m_Program, "Grid",
                                                        0);


    float m_lineWidth = 1.0F;

    std::unique_ptr<Core::VertexArray> m_VertexArray =
        std::make_unique<Core::VertexArray>();

    bool m_Activate = false;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_GRID_HPP
