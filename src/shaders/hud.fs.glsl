#version 330 core
#extension GL_ARB_separate_shader_objects : enable

in vec2 TexCoord;
uniform sampler2D sampler2d;

out vec4 fColor;

void main() {
    fColor = texture(sampler2d, TexCoord);
    if(fColor.a < 0.3)
        discard;
}