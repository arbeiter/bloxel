#version 330 core
layout (location = 0) in vec3 aPos;

out float Height;
out float x;
out float z;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Height = aPos.y;
    x = aPos.x;
    z = aPos.z;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = vec2(x, z);
}
