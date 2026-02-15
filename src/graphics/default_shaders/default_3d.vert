#version 450

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_colour;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec2 a_texcoords;

layout(location = 0) out vec4 colour;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec2 tex_coords;

layout(push_constant) uniform ViewUniforms {
    mat4 model;
    mat4 view;
    mat4 projection;
};

layout(binding = 1) uniform PBROptions {
    vec4 u_baseColour;
    float u_metallic;
    float u_roughness;
};

void main() {
    // gl_Position = projection * view * model * vec4(a_position, 1.0);
    gl_Position = vec4(a_position, 1.0);
    colour = vec4(a_colour, 1.0);
    tex_coords = a_texcoords;

    // mat3 rotationMatrix = transpose(inverse(mat3(model)));
    // normal = normalize(rotationMatrix * a_normal);
}
