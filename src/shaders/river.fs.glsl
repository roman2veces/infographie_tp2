#version 330 core
#extension GL_ARB_separate_shader_objects : enable

in vec2 fragmentTexCoord;

uniform sampler2D riverTexture;

out vec4 FragColor;

void main() {

    FragColor = texture2D(riverTexture, fragmentTexCoord);
}