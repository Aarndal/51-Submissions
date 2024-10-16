#version 460 core

in vec4 vertexColor;
in vec2 vertexUV;

out vec4 fragColor;

void main()
{
	fragColor = vec4(vertexUV.x, vertexUV.y, 0.0, 1.0);
}