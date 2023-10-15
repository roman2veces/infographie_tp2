#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 mvp;
uniform float time; 

out vec2 fragmentTexCoord; 

void main()
{

    float x = 0.025 * cos(time * 1.0 + (texCoord.x + texCoord.y) * 2.0);
    float y = 0.01 * sin(time * 2.0 + (texCoord.x + texCoord.y) * 2.0);

    vec2 updatedTexCoords = texCoord + vec2(x, y);
    gl_Position = mvp * vec4(position, 1.0);
    fragmentTexCoord = updatedTexCoords;
}