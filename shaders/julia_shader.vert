#version 330 core

layout ( location = 0 ) in vec3 aPos;


//modified from main code
uniform float scale;
uniform mat4  rotation;
uniform mat4  cameraMatrix;
uniform mat4  view;

//sends fragment position to fragment shader
out vec4 fragment_position;

void main()
{   

    gl_Position = fragment_position   = cameraMatrix*view* rotation *vec4 ( aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);;
 
}