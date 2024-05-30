#include "Display/CustomizableImage.hpp"

#include "pch.hpp"

#include "Core/Texture.hpp"
#include "Core/TextureUtils.hpp"

#include "Util/TransformUtils.hpp"

namespace Util {
CustomizableImage::CustomizableImage(const std::string &filepath) {
    auto surface =
        std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>>{
            IMG_Load(filepath.c_str()),
            SDL_FreeSurface,
        };
    if (surface == nullptr) {
        LOG_ERROR("Failed to load image: '{}'", filepath);
        LOG_ERROR("{}", IMG_GetError());
    }

    m_Texture = std::make_unique<Core::Texture>(
        Core::SdlFormatToGlFormat(surface->format->format), surface->w,
        surface->h, surface->pixels);
    m_Size = {surface->w, surface->h};
}

void CustomizableImage::SetImage(const std::string &filepath) {
    auto surface =
        std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>>{
            IMG_Load(filepath.c_str()),
            SDL_FreeSurface,
        };
    if (surface == nullptr) {
        LOG_ERROR("Failed to load image: '{}'", filepath);
        LOG_ERROR("{}", IMG_GetError());
    }

    m_Texture->UpdateData(Core::SdlFormatToGlFormat(surface->format->format),
                          surface->w, surface->h, surface->pixels);
    m_Size = {surface->w, surface->h};
}

void CustomizableImage::DrawTest(int count, const Util::Transform &transform,
                                 const float zIndex) {
    auto data = Util::ConvertToUniformBufferData(transform, m_Size, zIndex);
    s_UniformBuffer->SetData(0, data);

    m_Texture->Bind(UNIFORM_SURFACE_LOCATION);
    s_Program->Bind();
    s_Program->Validate();

    s_VertexArray->Bind();
    s_VertexArray->DrawTriangles();
}

void CustomizableImage::DrawUsingCamera(const Util::Transform &transform,
                                        const float zIndex) {
    auto data = Util::ConvertToUniformBufferDataUsingCameraMatrix(
        transform, m_Size, zIndex);
    s_UniformBuffer->SetData(0, data);

    m_Texture->Bind(UNIFORM_SURFACE_LOCATION);
    s_Program->Bind();
    s_Program->Validate();

    s_VertexArray->Bind();
    s_VertexArray->DrawTriangles();
}

void CustomizableImage::Init(std::vector<float> positionvertex,
                             std::vector<float> uv,
                             std::vector<unsigned int> indexbuffer) {

    m_PositionVertex = positionvertex;
    m_Uv = uv;
    m_IndexBuffer = indexbuffer;

    InitProgram();

    InitVertexArray();

    InitUniformBuffer();
}

void CustomizableImage::InitProgram() {
    // TODO: Create `BaseProgram` from `Program` and pass it into `Drawable`
    s_Program = std::make_unique<Core::Program>("../assets/shaders/Base.vert",
                                                "../assets/shaders/Base.frag");
    s_Program->Bind();

    GLint location = glGetUniformLocation(s_Program->GetId(), "surface");
    glUniform1i(location, UNIFORM_SURFACE_LOCATION);
}

void CustomizableImage::InitVertexArray() {
    s_VertexArray = std::make_unique<Core::VertexArray>();
    s_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(m_PositionVertex, 2));

    // UV

    s_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(m_Uv, 2));

    // Index
    s_VertexArray->SetIndexBuffer(
        std::make_unique<Core::IndexBuffer>(m_IndexBuffer));
    // NOLINTEND
}

void CustomizableImage::InitUniformBuffer() {
    s_UniformBuffer = std::make_unique<Core::UniformBuffer<Core::Matrices>>(
        *s_Program, "Matrices", 0);
}

std::unique_ptr<Core::Program> CustomizableImage::s_Program = nullptr;
std::unique_ptr<Core::VertexArray> CustomizableImage::s_VertexArray = nullptr;
std::unique_ptr<Core::UniformBuffer<Core::Matrices>>
    CustomizableImage::s_UniformBuffer = nullptr;

} // namespace Util
