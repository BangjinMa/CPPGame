#version 420 core
in Value  
{  
    vec2 texCoord;
    vec4 worldPosition;
    vec4 position;
    vec3 noraml;
}value; 

layout(std140) uniform ShadowInfos
{
    mat4 aFragPosLightSpace[4];
    float afarBounds[4];
} shadowInfos;

out vec4 FragColor;

uniform sampler2D diffuse;
uniform sampler2DArray shadowMap;

vec3 debug_color(float frag_depth)
{
    int index = 0;
	for (int i = 0; i < 4 ; i++)
	{
		if (frag_depth > shadowInfos.afarBounds[i])
			index = i + 1;
	}

	if (index == 0)
		return vec3(1.0, 0.0, 0.0);
	else if (index == 1)
		return vec3(0.0, 1.0, 0.0);
	else if (index == 2)
		return vec3(0.0, 0.0, 1.0);
	else
		return vec3(0.5, 1.0, 0.0);
}

void main() {
    float frag_depth = value.position.z;
	vec3 shadow = debug_color(frag_depth);
    FragColor = vec4(shadow, 1.0f);
}