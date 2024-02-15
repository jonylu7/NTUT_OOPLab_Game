#ifndef UTIL_IMAGE_HPP
#define UTIL_IMAGE_HPP

#include "pch.hpp" // IWYU pragma: export

#include <functional>

#include "Core/Drawable.hpp"
#include "Core/Texture.hpp"

#include "Camera.hpp"
#include "Util/Logger.hpp"
#include "Util/Transform.hpp"

namespace Util {
class Image : public Core::Drawable {
public:
    Image(const std::string &filepath);

    unsigned int getTextureID() { return m_Texture->GetTextureId(); }
    void Draw(const Util::Transform &transform, const float zIndex) override;
    void DrawUsingCamera(Core::Matrices data) override {
        s_UniformBuffer->SetData(0, data);

        m_Texture->Bind(UNIFORM_SURFACE_LOCATION);
        s_Program->Bind();
        s_Program->Validate();

        s_VertexArray->Bind();
        s_VertexArray->DrawTriangles();
    }

    int getHeight() { return m_Surface->h; };
    int getWidth() { return m_Surface->w; };

private:
    void InitProgram();
    void InitVertexArray();
    void InitUniformBuffer(const Util::Transform &transform = Util::Transform(),
                           const float zIndex = -1);

    // temp place here until batch
    void InitUniformBuffer(CameraClass camera) {
        Core::Matrices data = {
            {}, camera.getProjectionMatrix() * camera.getViewMatrix()};
        s_UniformBuffer->SetData(0, data);
    };

    static constexpr int UNIFORM_SURFACE_LOCATION = 0;

    static std::unique_ptr<Core::Program> s_Program;
    static std::unique_ptr<Core::VertexArray> s_VertexArray;
    static std::unique_ptr<Core::UniformBuffer<Core::Matrices>> s_UniformBuffer;

private:
    std::unique_ptr<Core::Texture> m_Texture = nullptr;
    std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>> m_Surface =
        nullptr;
};
} // namespace Util

#endif
