#version 430

layout(location = 0) in vec2 a_vertexPosition;
layout(location = 1) in vec4 a_colour;
layout(location = 2) in vec2 a_texcoords;

layout(location = 0) out vec4 colour;
layout(location = 1) out vec2 tex_coords;

layout(std140, binding = 0) uniform GlobalUniforms {
    mat4 view;
    mat4 projection;
};

layout(std140, binding = 2) uniform UIUniforms {
    vec4 u_pos_ofs;
    vec4 u_scale_opacity;
};

void main() {
    vec2 pos = a_vertexPosition * u_scale_opacity.xy;
    pos += u_pos_ofs.xy;
    pos += u_pos_ofs.zw;

    // Need to flip the Y pos as OpenGL has tex coords start in bottom left instead of top left
    // TODO: Reflip it
    gl_Position = projection * view * vec4(pos, 0, 1);
    colour = vec4(a_colour.xyz, u_scale_opacity.z);
	colour.a = u_scale_opacity.z;

    tex_coords = a_texcoords;
}
