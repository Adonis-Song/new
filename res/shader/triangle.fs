#version 330 core
out vec4 FragColor;
in vec3 outColor;
in vec2 TexCoord;
uniform sampler2D boxTexture;
uniform sampler2D smallTexture;

void main()
{
//     FragColor = vec4(outColor.x + bias, outColor.y + bias, outColor.z + bias , 1.0f);
    FragColor = mix(texture(boxTexture, TexCoord), texture(smallTexture, TexCoord), 0.2f);
//     FragColor = texture(smallTexture, TexCoord);
}