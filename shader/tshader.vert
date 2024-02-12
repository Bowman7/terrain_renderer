#version 330 core

layout (location=0) in vec3 pos;

uniform mat4 gVP; 
void main() {
     gl_Position = gVP * vec4(pos,1.0f);
}