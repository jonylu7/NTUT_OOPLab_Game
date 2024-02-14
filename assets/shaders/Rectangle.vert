#version 410 core

layout(location = 0) in vec2 vertexPos;
layout(location = 0) out vec3 vertexColor;

/**
 * C++ and GLSL maps `mat2` differently because weird padding issues
 * https://www.khronos.org/opengl/wiki/Layout_Qualifier_(GLSL)#Interface_components
 *
 * Sample code: `mat2 m = {a, b, c, d};`
 *
 * C++:
 * | a | b | c | d |
 *
 * GLSL:
 * | a | b |   |   |
 * | c | d |   |   |
 */

void main() {
    gl_Position = vec4(vertexPos.x, vertexPos.y, 0, 1);
    vertexColor=vec3(1.F,1.F,1.F);
}


