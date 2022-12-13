#version 330 core

//output color in rgba
out vec4 FragColor;

//comes from vertex shader
in vec3 color;
in vec2 texCoord;

uniform sampler2D makima;
uniform sampler2D fart;

//comes from main code
uniform float weirdColorOffset;


void main()
{
    

    FragColor = texture(makima,texCoord);
    //vec4(color.x * weirdColorOffset, color.y + weirdColorOffset, color.z - weirdColorOffset,1.0f);
}