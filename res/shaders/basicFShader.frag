#version 440
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

out vec4 fs_color;

uniform vec4 color;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform sampler2D texture0;



void main()
{

	//vec3 lightColor = vec3(1.0, 1.0, 1.0);
	//vec3 lightPos = vec3(-10, 30, 10);
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - position);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	float specularStrength = 0.8;

	vec3 viewDir = normalize(cameraPos - position);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2);
	vec3 specular = specularStrength * spec * lightColor;

	fs_color = vec4(ambient + specular + diffuse, 1.0) * color;
	//fs_color = color;
}