#ifndef CORE_SHADER_HPP
#define CORE_SHADER_HPP

#include "pch.hpp" // IWYU pragma: export

namespace Core {
/**
 * @see Core::Program
 */
class Shader {
public:
    enum class Type {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
    };

    Shader(const std::string &filepath, Type shaderType);
    Shader(const Shader &) = delete;
    Shader(Shader &&other);

    ~Shader();

    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&other);

    GLuint GetShaderId() const { return m_ShaderId; }

    void uploadMat4f(std::string varName,glm::mat4x4 matf){
        //int varLocation=glGetUniformLocation(m_ShaderId);



    };


private:
    void Compile(const std::string &src) const;
    void CheckStatus(const std::string &filepath) const;

    GLuint m_ShaderId;
};
} // namespace Core

#endif
