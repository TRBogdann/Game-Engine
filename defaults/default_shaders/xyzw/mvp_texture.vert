#version 450 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fragTexCoord;

void main() {
    gl_Position = projection * view * model * position;
    fragTexCoord = texCoord;
}

