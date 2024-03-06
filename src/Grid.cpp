//
// Created by 盧威任 on 2/16/24.
//

#include "Grid.hpp"
#include "Core/Drawable.hpp"
#include <iostream>

void Grid::Start() {

    //debug grid:
    /*
    float cellWidth = 48.F;
    float cellHeight = 48.F;

    for (int i = (WINDOW_WIDTH / 2); i > int(-(WINDOW_WIDTH / 2));
         i -= cellHeight) {
        // vertical
        m_lineVector.push_back(Line(glm::vec2(i, int(-(WINDOW_HEIGHT / 2))),
                                    glm::vec2(i, int(WINDOW_HEIGHT / 2))));
    }

    for (int i = (WINDOW_HEIGHT / 2); i > int(-(WINDOW_HEIGHT / 2));
         i -= cellWidth) {
        // horz
        m_lineVector.push_back(Line(glm::vec2(int(-(WINDOW_WIDTH / 2)), i),
                                    glm::vec2(int(WINDOW_WIDTH / 2), i)));
    }
     */
    // map grid
    float cellWidth = 48.F;
    float cellHeight = 48.F;
    int q=0;
    for (int i = (WINDOW_WIDTH / 2); i > int(-(WINDOW_WIDTH / 2));
         i -= cellHeight) {
        // vertical
        m_lineVector.push_back(Line(glm::vec2(i, int(-(WINDOW_HEIGHT / 2))),
                                    glm::vec2(i, int(WINDOW_HEIGHT / 2))));
        q++;
        if(q==5)
            break;
    }
q=0;
    for (int i = (WINDOW_HEIGHT / 2); i > int(-(WINDOW_HEIGHT / 2));
         i -= cellWidth) {
        // horz
        m_lineVector.push_back(Line(glm::vec2(int(-(WINDOW_WIDTH / 2)), i),
                                    glm::vec2(int(WINDOW_WIDTH / 2), i)));
        q++;
        if(q==5)
                break;

    }

    InitVertexAndColor();
}

void Grid::Draw(const Util::Transform &transform, const float zindex) {
    if (m_Activate == false) {
        return;
    }
    glLineWidth(m_lineWidth);
    const float width = WINDOW_WIDTH / 2.0F;
    const float height = WINDOW_HEIGHT / 2.0F;

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

    m_Matrices->SetData(0, data);
    m_VertexArray->Bind();

    m_VertexArray->DrawLines(m_lineVector.size() * 5 * 2);
}

void Grid::DrawUsingCamera(const Util::Transform &transform,
                           const float zIndex) {

    if (m_Activate == false) {
        return;
    }
    glLineWidth(m_lineWidth);
    const float width = WINDOW_WIDTH / 2.0F;
    const float height = WINDOW_HEIGHT / 2.0F;

    m_Program.Bind();
    m_Program.Validate();
    m_VertexArray->Bind();

    auto cp=CameraClass::getProjectionMatrix();
    auto cv = CameraClass::getViewMatrix();
    /*
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            std::cout<<cv[i][j]<<"---";
        }
    }
    std::cout<<"\n"<<std::endl;


*/
    auto r=cp;
    auto dp=glm::mat2(r[0][0],r[0][1],
              r[1][0],r[1][1]);

    //23 up/down

     auto m=glm::mat2(cv[3][1],cv[3][2],
                  cv[3][2],cv[3][1]);


    auto p=glm::mat2({
        1.0F / width, 0.0F, //
        0.0F, 1.0F / height //
    });
    auto mp=p*m*dp;

    auto v=glm::mat2(
        1.F, 0.F, //
        0.F, 1.F  );

    auto tranlate=transform.translation;
    Matrices data = {
        v,
        mp,
    };
    //0寬 1 右腳x 2右角y 3高
     data = {
        {
            0.3F, 0.1F, //
            0.1F, 0.3F  //
        },
        {
            2.F / width,  -0.3F/ width, //
            -0.1F/ height, 2.F / height //
        },
    };
    m_Matrices->SetData(0, data);
    m_VertexArray->Bind();

    m_VertexArray->DrawLines(m_lineVector.size() * 5 * 2);

/*
    if (m_Activate == false) {
        return;
    }
    glLineWidth(m_lineWidth);
    const float width = WINDOW_WIDTH / 2.0F;
    const float height = WINDOW_HEIGHT / 2.0F;

    m_Program.Bind();
    m_Program.Validate();
    m_VertexArray->Bind();

    auto cp=CameraClass::getProjectionMatrix();
    auto cv = CameraClass::getViewMatrix();
    auto r=cv*cp;
    auto m=glm::mat2(r[0][0],r[0][1],
                       r[1][0],r[1][1]);

    auto p=glm::mat2({
        1.0F / width, 0.0F, //
        0.0F, 1.0F / height //
    });
    auto mp=p*m;

    auto v=glm::mat4(
        1.F, 0.F, 0.F,0.F,//
        0.F, 1.F, 0.F,0.F,
        0.F, 0.F, 1.F,0.F,
        0.F, 0.F, 0.F,1.F
        );

    auto screen=glm::mat4(
        1.F/width, 1.F, 1.F,1.F,//
        1.F, 1.F/height, 1.F,1.F,
        1.F, 1.F, 1.F/width,1.F,
        1.F, 1.F, 1.F,1.F/height
    );

    auto tranlate=transform.translation;
    Core::Matrices data = {
        glm::mat4(1.F),
        r,
    };

    m_NewMatrices->SetData(0, data);
    m_VertexArray->Bind();

    m_VertexArray->DrawLines(m_lineVector.size() * 5 * 2);
    */
}

void Grid::InitVertexAndColor() {

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
