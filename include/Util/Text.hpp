#ifndef UTIL_TEXT_HPP
#define UTIL_TEXT_HPP

#include "pch.hpp" // IWYU pragma: export

#include <functional>

#include "Core/Drawable.hpp"
#include "Core/Texture.hpp"

#include "Util/Logger.hpp"

namespace Util {
class Text : public Core::Drawable {
public:
    Text(const std::string &font, int size, const std::string &text,
         const glm::mat3 &transform = {});

    void Draw() override;

private:
    void InitProgram();
    void InitVertexArray();
    void InitUniformBuffer();
    static std::unique_ptr<Core::Program> s_Program;

    std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>> m_Font;
    static std::unique_ptr<Core::VertexArray> s_VertexArray;
    static std::unique_ptr<Core::UniformBuffer<Core::Matrices>> s_UniformBuffer;
};
} // namespace Util

#endif
