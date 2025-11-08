#version 430

layout(location = 0) out vec4 colour;
layout(location = 0) in vec4 _colour;

void main() {
    colour = _colour;
}
