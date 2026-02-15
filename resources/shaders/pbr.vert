#version 450

#define BONE_COUNT 200

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_colour;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec2 a_texcoords;
layout(location = 4) in uvec4 a_skin_indices;
layout(location = 5) in uvec4 a_skin_weights;

layout(location = 0) out vec4 colour;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec2 tex_coords;

layout(std140, set = 1, binding = 0) uniform ViewUniforms {
    mat4 view;
    mat4 projection;
};

layout(std140, set = 1, binding = 1) uniform ModelUniforms {
    mat4 model;
};

layout(std140, set = 1, binding = 2) uniform Skeleton {
    mat4 bones[BONE_COUNT];
};



void main() {
	vec4 base_pos = vec4(a_position, 1.0);

	vec4 pos = vec4(0,0,0,0);
	for (int i = 0; i < 4; i++) {
		float w = a_skin_weights[i];
		mat4 bone = bones[a_skin_indices[i]];

		pos += w * (bone * base_pos);
	}

    gl_Position = projection * view * model * pos;

    colour = vec4(a_colour, 1.0);
    tex_coords = a_texcoords;

    // mat3 rotationMatrix = transpose(inverse(mat3(model)));
    // normal = normalize(rotationMatrix * a_normal);
}
