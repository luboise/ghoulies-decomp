#version 430

layout(location = 0) out vec4 colour;

layout(location = 0) in vec4 _colour;
layout(location = 1) in vec3 _normal;
layout(location = 2) in vec2 _tex_coords;

// layout(binding = 3) uniform sampler2D u_diffuseTexture;

void main() {
    vec3 the_sun = vec3(-20, 20, 0);
    float dotProd = dot(normalize(the_sun), normalize(_normal));

    float angle = acos(dotProd);
    float intensity = max(0.0, dotProd); // Ensuring no negative values

    intensity = intensity * 0.8 + 0.2;

    // Disable lighting for debugging
    // intensity = 1;

    colour = _colour;

    // colour = texture(u_diffuseTexture, _tex_coords) * intensity;
}
