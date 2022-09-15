#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;
uniform float time;

void main()
{
    outColor = aColor;
    gl_Position = vec4(aPos.x  , aPos.yz, 1.0);
    TexCoord = aTexCoord;
}