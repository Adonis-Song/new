#version 330 core
out vec4 FragColor;
in vec3 outColor;
in vec2 TexCoord;
uniform float time;
uniform sampler2D ourTexture;

void main()
{
    float bias = (time - 5.f) * 0.1f;
//     FragColor = vec4(outColor.x + bias, outColor.y + bias, outColor.z + bias , 1.0f);
    FragColor = texture(ourTexture, TexCoord);
}