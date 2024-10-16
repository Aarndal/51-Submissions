#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

// add out for vertex col

out vec2 vertexUV;
out vec4 vertexColor;

void main()
{
	gl_Position = vec4(position,1.0);

	vertexColor = color;

	vertexUV = uv;
}