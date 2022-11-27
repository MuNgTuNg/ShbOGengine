#version 330 core

out vec4 FragColor;
in vec3 color;

uniform float colorInput;

void main()
{
    

    FragColor = vec4(color.x * colorInput, color.y + colorInput, color.z - colorInput,1.0f);
}