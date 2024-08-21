#version 330 core

layout(location =0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 Color;

uniform float gMinHeight;
uniform float gMaxHeight;

void main(){
     gl_Position = projection * view * model * vec4(aPos,1.0f);

     float DeltaHeight = gMaxHeight - gMinHeight;
     float HeightRatio = (aPos.y - gMinHeight)/DeltaHeight;

     float c = HeightRatio * 0.8 + 0.2;
     Color = vec4(c,c,c,1.0f);
     
}