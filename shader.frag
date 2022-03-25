#version 330 core
out vec4 FragColor;

in float Height;
in float x;
in float z;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 src = texture(texture1, TexCoord);
    vec4 dst = texture(texture2, TexCoord);
    // FragColor =  vec3((src.rgb * src.a + dst.rgb * dst.a * (1.0 - src.a)) / final_alpha, final_alpha);

    FragColor = dst;
    FragColor = mix(src, dst, x);
}
