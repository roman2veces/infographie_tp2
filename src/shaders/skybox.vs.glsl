#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 vPosition;

uniform mat4 mvp;

out vec3 TexCoord;

void  main()
{
	gl_Position = mvp * vec4(vPosition, 1.0);
	TexCoord = vPosition;
}