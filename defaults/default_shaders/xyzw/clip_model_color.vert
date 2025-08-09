#version 450 core
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 mxPoz;
uniform vec4 mnPoz;

out vec4 ourColor;
out float clipMe;

void main() {
    clipMe = 0.0;
    if (aPos.x < mnPoz.x || aPos.x > mxPoz.x ||
        aPos.y < mnPoz.y || aPos.y > mxPoz.y ||
        aPos.z < mnPoz.z || aPos.z > mxPoz.z) {
        clipMe = 1.0;
    }

    gl_Position = projection * view * model * aPos;
    ourColor = aColor;
}

