#version 450 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 texCoord;

out vec2 fragTexCoord;

void main() {
    gl_Position = aPos;
    fragTexCoord = texCoord;
}

