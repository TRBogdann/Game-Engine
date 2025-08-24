#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float ambient;
uniform vec3  lightPos;

out vec4 ourColor;

void main() {

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
   
    vec3 col = vec3(0.2,0.2,0.2);
     
    int v1 = int(10.0*(aPos.x+1.0)/2.0);  
    int v2 = int(10.0*(aPos.z+1.0)/2.0);  
    int res1 = v1%2;
    int res2 = v2%2;
    
    
    if(res2 == res1)
    {
        col = vec3(0.7,0.7,0.7);
    }
    
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = vec3(0.0,1.0,0.0);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0,1.0,1.0);
    ourColor = vec4(col*(ambient + diffuse),1.0);
}