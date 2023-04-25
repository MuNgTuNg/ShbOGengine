#version 330 core

layout ( location = 0 ) in vec3 aPos;

layout (location = 1 ) in vec3 aColor;


//modified from main code
uniform float scale;
uniform mat4 rotation;
uniform mat4 cameraMatrix;
uniform mat4 view;
uniform mat4 model;

//sends color and texture data to the fragment shader
out vec3 color;

void main()
{
    gl_Position =  cameraMatrix* model*view* rotation *vec4 ( aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
    
    color = aColor;
}