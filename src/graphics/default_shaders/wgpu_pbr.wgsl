struct VertexInput {
    @location(0) position: vec3f,
    @location(1) colour: vec3f,
    @location(2) normal: vec3f,
    @location(3) texcoords: vec2f,
    @location(4) skin_indices: vec4<u32>,
    @location(5) skin_weights: vec4f};

struct VertexOutput {
    @builtin(position) clip_position: vec4f,
    @location(0) colour: vec4f,
    @location(1) normal: vec3f,
    @location(2) texcoords: vec2f,
};

struct FragmentInput {
    @location(0) colour: vec4f,
    @location(1) normal: vec3f,
    @location(2) texcoords: vec2f,
}

struct MatrixUniforms {
    view: mat4x4f,
    projection: mat4x4f,
};

@group(0) @binding(0) var<uniform> matrices: MatrixUniforms;
@group(0) @binding(1) var<uniform> model: mat4x4f;

@vertex
fn vs_main(
    in: VertexInput,
) -> VertexOutput {
    var out: VertexOutput;

    out.clip_position = matrices.projection
						* matrices.view
						* model
						* vec4f(in.position, 1.0);

    out.colour = vec4(in.colour, 1.0);
    out.texcoords = in.texcoords;

    return out;
}

@fragment
fn fs_main(
    in: VertexOutput
) -> @location(0) vec4f {
    return in.colour;
}
