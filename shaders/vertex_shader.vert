#version 330 core

layout ( location = 0 ) in vec3 aPos;

layout (location = 1 ) in vec3 aColor;

layout (location = 2) in vec2 aTex;

//modified from main code
uniform float scale;
uniform mat4 rotationMatrix;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

uniform mat4 localView;

//sends color and texture data to the fragment shader
out vec3 color;
out vec2 texCoord;

void main()
{
    gl_Position = proj*localView* view * model * rotationMatrix * vec4 ( aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
    
    color = aColor;
    texCoord = aTex;
}