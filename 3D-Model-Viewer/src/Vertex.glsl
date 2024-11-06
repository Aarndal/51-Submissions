#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

out vec3 vertexPosition;
out vec4 vertexColor;
out vec3 vertexNormal;
out vec2 vertexUV;

layout(location = 4) uniform mat4 modelMatrix;
layout(location = 5) uniform mat4 viewMatrix;
layout(location = 6) uniform mat4 projectionMatrix;
layout(location = 7) uniform mat3 modelNormalMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position,1.0);

	vertexPosition = (modelMatrix * vec4(position, 1.0)).xyz;
	vertexNormal = normalize(modelNormalMatrix * normal);
	vertexColor = color;
	vertexUV = uv;
}