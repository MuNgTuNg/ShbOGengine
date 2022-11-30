#version 330 core

out vec4 FragColor;
in vec3 color;

uniform float weirdColorOffset;

void main()
{
    

    FragColor = vec4(color.x * weirdColorOffset, color.y + weirdColorOffset, color.z - weirdColorOffset,1.0f);
}