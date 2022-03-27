#version 330 core
out vec4 FragColor;

in float Height;
in float x;
in float z;
in vec2 TexCoord;
uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord);
}
