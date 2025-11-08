#version 430

layout(location = 0) out vec4 colour;

layout(location = 0) in vec4 _colour;
layout(location = 1) in vec2 _tex_coords;
layout(binding = 2) uniform sampler2D u_diffuseTexture;

void main() {
    colour = texture(u_diffuseTexture, _tex_coords) * _colour;
	colour.w = 0.4;
}
