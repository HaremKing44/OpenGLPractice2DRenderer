#version 330 core

//in vec4 OurColor;

out vec4 FragColor;

uniform vec4 OurColor;

void main()
{
	FragColor = OurColor;
}