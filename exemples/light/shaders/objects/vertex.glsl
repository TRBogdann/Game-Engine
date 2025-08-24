#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float ambient;
uniform vec3  lightPos;
uniform float specularStrength;
uniform vec3 viewPos;
uniform vec3 aColor;

out vec4 ourColor;

void main() {

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vec3 col = aColor;
    
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));

    //Diffusal light
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = aNorm;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0,1.0,1.0);

    //Specular light


    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0,1.0,1.0); 

    ourColor = vec4(col*(ambient + diffuse + specular),1.0);
}