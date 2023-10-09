#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 vPosition;

// uniform mat4 mvp;

void  main()
{
	// gl_Position = mvp * vec4(vPosition, 1.0);
	gl_Position = vec4(vPosition, 1.0);
}