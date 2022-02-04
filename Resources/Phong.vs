#version 330

in vec3  position;
in vec3  normal;
in vec2 UVCoord;
uniform mat4 ViewProjectionMat;
uniform mat4 ModelTransformMat;

out vec3 normal0;
out vec2 uv;

void recomputeNormals()
{
    normal0 = normalize((transpose(inverse(mat3(ModelTransformMat))) * normal));
}

void main()
{
    recomputeNormals();
    uv= UVCoord;
    gl_Position = ViewProjectionMat*ModelTransformMat*vec4(position, 1.0);
}

