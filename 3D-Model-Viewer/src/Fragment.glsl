#version 460 core

in vec4 vertexColor;
in vec2 vertexUV;

out vec4 fragColor;

uniform sampler2D texture01;

void main()
{
	//fragColor = vec4(vertexUV.x, vertexUV.y, 0.0, 1.0);

	fragColor = texture(texture01, vertexUV);
}