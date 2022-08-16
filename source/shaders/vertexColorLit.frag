#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - FragPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 6.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	return vec4(Color * diffuse, 1.0f);
}

vec4 direcLight()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	return vec4(Color * diffuse, 1.0f);
}
void main()
{
	// outputs final color
	FragColor = direcLight();
}
