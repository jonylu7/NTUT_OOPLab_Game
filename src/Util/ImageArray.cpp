#include "Util/ImageArray.hpp"

#include "pch.hpp"

#include "Core/Texture.hpp"
#include "Core/TextureUtils.hpp"

#include "Util/TransformUtils.hpp"

#include "config.hpp"

namespace Util {
ImageArray::ImageArray(const std::string &filepath)
    : m_Path(filepath) {
    if (s_Program == nullptr) {
        InitProgram();
    }
    if (s_VertexArray == nullptr) {
        InitVertexArray();
    }
    if (s_UniformBuffer == nullptr) {
        InitUniformBuffer();
    }

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

void ImageArray::SetImage(const std::string &filepath) {
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

void ImageArray::Draw(const Util::Transform &transform, const float zIndex) {
    auto data = Util::ConvertToUniformBufferData(transform, m_Size, zIndex);
    s_UniformBuffer->SetData(0, data);

    m_Texture->Bind(UNIFORM_SURFACE_LOCATION);
    s_Program->Bind();
    s_Program->Validate();

    s_VertexArray->Bind();
    s_VertexArray->DrawTriangles();
}

void ImageArray::DrawUsingCamera(const Util::Transform &transform, const float zIndex){
    auto data = Util::ConvertToUniformBufferDataUsingCameraMatrix(transform, m_Size, zIndex);
    s_UniformBuffer->SetData(0, data);

    m_Texture->Bind(UNIFORM_SURFACE_LOCATION);
    s_Program->Bind();
    s_Program->Validate();

    s_VertexArray->Bind();
    s_VertexArray->DrawTriangles();
}

void ImageArray::InitProgram() {
    // TODO: Create `BaseProgram` from `Program` and pass it into `Drawable`
    s_Program = std::make_unique<Core::Program>("../assets/shaders/Base.vert",
                                                "../assets/shaders/Base.frag");
    s_Program->Bind();

    GLint location = glGetUniformLocation(s_Program->GetId(), "surface");
    glUniform1i(location, UNIFORM_SURFACE_LOCATION);
}

void ImageArray::InitVertexArray() {
    s_VertexArray = std::make_unique<Core::VertexArray>();

    // NOLINTBEGIN
    // These are vertex data for the rectangle but clang-tidy has magic
    // number warnings

    // Vertex

    //init position,uv,index according to "offset"vector

    std::vector<float> positionVertex;
    std::vector<float> uvVertex;
    std::vector<unsigned int> indexBuffer;

    std::vector<glm::vec2> offset={glm::vec2(0,0),glm::vec2(1,0),glm::vec2(1,1),glm::vec2(0,1)
                                                                                            ,glm::vec2(0,3)
    };


    for(int i=0;i<offset.size();i++){
        positionVertex.push_back(-0.5F+offset[i].x);
        positionVertex.push_back(0.5F+offset[i].y);

        positionVertex.push_back(-0.5F+offset[i].x);
        positionVertex.push_back(-0.5F+offset[i].y);
        positionVertex.push_back(0.5F+offset[i].x);
        positionVertex.push_back(-0.5F+offset[i].y);

        positionVertex.push_back(0.5F+offset[i].x);
        positionVertex.push_back(0.5F+offset[i].y);


        std::vector<float> uv({ 0.0F, 0.0F, //
                            0.0F, 1.0F, //
                            1.0F, 1.0F, //
                            1.0F, 0.0F});
        uvVertex.insert(uvVertex.end(),uv.begin(),uv.end());

        unsigned int iBufferStep=i*4;
        std::vector<unsigned int> iBuffer({0+iBufferStep, 1+iBufferStep, 2+iBufferStep, //
            0+iBufferStep, 2+iBufferStep, 3+iBufferStep});

        indexBuffer.insert(indexBuffer.end(),iBuffer.begin(),iBuffer.end());

    }




    s_VertexArray->AddVertexBuffer(std::make_unique<Core::VertexBuffer>(
positionVertex,
        2));

    // UV
    s_VertexArray->AddVertexBuffer(std::make_unique<Core::VertexBuffer>(
        uvVertex,
        2));

    // Index
    s_VertexArray->SetIndexBuffer(
        std::make_unique<Core::IndexBuffer>(indexBuffer));
    // NOLINTEND


}

void ImageArray::InitUniformBuffer() {
    s_UniformBuffer = std::make_unique<Core::UniformBuffer<Core::Matrices>>(
        *s_Program, "Matrices", 0);
}


std::unique_ptr<Core::Program> ImageArray::s_Program = nullptr;
std::unique_ptr<Core::VertexArray> ImageArray::s_VertexArray = nullptr;
std::unique_ptr<Core::UniformBuffer<Core::Matrices>> ImageArray::s_UniformBuffer =
    nullptr;
} // namespace Util
