#version 330 core

layout ( location = 0 ) in vec3 aPos;

layout (location = 1 ) in vec3 aColor;

uniform float scale;
uniform mat4 rotationMatrix;


out vec3 color;

void main()
{
    gl_Position = rotationMatrix * vec4 ( aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
    
    color = aColor;
}