//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_BATCHRENDER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_BATCHRENDER_HPP
#include "Core/Texture.hpp"
#include "Core/Program.hpp"
#include "Core/VertexArray.hpp"
#include "Core/UniformBuffer.hpp"
#include "Util/Transform.hpp"
#include "pch.hpp"

class BatchRender{

public:
BatchRender();
~BatchRender(){}
void Start(const char *filePath);
void Update();

private:
    void InitProgram();
    void InitVertexArray();
    void InitUniformBuffer(const Util::Transform &transform = Util::Transform(), const float zIndex = -1);

    static constexpr int UNIFORM_SURFACE_LOCATION = 0;

    static std::unique_ptr<Core::Program> s_Program;
    static std::unique_ptr<Core::VertexArray> s_VertexArray;
    static std::unique_ptr<Core::UniformBuffer<Core::Matrices>> s_UniformBuffer;


private:
    std::unique_ptr<Core::Program> m_Program;
    std::unique_ptr<Core::Texture> m_Texture = nullptr;
    std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>> m_Surface =
        nullptr;

    bool hasRoom;




};


#endif // PRACTICALTOOLSFORSIMPLEDESIGN_BATCHRENDER_HPP
