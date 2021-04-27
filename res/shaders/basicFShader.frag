#version 440

//in vec3 vs_posiiton;
//in vec3 vs_color;
//in vec2 vs_texcoord;

out vec4 color;

uniform sampler2D texture0;

void main()
{
	color = vec4(0.6f, 0.6f, 0.6f, 1.0f);
	//fs_color = texture(texture0, vs_texcoord);
}