#version 440 

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

layout(location = 0) out vec3 position;
layout(location = 1) out vec3 normal;

void main()
{
	position = vec4(ModelMatrix * vec4(vertex_position, 1.0f)).xyz;
	normal = mat3(transpose(inverse(ModelMatrix))) * vertex_normal;  
	if (vertex_normal.x == 0)
		gl_Position = vec4(0);
	else
		gl_Position = ModelMatrix * ProjectionMatrix * ViewMatrix * vec4(vertex_position, 1.0f);
	
}