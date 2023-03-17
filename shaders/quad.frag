#version 330 core

//output color in rgba
out vec4 FragColor;

//comes from vertex shader
in vec3 color;


void main()
{
    

    FragColor = vec4(color,1.f);
}