#version 460 core

in vec3 vertexPosition;
in vec4 vertexColor;
in vec3 vertexNormal;
in vec2 vertexUV;

out vec4 fragColor;

uniform vec3 lightPosition = {100.,100.,0.};
uniform vec4 lightColor = {1.,1.,1.,1.};
uniform vec3 viewPosition;
uniform sampler2D texture01;

void main()
{
	//fragColor = vec4(vertexUV.x, vertexUV.y, 0.0, 1.0);
    float gamma = 2.2;
    float alpha = 1.0;

	float ambientStrength = .3;
    vec4 ambient = ambientStrength * lightColor;
    
    float diffuseStrength = 1.;
    vec3 lightDir = normalize(vertexPosition - lightPosition);
    float diff = max(dot(vertexNormal,lightDir),0.);
    vec4 diffuse = diffuseStrength * diff * lightColor;

    float specularStrength = 0.8;
    vec3 refDir = reflect(-lightDir, vertexNormal);
    vec3 viewDir = normalize(viewPosition - vertexPosition); 
    float spec = pow(max(dot(viewDir,refDir),0.),32);
    vec4 specular = specularStrength* spec * lightColor;

	vec4 color = (ambient + diffuse + specular)* texture(texture01,vertexUV);

    fragColor = vec4(pow(color.rgb, vec3(1.0/gamma)),alpha);

}