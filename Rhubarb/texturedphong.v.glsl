uniform mat4 mvMatrix;
uniform mat4 pMatrix;
uniform vec3 vLight;

attribute vec4 vVertex;
attribute vec3 vNormal;
attribute vec2 vTexture;

varying vec4 vFragColor;
varying vec2 vTex;

void main(void) { 
	mat3 mNormalMatrix;
	mNormalMatrix[0] = normalize(mvMatrix[0].xyz);
	mNormalMatrix[1] = normalize(mvMatrix[1].xyz);
	mNormalMatrix[2] = normalize(mvMatrix[2].xyz);
	
	vec3 vNorm = normalize(mNormalMatrix * vNormal);
	
	vec4 ecPosition;
	vec3 ecPosition3;
	ecPosition = mvMatrix * vVertex;
	ecPosition3 = ecPosition.xyz /ecPosition.w;
	
	vec3 vLightDir = normalize(vLight - ecPosition3);
	float fDot = max(0.0, dot(vNorm, vLightDir)); 
	
	vec4 vColor = vec4(1.0, 1.0, 1.0, 1.0);
	
	vFragColor.rgb = vColor.rgb * fDot;
	vFragColor.a = vColor.a;
	
	vTex = vTexture;
	
	mat4 mvpMatrix;
	mvpMatrix = pMatrix * mvMatrix;
	
	gl_Position = mvpMatrix * vVertex; 
}