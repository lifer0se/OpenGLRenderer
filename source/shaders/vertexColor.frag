#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;

uniform vec3 lightColor;

void main()
{
	// outputs final color
	FragColor = vec4(lightColor, 1.0f);
}
