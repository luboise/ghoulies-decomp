#version 430

layout(location = 0) out vec4 colour;

layout(location = 0) in vec4 _colour;
layout(location = 1) in vec3 _normal;
layout(location = 2) in vec2 _tex_coords;

layout(set = 2, binding = 0) uniform sampler2D u_diffuseTexture;

layout(std140, set = 3, binding = 0) uniform LightingUniforms {
    float u_ambient_brightness;
    vec3 u_room_lighting_colour;
};

void main() {
    colour =
        vec4(texture(u_diffuseTexture, _tex_coords).xyz * u_ambient_brightness, 1);
}
