#version 130

in vec4 vVertex;
in vec3 vNormal;
in vec2 vTexture;

uniform mat4   mvpMatrix;
uniform mat4   mvMatrix;
uniform mat3   normalMatrix;
uniform vec3   LightPosition;

smooth out vec3 vNormalSmooth;
smooth out vec3 vLightDir;
smooth out vec2 vTextureSmooth;

void main(void) 
{
    vNormalSmooth = normalMatrix * vNormal;

    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

    vLightDir = normalize(LightPosition - vPosition3);

	vTextureSmooth = vTexture;
	
    gl_Position = mvpMatrix * vVertex;
}