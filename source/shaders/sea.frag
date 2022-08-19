#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;

void main()
{
	FragColor = vec4(Color, 0.5f);
}
