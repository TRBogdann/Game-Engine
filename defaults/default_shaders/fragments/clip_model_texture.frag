#version 450 core

in float clipMe;
uniform sampler2D textureSampler;
in vec2 fragTexCoord;
out vec4 FragColor;

void main() {
    if (clipMe > 0.5)
        discard;
    
    FragColor = texture(textureSampler, fragTexCoord);
}

