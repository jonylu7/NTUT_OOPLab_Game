#version 410 core

layout(location = 0) in vec2 vertexPos;
layout(location = 1) in vec3 color;

layout(location = 0) out vec3 vertexColor;

layout(std140) uniform DrawLines {
    mat4 _model;
    mat4 _projection;
};

void main() {

    vec4 pos = _projection*_model*vec4(vertexPos,0,1);

    gl_Position = vec4(pos.x, pos.y, 0, 1);
    vertexColor = color;
}


