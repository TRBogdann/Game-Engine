#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 mxPoz;
uniform vec4 mnPoz;

out vec2 fragTexCoord;
out float clipMe;

void main() {
    clipMe = 0.0;
    if (position.x < mnPoz.x || position.x > mxPoz.x ||
        position.y < mnPoz.y || position.y > mxPoz.y ||
        position.z < mnPoz.z || position.z > mxPoz.z) {
        clipMe = 1.0;
    }

    gl_Position = projection * view * model * vec4(position, 1.0);
    fragTexCoord = texCoord;
}

