#version 440 

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texcoord;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

layout(location = 0) out vec3 position;
layout(location = 1) out vec2 texcoord;
layout(location = 2) out vec3 normal;

void main()
{
	position = vec3(ModelMatrix * vec4(vertex_position, 1.0f));
	normal = mat3(transpose(inverse(ModelMatrix))) * vertex_normal;  

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.0f);
	
}