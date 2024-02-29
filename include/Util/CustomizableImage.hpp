#ifndef UTIL_CUSTOMIZABLEIMAGE_HPP
#define UTIL_CUSTOMIZABLEIMAGE_HPP

#include "pch.hpp" // IWYU pragma: export

#include <functional>
#include <glm/fwd.hpp>

#include "Core/Drawable.hpp"
#include "Core/Texture.hpp"

#include "Camera.hpp"
#include "Util/Logger.hpp"
#include "Util/Transform.hpp"
#include "Util/TransformUtils.hpp"

namespace Util {
/**
 * @class CustomizableImage
 * @brief A class representing an image.
 *
 * This class encapsulates the properties and behaviors of an image.
 * It includes properties such as texture and surface.
 * It also includes behaviors such as drawing the image.
 */
class CustomizableImage : public Core::Drawable {
public:
    /**
     * @brief Constructor that takes a file path to the image.
     *
     * @param filepath The file path to the image.

     */
    explicit CustomizableImage(const std::string &filepath);

    /**
     * @brief extra requried step to run Customizable Image, please run this!
     * @param positionvertex defines the position of the image (default: {-0.5F,
     0.5F,  // -0.5F, -0.5F, // 0.5F, -0.5F,  // 0.5F, 0.5F,})
     * @param uv defines the inner coordinates of the image (default:{0.0F,
     0.0F, // 0.0F, 1.F, // 1.F, 1.F, // 1.F, 0.0F, //})
     * @param indexbuffer defines drawing sequences of the vertex (default:{0,
     1, 2, // 0, 2, 3, //
     })
     */
    void Init(std::vector<float> positionvertex, std::vector<float> uv,
              std::vector<unsigned int> indexbuffer);

    /**
     * @brief Retrieves the size of the image.
     *
     * This function returns the size of the image.
     * comment: wierd....
     * @return The size of the image as a vec2(x, y).
     */
    glm::vec2 GetSize() const override { return m_Size; };

    /**
     * @brief Sets the image to the specified file path.
     *
     * This function sets the image to the specified file path.
     *
     * @param filepath The file path to the image.
     */
    void SetImage(const std::string &filepath);

    /**
     * @brief Draws the image with a given transform and z-index.
     *
     * This function draws the image at the specified z-index and applies the
     * given transform.
     *
     * @param transform The transform to apply to the image.
     * @param zIndex The z-index at which to draw the image.
     */

    unsigned int getTextureID() { return m_Texture->GetTextureId(); }

    void Draw(const Util::Transform &transform, const float zIndex) override {
        auto data = Util::ConvertToUniformBufferData(transform, m_Size, zIndex);
        s_UniformBuffer->SetData(0, data);

        m_Texture->Bind(UNIFORM_SURFACE_LOCATION);
        s_Program->Bind();
        s_Program->Validate();

        s_VertexArray->Bind();
        s_VertexArray->DrawTriangles();
    };

    void SetIndex(std::vector<unsigned int> index) {
        s_VertexArray->SetIndexBuffer(
            std::make_unique<Core::IndexBuffer>(index));
    }

    void DrawTest(int count, const Util::Transform &transform,
                  const float zIndex);
    void DrawUsingCamera(const Util::Transform &transform,
                         const float zIndex) override;

private:
    void InitProgram();
    void InitVertexArray();
    void InitUniformBuffer();

    static constexpr int UNIFORM_SURFACE_LOCATION = 0;

    static std::unique_ptr<Core::Program> s_Program;
    static std::unique_ptr<Core::VertexArray> s_VertexArray;
    static std::unique_ptr<Core::UniformBuffer<Core::Matrices>> s_UniformBuffer;

private:
    std::unique_ptr<Core::Texture> m_Texture = nullptr;

    std::string m_Path;
    glm::vec2 m_Size;

    std::vector<float> m_Uv;
    std::vector<float> m_PositionVertex;
    std::vector<unsigned int> m_IndexBuffer;
};
} // namespace Util

#endif // namespace Util
