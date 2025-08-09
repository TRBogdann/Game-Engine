#version 450 core
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 ourColor;

void main() {
    gl_Position = projection * view * model * aPos;
    ourColor = aColor;
}

