#version 330 core
#extension GL_ARB_separate_shader_objects : enable

in vec3 TexCoord; 
uniform samplerCube cubemapTexture;

out vec4 fColor;

void main()
{
    fColor = texture(cubemapTexture, normalize(TexCoord));
}