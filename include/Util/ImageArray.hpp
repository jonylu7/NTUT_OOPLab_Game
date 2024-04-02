#ifndef UTIL_IMAGEARRAY_HPP
#define UTIL_IMAGEARRAY_HPP

#include "pch.hpp" // IWYU pragma: export
#include <functional>
#include <glm/fwd.hpp>
#include <vector>

#include "Core/Drawable.hpp"
#include "Core/Texture.hpp"

#include "Camera.hpp"
#include "Util/Logger.hpp"
#include "Util/Transform.hpp"

namespace Util {
/**
 * @class ImageArray
 * @brief A class representing an image.
 *
 * This class encapsulates the properties and behaviors of an image.
 * It includes properties such as texture and surface.
 * It also includes behaviors such as drawing the image.
 */
class ImageArray : public Core::Drawable {
public:
    /**
     * @brief Constructor that takes a file path to the image.
     *
     * @param filepath The file path to the image.
     */
    explicit ImageArray(const std::string &filepath,
                        const std::vector<glm::vec2> offset);

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

    void Draw(const Util::Transform &transform, const float zIndex) override;
    void DrawUsingCamera(const Util::Transform &transform,
                         const float zIndex) override;

    // should be deleted
    int getHeight() { return 0; };
    int getWidth() { return 0; };

private:
    void InitProgram();
    void InitVertexArray(std::vector<glm::vec2> offset);
    void InitUniformBuffer();

    static constexpr int UNIFORM_SURFACE_LOCATION = 0;

    static std::unique_ptr<Core::Program> s_Program;
    std::unique_ptr<Core::VertexArray> m_VertexArray;
    std::unique_ptr<Core::UniformBuffer<Core::Matrices>> m_UniformBuffer;

private:
    std::unique_ptr<Core::Texture> m_Texture = nullptr;
    std::vector<glm::vec2> m_Offset;
    std::string m_Path;
    glm::vec2 m_Size;
};
} // namespace Util

#endif
