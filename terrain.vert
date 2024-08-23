#version 330 core

layout(location =0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 Color;
void main(){
     gl_Position = projection * view * model * vec4(aPos,1.0f);

     Color = vec4(aPos.y/200.0);
}