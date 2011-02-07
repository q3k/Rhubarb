#version 130

in vec4 vVertex;
in vec3 vNormal;

uniform mat4   mvpMatrix;
uniform mat4   mvMatrix;
uniform mat3   normalMatrix;
uniform vec3   LightPosition;

smooth out vec3 vNormalSmooth;
smooth out vec3 vLightDir;

void main(void) 
{
	/*mat3 normalMatrix;
	normalMatrix[0] = normalize(mvMatrix[0].xyz);
	normalMatrix[1] = normalize(mvMatrix[1].xyz);
	normalMatrix[2] = normalize(mvMatrix[2].xyz);*/
    vNormalSmooth = normalMatrix * vNormal;

    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

    //vLightDir = normalize(LightPosition - vPosition3);
	vLightDir = vec3(0.0, 0.0, 1.0);

    gl_Position = mvpMatrix * vVertex;
}
