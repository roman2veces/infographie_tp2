#version 330 core
#extension GL_ARB_separate_shader_objects : enable

// uniform vec3 outColor;
out vec4 fColor;

void main()
{
	fColor = vec4(1.0, 0.0, 0.0, 1.0);
}