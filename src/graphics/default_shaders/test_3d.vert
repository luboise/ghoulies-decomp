#version 450

layout(location = 0) in vec3 a_position;

void main() {
    // gl_Position = projection * view * model * vec4(a_position, 1.0);
    gl_Position = vec4(a_position, 1.0);

    // mat3 rotationMatrix = transpose(inverse(mat3(model)));
    // normal = normalize(rotationMatrix * a_normal);
}
